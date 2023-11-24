#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

#include <lsp_client/reader.h>
#include <arena/arena.h>
#include "lsp_model.h"

#include <arena/arena.c>
#include <file_io/file_io.c>

void error(char *s);

typedef struct ServerMessage {
    int content_length;
    int body_offset;

    size_t len;
    char *buf;
} ServerMessage;

typedef enum {
    MSG_EOF,
    MSG_IN_FLIGHT,

    MSG_SUCCESS,
} MessageResult;

MessageResult read_server_message(int *pipe, ServerMessage *msg) {
    int n = read(pipe[0], msg->buf, msg->len);
    if (n == 0) return MSG_EOF;
    else if (n == -1 && errno == EAGAIN) return MSG_IN_FLIGHT;

    sscanf(msg->buf, "Content-Length: %d\r\n\r\n%n", &msg->content_length, &msg->body_offset);
    printf("Server Message:\n%.*s\n", msg->content_length, msg->buf+msg->body_offset);

    return MSG_SUCCESS;
}

void send_initialize_message(Arena *arena, const char *root_directory, int *pipe) {
  pid_t pid = getpid();

  const int root_uri_length = (7 + strlen(root_directory));
  char *root_uri = arena_allocate_block(arena, sizeof(char) * root_uri_length);
  sprintf(root_uri, "file://%s", root_directory);

  InitializeRequest req = (InitializeRequest) {
    1,
    (JsonString) { 3, "2.0" },
    (JsonString) { 10, "initialize" },
    (InitializeRequestParams) {
      {},
      (JsonString) { root_uri_length, root_uri },
      pid,
    },
  };

  unsigned int index = 0;
  char buf[2048];
  char content_buf[100];
  serialize_json_InitializeRequest(arena, &req, buf, 2048, &index);

  unsigned int header_len = snprintf(content_buf, 100, "Content-Length: %d\r\n\r\n", index);
  printf("Sending-> %.*s", header_len, content_buf);
  printf("%.*s\n", index, buf);

  write(pipe[1], content_buf, header_len);
  write(pipe[1], buf, index);
}

void send_initialized_notification(Arena *arena, int *pipe) {
  pid_t pid = getpid();

  InitializedNotification req = (InitializedNotification) {
    (JsonString) { 3, "2.0" },
    (JsonString) { 11, "initialized" },
    {}
  };

  unsigned int index = 0;
  char buf[2048];
  char content_buf[100];
  serialize_json_InitializedNotification(arena, &req, buf, 2048, &index);

  unsigned int header_len = snprintf(content_buf, 100, "Content-Length: %d\r\n\r\n", index);
  printf("Sending-> %.*s", header_len, content_buf);
  printf("%.*s\n", index, buf);

  write(pipe[1], content_buf, header_len);
  write(pipe[1], buf, index);
}

void send_did_open_text_document_notification(Arena *arena, const char *file_path, int *pipe) {
  pid_t pid = getpid();

  unsigned long fsize = get_file_size(file_path);
  char *text = arena_allocate_block(arena, sizeof(char)*fsize);
  if(!load_file(file_path, fsize, text)) perror("failed to load file");
  JsonString file_contents = (JsonString) { fsize, text };

  const int file_uri_length = (7 + strlen(file_path));
  char *file_uri = arena_allocate_block(arena, sizeof(char) * file_uri_length);
  sprintf(file_uri, "file://%s", file_path);

  DidOpenTextDocumentNotification req = (DidOpenTextDocumentNotification) {
    (JsonString) { 3, "2.0" },
    (JsonString) { 20, "textDocument/didOpen" },
    (DidOpenTextDocumentParams) {
      (TextDocumentItem){
        (JsonString) { file_uri_length, file_uri },
        (JsonString) { 4, "rust" },
        0,
        file_contents
      },
    },
  };

  unsigned int index = 0;
  char buf[40000];
  char content_buf[100];
  serialize_json_DidOpenTextDocumentNotification(arena, &req, buf, 40000, &index);

  unsigned int header_len = snprintf(content_buf, 100, "Content-Length: %d\r\n\r\n", index);
  printf("Sending-> %.*s", header_len, content_buf);
  printf("%.*s\n\n", index, buf);

  write(pipe[1], content_buf, header_len);
  write(pipe[1], buf, index);
}

