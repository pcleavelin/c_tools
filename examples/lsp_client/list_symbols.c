#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

#include <lsp_client/reader.h>
#include <lsp_client/lsp_client.h>
#include <arena/arena.h>

#include <arena/arena.c>

void lsp_exit(Arena *arena, int *pipe, char *msg);

int main(int argc, char *argv[]) {
    int to_client_pipe[2], to_server_pipe[2], child_pid;

    if (argc < 2) {
        perror("Expected path to lsp server");
    }

    if (pipe(to_client_pipe) < 0) {
        perror("creating client pipe failed");
        exit(1);
    }
    if (pipe(to_server_pipe) < 0) {
        perror("creating server pipe failed");
        exit(1);
    }


    if ((child_pid=fork()) == 0) {
        // Close child's stdin & stdout
        close(0);
        close(1);
        //close(2);

        // Set pipes to be the child's stdin & stdout
        dup2(to_client_pipe[0],0);
        dup2(to_server_pipe[1],1);
        //dup2(out[1],2);

        /* Close the other ends of the pipes that the parent will use, because if
         * we leave these open in the child, the child/parent will not get an EOF
         * when the parent/child closes their end of the pipe.
         */
        close(to_client_pipe[1]);
        close(to_server_pipe[0]);

        // Overwite child binary with lsp server
        execl(argv[1], "clangd", (char *)NULL);
        perror("Could not exec lsp server");
        return 1;
    }

    printf("Spawned '%s' as a child process at pid %d\n", argv[1], child_pid);

    /* This is the parent process */
    /* Close the pipe ends that the child uses to read from / write to so
     * the when we close the others, an EOF will be transmitted properly.
     */
    close(to_client_pipe[0]);
    close(to_server_pipe[1]);

    Arena json_arena = new_arena(sizeof(char)*1024*1024);
    jsmntok_t tokens[20000];

    Option(LspInitializeResult) response = lsp_initialize(&json_arena, to_client_pipe, to_server_pipe, Some(JsonString, ((JsonString) { strlen(argv[2]), argv[2] })), tokens, 20000);

    match_option(response, {
        printf("server name: %.*s\n", response.value.serverInfo.name.length, response.value.serverInfo.name.text);
        printf("server version: %.*s\n", response.value.serverInfo.version.length, response.value.serverInfo.version.text);
    }, {
        fprintf(stderr, "Error when trying to initialize LSP Server");
        exit(1);
    });

    // TODO: have some event loop going on here polling for messages from the LSP server
    JsonString filename = MakeString(argv[3]);
    // TODO: change this to take in a JsonString
    lsp_open_file(&json_arena, to_client_pipe, argv[3], MakeString("c"));
    Option(LspDocumentSymbolsResponse) symbols_response = lsp_get_document_symbols(&json_arena, to_client_pipe, to_server_pipe, filename, tokens, 20000);

    if (is_some(symbols_response)) {
        for (int i=0;i<symbols_response.value.count;++i) {
            LspSymbolInformation *si = &symbols_response.value.result[i];
            printf("Kind: %ld, %.*s\n", si->kind, si->name.length, si->name.text);
        }
    }

    lsp_shutdown(&json_arena, to_client_pipe);
    close(to_client_pipe[1]);

    return 0;
}

void lsp_exit(Arena *arena, int *pipe, char *msg) {
    perror(msg);

    arena_clear(arena);
    lsp_shutdown(arena, pipe);

    exit(1);
}
