#ifndef __C_LSPCLIENT__
#define __C_LSPCLIENT__

#include <file_io/file_io.h>
#include "reader.h"
#include "lsp_model.h"

#define lsp_send_client_message(arena, pipe, type, req) \
{\
    unsigned int index = 0;\
    const int buf_len = 40000;\
    char buf[buf_len];\
    char content_buf[100];\
    serialize_json_ ## type (arena, req, buf, buf_len, &index);\
    unsigned int header_len = snprintf(content_buf, 100, "Content-Length: %d\r\n\r\n", index);\
    write(pipe[1], content_buf, header_len);\
    write(pipe[1], buf, index);\
}

ReadResult lsp_read_from_server(Arena *arena, int *pipe, jsmntok_t *tokens, int max_tokens) {
    printf("Waiting for server message\n");
    Reader r = init_reader(arena, pipe[0]);
    ReadResult result = jrpc_read(&r);
    printf("result from jrpc_read %d\n", result.status);

    switch(result.status) {
        case READ_EOF:
            //lsp_exit(&json_arena, in, "Got EOF while reading from server\n");
            printf("Got EOF while reading from server\n");
            return result;
        case READ_MSG_IN_FLIGHT:
            //lsp_exit(&json_arena, in, "Message still in flight from server\n");
            printf("Message still in flight from server\n");
            return result;
        case READ_OUT_OF_MEMORY:
            //lsp_exit(&json_arena, in, "OUT OF MEMORY while reading from server\n");
            printf("OUT OF MEMORY while reading from server\n");
            return result;
        case READ_OK:
            printf("Got READ_OK\n");
            break;
    }

    printf("\n--> %.*s\n", result.length, result.buf);

    int jsmn_result;
    jsmn_parser p;
    jsmn_init(&p);
    if ((jsmn_result = jsmn_parse(&p, result.buf, result.length, tokens, max_tokens)) < 0) {
        fprintf(stderr, "JSON parse error: jsmn_parse: %d\n", jsmn_result);
        exit(1);
    }

    return result;
}

Option(LspServerResponse) lsp_poll_from_server(Arena *arena, int *to_client_pipe, int *to_server_pipe, jsmntok_t *tokens, int max_tokens) {
    ReadResult result = lsp_read_from_server(arena, to_server_pipe, tokens, max_tokens);
    if (result.status != READ_OK) {
        fprintf(stderr, "Failed to read from server\n");
        return None(LspServerResponse);
    }

    unsigned int parse_index = 0;
    return parse_json_LspServerResponse(arena, result.buf, tokens, &parse_index, parse_index);
}

void lsp_send_initialize_message(Arena *arena, Option(JsonString) root_directory, int *pipe) {
    pid_t pid = getpid();

    if (is_some(root_directory)) {
        const int root_uri_length = (7 + root_directory.value.length);
        char *root_uri = arena_allocate_block(arena, sizeof(char) * root_uri_length);
        sprintf(root_uri, "file://%.*s", root_directory.value.length, root_directory.value.text);

        root_directory.value.length = root_uri_length;
        root_directory.value.text = root_uri;
    }

    LspRequest req = (LspRequest) {
        1,
        (JsonString) { 3, "2.0" },
        (LspRequestMethod) {
            LspRequestMethod_Initialize,
            (LspInitializeRequestParams) {
                (LspClientCapabilities) {
                    None(LspClientCapabilitiesWorkspace)
                },
                root_directory,
                pid,
            },
        }
    };
    lsp_send_client_message(arena, pipe, LspRequest, &req);
}
void lsp_send_initialize_notification(Arena *arena, int *pipe) {
    LspNotification req = (LspNotification) {
        (JsonString) { 3, "2.0" },
        (LspNotificationMethod) {
            LspNotificationMethod_Initialized,
        }
    };
    lsp_send_client_message(arena, pipe, LspNotification, &req);
}

