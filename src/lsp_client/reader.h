#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arena/arena.h>

typedef struct Reader {
  Arena *arena;
  int file_descriptor;

  int buf_start_offset;
  int buf_end_offset;
  char *buf;
} Reader;

typedef enum ReadStatus {
  READ_EOF,
  READ_MSG_IN_FLIGHT,
  READ_OK,
} ReadStatus;

typedef struct ReadResult {
  ReadStatus status;

  int length;
  char *buf;
} ReadResult;

ReadResult _read_eof() {
  return (ReadResult){READ_EOF, 0, NULL};
}
ReadResult _read_in_flight() {
  return (ReadResult){READ_MSG_IN_FLIGHT, 0, NULL};
}
ReadResult _read_ok(Reader *r, int length) {
  int start = r->buf_start_offset;
  r->buf_start_offset += length;

  // printf("read ok %d bytes: '%.*s'\n", length, length, r->buf+start);
  return (ReadResult){READ_OK, length, r->buf+start};
}

Reader init_reader(Arena *arena, int file_descriptor) {
  char *buf = (char *)arena_allocate_block(arena, 4096*2);

  return (Reader) {
    arena,
    file_descriptor,
    0,
    0,
    buf,
  };
}

void clear_reader(Reader *r) {
  r->buf_start_offset = 0;
  r->buf_end_offset = 0;
}

bool string_contains(const char *haystack, const int haystack_len, const char *needle, const int needle_len, int *offset) {
  while(*offset < haystack_len) {
    // printf("comparing '%.*s' with '%s'\n", needle_len, haystack+(*offset), needle);
    if (strncmp(haystack+(*offset), needle, needle_len) == 0) {
      return true;
    }

    *offset += 1;
  }

  return false;
}

ReadResult reader_read_exact(Reader *r, const size_t num_bytes) {
  while(true) {
    const size_t buf_len = r->buf_end_offset - r->buf_start_offset;
    if (buf_len >= num_bytes) {
      return _read_ok(r, num_bytes);
    }

    int bytes_read = read(r->file_descriptor, r->buf + r->buf_end_offset, 32);
    if (bytes_read == 0) return _read_eof();
    else if (bytes_read == -1 && errno == EAGAIN) return _read_in_flight();
    r->buf_end_offset += bytes_read;

    // printf("DEBUG: read %d bytes: %.*s\n", bytes_read, bytes_read, r->buf+r->buf_end_offset-bytes_read);
  }
}

ReadResult reader_read_until(Reader *r, const char *suffix) {
  bool matched = false;
  const size_t suffix_len = strlen(suffix);

  int compare_offset = 0;
  do {
    const int buf_len = r->buf_end_offset - r->buf_start_offset;
    compare_offset = 0;
    if (suffix_len <= buf_len) {
      matched = string_contains(r->buf + r->buf_start_offset, buf_len, suffix, suffix_len, &compare_offset);
    }

    if (matched) break;

    int bytes_read = read(r->file_descriptor, r->buf + r->buf_end_offset, 32);
    if (bytes_read == 0) return _read_eof();
    else if (bytes_read == -1 && errno == EAGAIN) return _read_in_flight();
    r->buf_end_offset += bytes_read;

    //printf("DEBUG: read %d bytes: %.*s\n", bytes_read, bytes_read, r->buf+r->buf_start_offset);
  } while(!matched);

  return _read_ok(r, compare_offset+suffix_len);
}

ReadResult jrpc_read(Reader *reader) {
  ReadResult result = reader_read_until(reader, "\r\n\r\n");
  if (result.status != READ_OK) return result;

  int content_length = 0;
  int body_offset = 0;
  // FIXME: probably bad as `result->buf` is not null-terminated
  sscanf(result.buf, "Content-Length: %d\r\n\r\n%n", &content_length, &body_offset);

  return reader_read_exact(reader, content_length);
}