void send_document_symbols_message(Arena *arena, const char *file_path, int *pipe) {
  pid_t pid = getpid();

  const int file_uri_length = (7 + strlen(file_path));
  char *file_uri = arena_allocate_block(arena, sizeof(char) * file_uri_length);
  sprintf(file_uri, "file://%s", file_path);

  DocumentSymbolsRequest req = (DocumentSymbolsRequest) {
    1,
    (JsonString) { 3, "2.0" },
    (JsonString) { 27, "textDocument/documentSymbol" },
    (DocumentSymbolsParams) {
      (TextDocument){
        (JsonString) { file_uri_length, file_uri },
      },
    },
  };

  unsigned int index = 0;
  char buf[2048];
  char content_buf[100];
  serialize_json_DocumentSymbolsRequest(arena, &req, buf, 2048, &index);

  unsigned int header_len = snprintf(content_buf, 100, "Content-Length: %d\r\n\r\n", index);
  printf("Sending-> %.*s", header_len, content_buf);
  printf("%.*s\n", index, buf);
  fflush(stdout);

  write(pipe[1], content_buf, header_len);
  write(pipe[1], buf, index);
}

void send_shutdown_message(Arena *arena, int *pipe) {
  ShutdownRequest req = (ShutdownRequest) {
    2,
    (JsonString) { 3, "2.0" },
    (JsonString) { 8, "shutdown" },
  };

  unsigned int index = 0;
  char buf[2048];
  char content_buf[100];
  serialize_json_ShutdownRequest(arena, &req, buf, 2048, &index);

  unsigned int header_len = snprintf(content_buf, 100, "Content-Length: %d\r\n\r\n", index);
  printf("Sending-> %.*s", header_len, content_buf);
  printf("%.*s\n", index, buf);

  write(pipe[1], content_buf, header_len);
  write(pipe[1], buf, index);
}

void send_exit_message(Arena *arena, int *pipe) {
  ExitNotification req = (ExitNotification) {
    (JsonString) { 3, "2.0" },
    (JsonString) { 4, "exit" },
  };

  unsigned int index = 0;
  char buf[2048];
  char content_buf[100];
  serialize_json_ExitNotification(arena, &req, buf, 2048, &index);

  unsigned int header_len = snprintf(content_buf, 100, "Content-Length: %d\r\n\r\n", index);
  printf("Sending-> %.*s", header_len, content_buf);
  printf("%.*s\n", index, buf);

  write(pipe[1], content_buf, header_len);
  write(pipe[1], buf, index);
}