Option(LspInitializeResult) lsp_initialize(Arena *arena, int *to_client_pipe, int *to_server_pipe, Option(JsonString) root_uri, jsmntok_t *tokens, int max_tokens) {
    lsp_send_initialize_message(arena, root_uri, to_client_pipe);

    Option(LspServerResponse) response = lsp_poll_from_server(arena, to_client_pipe, to_server_pipe, tokens, max_tokens);
    match_option(response, {
        if (response.value.type == LspServerResponse_RequestResponse) {
            if (response.value.RequestResponse.result.type == LspRequestResult_Initialize) {
                lsp_send_initialize_notification(arena, to_client_pipe);
                return Some(LspInitializeResult, response.value.RequestResponse.result.Initialize);
            } 
        }

        printf("Error: expected Initialize reponse\n");
        return None(LspInitializeResult);
    }, {
        printf("Error: failed to parse response from server\n");
        return None(LspInitializeResult);
    });
}

void lsp_shutdown(Arena *arena, int *pipe) {
    LspRequest req = (LspRequest) {
        1,
        (JsonString) { 3, "2.0" },
        (LspRequestMethod) {
            LspRequestMethod_Shutdown,
        }
    };
    lsp_send_client_message(arena, pipe, LspRequest, &req);

    LspNotification exit_notification = (LspNotification) {
        (JsonString) { 3, "2.0" },
        (LspNotificationMethod) {
            LspNotificationMethod_Exit,
        }
    };
    lsp_send_client_message(arena, pipe, LspNotification, &exit_notification);
}

void lsp_open_file(Arena *arena, int *to_client_pipe, const char *file_path, JsonString language_type) {
    unsigned long fsize = get_file_size(file_path);
    char *text = arena_allocate_block(arena, sizeof(char)*fsize);
    if(!load_file(file_path, fsize, text)) perror("failed to load file");
    JsonString file_contents = (JsonString) { fsize, text };

    const int file_uri_length = (7 + strlen(file_path));
    char *file_uri = arena_allocate_block(arena, sizeof(char) * file_uri_length);
    sprintf(file_uri, "file://%s", file_path);

    LspNotification req = (LspNotification) {
        MakeString("2.0"),
        (LspNotificationMethod) {
            .type = LspNotificationMethod_OpenFile,
            .OpenFile = (LspDidOpenTextDocumentParams) {
                (LspTextDocumentItem){
                    (JsonString) { file_uri_length, file_uri },
                    language_type,
                    0,
                    file_contents
                },
            },
        }
    };
    lsp_send_client_message(arena, to_client_pipe, LspNotification, &req);
}

Option(LspRequestResult) lsp_get_document_symbols(Arena *arena, int *to_client_pipe, int *to_server_pipe, JsonString file_path, jsmntok_t *tokens, int max_tokens) {
    const int file_uri_length = (7 + file_path.length);
    char *file_uri = arena_allocate_block(arena, sizeof(char) * file_uri_length);
    sprintf(file_uri, "file://%.*s", file_path.length, file_path.text);

    file_path.length = file_uri_length;
    file_path.text = file_uri;

    LspRequest req = (LspRequest) {
        1,
        (JsonString) { 3, "2.0" },
        (LspRequestMethod) {
            .type = LspRequestMethod_GetDocumentSymbols,
            .GetDocumentSymbols = (LspDocumentSymbolsParams) {
                (LspTextDocument){
                    file_path
                },
            }
        }
    };
    lsp_send_client_message(arena, to_client_pipe, LspRequest, &req);

    // lol, ignore everything except the document symbols response
    while(true) {
        Option(LspServerResponse) response = lsp_poll_from_server(arena, to_client_pipe, to_server_pipe, tokens, max_tokens);
        match_option(response, {
            if (response.value.type == LspServerResponse_RequestResponse) {
                if (response.value.RequestResponse.result.type == LspRequestResult_DocumentSymbols) {
                    lsp_send_initialize_notification(arena, to_client_pipe);
                    return Some(LspRequestResult, response.value.RequestResponse.result);
                } 
            }

            printf("Error: expected textDocument/documentSymbol response\n");
            continue;
        }, {
            printf("Error: failed to parse response from server\n");
            return None(LspRequestResult);
        });
    }
}

#endif