int main(int argc, char *argv[]) {
    int in[2], out[2], n, pid;
    char buf[1024*4];

    if (argc < 2) {
      perror("Expected path to lsp server");
    }

    /* In a pipe, xx[0] is for reading, xx[1] is for writing */
    if (pipe(in) < 0) error("pipe in");
    if (pipe(out) < 0) error("pipe out");

    if ((pid=fork()) == 0) {
      /* This is the child process */

      /* Close stdin, stdout, stderr */
      close(0);
      close(1);
      //close(2);
      /* make our pipes, our new stdin,stdout and stderr */
      dup2(in[0],0);
      dup2(out[1],1);
      //dup2(out[1],2);

      /* Close the other ends of the pipes that the parent will use, because if
       * we leave these open in the child, the child/parent will not get an EOF
       * when the parent/child closes their end of the pipe.
       */
      close(in[1]);
      close(out[0]);

      /* Over-write the child process with the hexdump binary */
      execl(argv[1], "rust-analyzer", (char *)NULL);
      error("Could not exec lsp server");
      return 1;
    }

    printf("Spawned '%s' as a child process at pid %d\n", argv[1], pid);

    /* This is the parent process */
    /* Close the pipe ends that the child uses to read from / write to so
     * the when we close the others, an EOF will be transmitted properly.
     */
    close(in[0]);
    close(out[1]);

    Arena json_arena = new_arena(sizeof(char)*1024*1024);
    jsmn_parser p;
    jsmntok_t tokens[12000];

    send_initialize_message(&json_arena, argv[2], in);
    //write(in[1], data, strlen(data));
    //sleep(2);


    printf("Waiting for server message\n");
    Reader r = init_reader(&json_arena, out[0]);
    ReadResult result = jrpc_read(&r);
    printf("result from jrpc_read %d\n", result.status);
    switch(result.status) {
      case READ_EOF:
        fprintf(stderr, "Got eof while reading from server\n");
        exit(1);
        break;
      case READ_MSG_IN_FLIGHT:
        fprintf(stderr, "Message still in flight from server\n");
        exit(1);
        break;
      case READ_OK:
        //printf("Message: %.*s\n", result.length, result.buf);
        break;
    }

    int jsmn_result;
    jsmn_init(&p);
    if ((jsmn_result = jsmn_parse(&p, result.buf, result.length, tokens, 12000)) < 0) {
        fprintf(stderr, "JSON parse error: jsmn_parse: %d\n", jsmn_result);
        exit(1);
    }

    unsigned int index = 0;
    InitializeResponse response = parse_json_InitializeResponse(&json_arena, result.buf, tokens, &index);

    printf("\n\nserver name: %.*s\n", response.result.serverInfo.name.length, response.result.serverInfo.name.text);
    printf("server version: %.*s\n", response.result.serverInfo.version.length, response.result.serverInfo.version.text);

    send_initialized_notification(&json_arena, in);

    // ------------------------------
    send_did_open_text_document_notification(&json_arena, argv[3], in);
    printf("sent open text document notification\n");
    send_document_symbols_message(&json_arena, argv[3], in);

    //while(true) {
      printf("Waiting for server message\n");
      r = init_reader(&json_arena, out[0]);
      result = jrpc_read(&r);
      printf("result from jrpc_read %d\n", result.status);
      switch(result.status) {
        case READ_EOF:
          printf("Got eof while reading from server\n");
          exit(1);
          break;
        case READ_MSG_IN_FLIGHT:
          printf("Message still in flight from server\n");
          exit(1);
          break;
        case READ_OK:
          printf("Message: %.*s\n", result.length, result.buf);
          break;
      }
    //}

    
    jsmn_init(&p);
    if ((jsmn_result = jsmn_parse(&p, result.buf, result.length, tokens, 12000)) < 0) {
        fprintf(stderr, "JSON parse error: jsmn_parse: %d\n", jsmn_result);
        exit(1);
    }

    index = 0;
    DocumentSymbolsResponse symbols = parse_json_DocumentSymbolsResponse(&json_arena, result.buf, tokens, &index);

    for (int i=0;i<symbols.count;++i) {
      SymbolInformation *si = &symbols.result[i];
      printf("Name: %.*s\n", si->name.length, si->name.text);
      // printf("Start: Line: %ld, Col: %ld\n", si->location.range.start.line, si->location.range.start.character);
      // printf("End: Line: %ld, Col: %ld\n", si->location.range.end.line, si->location.range.end.character);
    }

    send_shutdown_message(&json_arena, in);
    send_exit_message(&json_arena, in);

    /*
    ServerMessage msg = (ServerMessage) { 0, 0, 1024*4, buf };
    MessageResult result;
    while((result = read_server_message(out, &msg))) {
        if (result == MSG_SUCCESS) {
            break;
        }

        printf("server message in-flight, trying read again...\n");
    }
    printf("Got EOF from server\n");
    

    jsmn_init(&p);
    int r = jsmn_parse(&p, msg.buf+msg.body_offset, msg.content_length, tokens, 2048);

    if (r < 0) {
        fprintf(stderr, "JSON parse error: jsmn_parse: %d\n", r);
        exit(1);
    }

    unsigned int index = 0;
    InitializeResponse response = parse_json_InitializeResponse(&json_arena, msg.buf+msg.body_offset, tokens, &index);

    printf("\n\nserver name: %.*s\n", response.result.serverInfo.name.length, response.result.serverInfo.name.text);
    printf("server version: %.*s\n", response.result.serverInfo.version.length, response.result.serverInfo.version.text);

    if (true) {
      printf("\nsending shutdown request...\n");
      send_shutdown_message(in);

      //sleep(2);

      printf("Waiting for server message\n");
      while((result = read_server_message(out, &msg))) {
        if (result == MSG_SUCCESS) {
          break;
        }

        printf("server message in-flight, trying read again...\n");
      }

      if (result == MSG_EOF) {
        printf("Got EOF from server\n");
      } else {

        jsmn_init(&p);
        int r = jsmn_parse(&p, msg.buf+msg.body_offset, msg.content_length, tokens, 2048);

        if (r < 0) {
          fprintf(stderr, "JSON parse error: jsmn_parse: %d\n", r);
          exit(1);
        }

        unsigned int index = 0;
        ShutdownResponse response = parse_json_ShutdownResponse(&json_arena, msg.buf+msg.body_offset, tokens, &index);
      }

      send_exit_message(in);

      printf("Waiting for server message\n");
      while((result = read_server_message(out, &msg))) {
        if (result == MSG_SUCCESS) {
          break;
        }

        printf("server message in-flight, trying read again...\n");
      }

      if (result == MSG_EOF) {
        printf("Got EOF from server\n");
      }
      jsmn_init(&p);
      int r = jsmn_parse(&p, msg.buf+msg.body_offset, msg.content_length, tokens, 2048);
      unsigned int index = 0;
      ShutdownResponse response = parse_json_ShutdownResponse(&json_arena, msg.buf+msg.body_offset, tokens, &index);

      printf("ERROR: code: %ld, message: %.*s\n", response.error.code, response.error.message.length, response.error.message.text);
    }
    */
    
    close(in[1]);

    return 0;
}

void error(char *s)
{
    perror(s);
    exit(1);
}
