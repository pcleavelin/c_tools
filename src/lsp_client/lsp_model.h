// DO NOT EDIT - This file was automatically generated

#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <jsmn.h>
#include <better_structs/json.h>

static void json_skip_object(const char *json, const jsmntok_t *tokens, unsigned int *index, bool is_array) {
    const int num_children = tokens[*index].size;
    // if the object was empty
    if (num_children == 0) {
        *index += 1;
        return;
    }
    // move into the object
    *index += 1;
    for (int i=0; i<num_children; i++) {
        // Look at the field value
        if (!is_array) {
            *index += 1;
        }
        if (tokens[*index].type == JSMN_OBJECT || tokens[*index].type == JSMN_ARRAY) {
            json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);
        } else {
            *index += 1;
        }
    }
}
typedef struct LspTextDocument {
    JsonString uri;
} LspTextDocument;
GenerateOptionType(LspTextDocument);
LspTextDocument parse_json_LspTextDocument(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspTextDocument new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "uri", 3) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            num_parsed_fields += 1;
            new_struct.uri = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            *index += 1;
        }
        else if (tokens[*index+1].type == JSMN_OBJECT || tokens[*index+1].type == JSMN_ARRAY) {
            *index += 1;
            json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);
        } else {
            *index += 2;
        }
    }

    if (num_parsed_fields != 1) {
        fprintf(stderr, "JSON parse error: Expected 1 fields, got %ld\n", num_parsed_fields);
    }

    return new_struct;
}
void serialize_json_LspTextDocument(Arena *arena, LspTextDocument *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_string_field(arena, buf, buf_size, index, "uri", data->uri, false);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}
GenerateOptionStructSerializeFunc(serialize_json_LspTextDocument, LspTextDocument);

typedef struct LspDocumentSymbolsParams {
    LspTextDocument textDocument;
} LspDocumentSymbolsParams;
GenerateOptionType(LspDocumentSymbolsParams);
LspDocumentSymbolsParams parse_json_LspDocumentSymbolsParams(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspDocumentSymbolsParams new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "textDocument", 12) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.textDocument = parse_json_LspTextDocument(arena, json, tokens, index);
            num_parsed_fields += 1;
        }
        else if (tokens[*index+1].type == JSMN_OBJECT || tokens[*index+1].type == JSMN_ARRAY) {
            *index += 1;
            json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);
        } else {
            *index += 2;
        }
    }

    if (num_parsed_fields != 1) {
        fprintf(stderr, "JSON parse error: Expected 1 fields, got %ld\n", num_parsed_fields);
    }

    return new_struct;
}
void serialize_json_LspDocumentSymbolsParams(Arena *arena, LspDocumentSymbolsParams *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    *index += snprintf(buf + *index, buf_size - *index, "\"textDocument\":");
    serialize_json_LspTextDocument(arena, &data->textDocument, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}
GenerateOptionStructSerializeFunc(serialize_json_LspDocumentSymbolsParams, LspDocumentSymbolsParams);

typedef struct LspPosition {
    long line;
    long character;
} LspPosition;
GenerateOptionType(LspPosition);
LspPosition parse_json_LspPosition(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspPosition new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "line", 4) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            long value = 0;
            errno = 0;
            value = strtol(json + tokens[*index].start, 0, 10);
            if (errno != 0 && value == 0) {
                fprintf(stderr, "JSON parse error: errno!=0: Expected json type 'i32'\n");
                exit(1);
            } else if (value == LONG_MIN || value == LONG_MAX) {
                fprintf(stderr, "JSON parse error: value==MAX: Expected json type 'i32'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.line = value;
        }
        else if (is_jsoneq(json, &tokens[*index], "character", 9) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            long value = 0;
            errno = 0;
            value = strtol(json + tokens[*index].start, 0, 10);
            if (errno != 0 && value == 0) {
                fprintf(stderr, "JSON parse error: errno!=0: Expected json type 'i32'\n");
                exit(1);
            } else if (value == LONG_MIN || value == LONG_MAX) {
                fprintf(stderr, "JSON parse error: value==MAX: Expected json type 'i32'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.character = value;
        }
        else if (tokens[*index+1].type == JSMN_OBJECT || tokens[*index+1].type == JSMN_ARRAY) {
            *index += 1;
            json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);
        } else {
            *index += 2;
        }
    }

    if (num_parsed_fields != 2) {
        fprintf(stderr, "JSON parse error: Expected 2 fields, got %ld\n", num_parsed_fields);
    }

    return new_struct;
}
void serialize_json_LspPosition(Arena *arena, LspPosition *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_integer_field(arena, buf, buf_size, index, "line", data->line, false);
    serialize_integer_field(arena, buf, buf_size, index, "character", data->character, true);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}
GenerateOptionStructSerializeFunc(serialize_json_LspPosition, LspPosition);

typedef struct LspRange {
    LspPosition start;
    LspPosition end;
} LspRange;
GenerateOptionType(LspRange);
LspRange parse_json_LspRange(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspRange new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "start", 5) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.start = parse_json_LspPosition(arena, json, tokens, index);
            num_parsed_fields += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "end", 3) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.end = parse_json_LspPosition(arena, json, tokens, index);
            num_parsed_fields += 1;
        }
        else if (tokens[*index+1].type == JSMN_OBJECT || tokens[*index+1].type == JSMN_ARRAY) {
            *index += 1;
            json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);
        } else {
            *index += 2;
        }
    }

    if (num_parsed_fields != 2) {
        fprintf(stderr, "JSON parse error: Expected 2 fields, got %ld\n", num_parsed_fields);
    }

    return new_struct;
}
void serialize_json_LspRange(Arena *arena, LspRange *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    *index += snprintf(buf + *index, buf_size - *index, "\"start\":");
    serialize_json_LspPosition(arena, &data->start, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, ",\"end\":");
    serialize_json_LspPosition(arena, &data->end, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}
GenerateOptionStructSerializeFunc(serialize_json_LspRange, LspRange);

typedef struct LspLocation {
    JsonString uri;
    LspRange range;
} LspLocation;
GenerateOptionType(LspLocation);
LspLocation parse_json_LspLocation(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspLocation new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "uri", 3) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            num_parsed_fields += 1;
            new_struct.uri = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            *index += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "range", 5) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.range = parse_json_LspRange(arena, json, tokens, index);
            num_parsed_fields += 1;
        }
        else if (tokens[*index+1].type == JSMN_OBJECT || tokens[*index+1].type == JSMN_ARRAY) {
            *index += 1;
            json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);
        } else {
            *index += 2;
        }
    }

    if (num_parsed_fields != 2) {
        fprintf(stderr, "JSON parse error: Expected 2 fields, got %ld\n", num_parsed_fields);
    }

    return new_struct;
}
void serialize_json_LspLocation(Arena *arena, LspLocation *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_string_field(arena, buf, buf_size, index, "uri", data->uri, false);
    *index += snprintf(buf + *index, buf_size - *index, ",\"range\":");
    serialize_json_LspRange(arena, &data->range, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}
GenerateOptionStructSerializeFunc(serialize_json_LspLocation, LspLocation);

typedef struct LspSymbolInformation {
    JsonString name;
    long kind;
    LspLocation location;
} LspSymbolInformation;
GenerateOptionType(LspSymbolInformation);
LspSymbolInformation parse_json_LspSymbolInformation(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspSymbolInformation new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "name", 4) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            num_parsed_fields += 1;
            new_struct.name = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            *index += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "kind", 4) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            long value = 0;
            errno = 0;
            value = strtol(json + tokens[*index].start, 0, 10);
            if (errno != 0 && value == 0) {
                fprintf(stderr, "JSON parse error: errno!=0: Expected json type 'i32'\n");
                exit(1);
            } else if (value == LONG_MIN || value == LONG_MAX) {
                fprintf(stderr, "JSON parse error: value==MAX: Expected json type 'i32'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.kind = value;
        }
        else if (is_jsoneq(json, &tokens[*index], "location", 8) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.location = parse_json_LspLocation(arena, json, tokens, index);
            num_parsed_fields += 1;
        }
        else if (tokens[*index+1].type == JSMN_OBJECT || tokens[*index+1].type == JSMN_ARRAY) {
            *index += 1;
            json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);
        } else {
            *index += 2;
        }
    }

    if (num_parsed_fields != 3) {
        fprintf(stderr, "JSON parse error: Expected 3 fields, got %ld\n", num_parsed_fields);
    }

    return new_struct;
}
void serialize_json_LspSymbolInformation(Arena *arena, LspSymbolInformation *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_string_field(arena, buf, buf_size, index, "name", data->name, false);
    serialize_integer_field(arena, buf, buf_size, index, "kind", data->kind, true);
    *index += snprintf(buf + *index, buf_size - *index, ",\"location\":");
    serialize_json_LspLocation(arena, &data->location, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}
GenerateOptionStructSerializeFunc(serialize_json_LspSymbolInformation, LspSymbolInformation);

typedef struct LspDocumentSymbolsResponse {
    long count;
    LspSymbolInformation * result;
} LspDocumentSymbolsResponse;
GenerateOptionType(LspDocumentSymbolsResponse);
LspDocumentSymbolsResponse parse_json_LspDocumentSymbolsResponse(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspDocumentSymbolsResponse new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "result", 6) && tokens[*index+1].type == JSMN_ARRAY) {
            const int array_size = tokens[*index+1].size;
            *index += 2;
            new_struct.result = arena_allocate_block(arena, sizeof(LspSymbolInformation) * array_size);
            new_struct.count = array_size;
            for (int i=0;i<array_size;i++) {
                if(tokens[*index].type == JSMN_OBJECT) {
                    new_struct.result[i] = parse_json_LspSymbolInformation(arena, json, tokens, index);
                } else {
                    fprintf(stderr, "JSON parse error: Expected json type 'LspSymbolInformation' in array 'result'\n");
                    exit(1);
                }
            }
            num_parsed_fields += 1;
        }
        else if (tokens[*index+1].type == JSMN_OBJECT || tokens[*index+1].type == JSMN_ARRAY) {
            *index += 1;
            json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);
        } else {
            *index += 2;
        }
    }

    if (num_parsed_fields != 1) {
        fprintf(stderr, "JSON parse error: Expected 1 fields, got %ld\n", num_parsed_fields);
    }

    return new_struct;
}
void serialize_json_LspDocumentSymbolsResponse(Arena *arena, LspDocumentSymbolsResponse *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    *index += snprintf(buf + *index, buf_size - *index, "\"result\":[");
    for(int i=0;i<data->count;i++) {
        serialize_json_LspSymbolInformation(arena, &data->result[i], buf, buf_size, index);
    }
    *index += snprintf(buf + *index, buf_size - *index, "]");
    *index += snprintf(buf + *index, buf_size - *index, "}");
}
GenerateOptionStructSerializeFunc(serialize_json_LspDocumentSymbolsResponse, LspDocumentSymbolsResponse);

typedef struct LspTextDocumentItem {
    JsonString uri;
    JsonString languageId;
    long version;
    JsonString text;
} LspTextDocumentItem;
GenerateOptionType(LspTextDocumentItem);
LspTextDocumentItem parse_json_LspTextDocumentItem(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspTextDocumentItem new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "uri", 3) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            num_parsed_fields += 1;
            new_struct.uri = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            *index += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "languageId", 10) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            num_parsed_fields += 1;
            new_struct.languageId = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            *index += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "version", 7) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            long value = 0;
            errno = 0;
            value = strtol(json + tokens[*index].start, 0, 10);
            if (errno != 0 && value == 0) {
                fprintf(stderr, "JSON parse error: errno!=0: Expected json type 'i32'\n");
                exit(1);
            } else if (value == LONG_MIN || value == LONG_MAX) {
                fprintf(stderr, "JSON parse error: value==MAX: Expected json type 'i32'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.version = value;
        }
        else if (is_jsoneq(json, &tokens[*index], "text", 4) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            num_parsed_fields += 1;
            new_struct.text = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            *index += 1;
        }
        else if (tokens[*index+1].type == JSMN_OBJECT || tokens[*index+1].type == JSMN_ARRAY) {
            *index += 1;
            json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);
        } else {
            *index += 2;
        }
    }

    if (num_parsed_fields != 4) {
        fprintf(stderr, "JSON parse error: Expected 4 fields, got %ld\n", num_parsed_fields);
    }

    return new_struct;
}
void serialize_json_LspTextDocumentItem(Arena *arena, LspTextDocumentItem *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_string_field(arena, buf, buf_size, index, "uri", data->uri, false);
    serialize_string_field(arena, buf, buf_size, index, "languageId", data->languageId, true);
    serialize_integer_field(arena, buf, buf_size, index, "version", data->version, true);
    serialize_string_field(arena, buf, buf_size, index, "text", data->text, true);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}
GenerateOptionStructSerializeFunc(serialize_json_LspTextDocumentItem, LspTextDocumentItem);

typedef struct LspDidOpenTextDocumentParams {
    LspTextDocumentItem textDocument;
} LspDidOpenTextDocumentParams;
GenerateOptionType(LspDidOpenTextDocumentParams);
LspDidOpenTextDocumentParams parse_json_LspDidOpenTextDocumentParams(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspDidOpenTextDocumentParams new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "textDocument", 12) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.textDocument = parse_json_LspTextDocumentItem(arena, json, tokens, index);
            num_parsed_fields += 1;
        }
        else if (tokens[*index+1].type == JSMN_OBJECT || tokens[*index+1].type == JSMN_ARRAY) {
            *index += 1;
            json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);
        } else {
            *index += 2;
        }
    }

    if (num_parsed_fields != 1) {
        fprintf(stderr, "JSON parse error: Expected 1 fields, got %ld\n", num_parsed_fields);
    }

    return new_struct;
}
void serialize_json_LspDidOpenTextDocumentParams(Arena *arena, LspDidOpenTextDocumentParams *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    *index += snprintf(buf + *index, buf_size - *index, "\"textDocument\":");
    serialize_json_LspTextDocumentItem(arena, &data->textDocument, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}
GenerateOptionStructSerializeFunc(serialize_json_LspDidOpenTextDocumentParams, LspDidOpenTextDocumentParams);

typedef struct LspClientCapabilitiesWorkspace {
} LspClientCapabilitiesWorkspace;
GenerateOptionType(LspClientCapabilitiesWorkspace);
LspClientCapabilitiesWorkspace parse_json_LspClientCapabilitiesWorkspace(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspClientCapabilitiesWorkspace new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
 if (tokens[*index+1].type == JSMN_OBJECT || tokens[*index+1].type == JSMN_ARRAY) {
            *index += 1;
            json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);
        } else {
            *index += 2;
        }
    }

    if (num_parsed_fields != 0) {
        fprintf(stderr, "JSON parse error: Expected 0 fields, got %ld\n", num_parsed_fields);
    }

    return new_struct;
}
void serialize_json_LspClientCapabilitiesWorkspace(Arena *arena, LspClientCapabilitiesWorkspace *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    *index += snprintf(buf + *index, buf_size - *index, "}");
}
GenerateOptionStructSerializeFunc(serialize_json_LspClientCapabilitiesWorkspace, LspClientCapabilitiesWorkspace);

typedef struct LspClientCapabilities {
    Option(LspClientCapabilitiesWorkspace) workspace;
} LspClientCapabilities;
GenerateOptionType(LspClientCapabilities);
LspClientCapabilities parse_json_LspClientCapabilities(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspClientCapabilities new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "workspace", 9) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.workspace = Some(LspClientCapabilitiesWorkspace, parse_json_LspClientCapabilitiesWorkspace(arena, json, tokens, index));
            num_parsed_fields += 1;
        }
        else if (tokens[*index+1].type == JSMN_OBJECT || tokens[*index+1].type == JSMN_ARRAY) {
            *index += 1;
            json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);
        } else {
            *index += 2;
        }
    }

    if (num_parsed_fields != 1) {
        fprintf(stderr, "JSON parse error: Expected 1 fields, got %ld\n", num_parsed_fields);
    }

    return new_struct;
}
void serialize_json_LspClientCapabilities(Arena *arena, LspClientCapabilities *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    *index += snprintf(buf + *index, buf_size - *index, "\"workspace\":");
    serialize_json_LspClientCapabilitiesWorkspace_optional(arena, &data->workspace, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}
GenerateOptionStructSerializeFunc(serialize_json_LspClientCapabilities, LspClientCapabilities);

typedef struct LspInitializeRequestParams {
    LspClientCapabilities capabilities;
    Option(JsonString) rootUri;
    long processId;
} LspInitializeRequestParams;
GenerateOptionType(LspInitializeRequestParams);
LspInitializeRequestParams parse_json_LspInitializeRequestParams(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspInitializeRequestParams new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "capabilities", 12) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.capabilities = parse_json_LspClientCapabilities(arena, json, tokens, index);
            num_parsed_fields += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "rootUri", 7) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            num_parsed_fields += 1;
            new_struct.rootUri = Some(JsonString, ((JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start }));
            *index += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "processId", 9) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            long value = 0;
            errno = 0;
            value = strtol(json + tokens[*index].start, 0, 10);
            if (errno != 0 && value == 0) {
                fprintf(stderr, "JSON parse error: errno!=0: Expected json type 'i32'\n");
                exit(1);
            } else if (value == LONG_MIN || value == LONG_MAX) {
                fprintf(stderr, "JSON parse error: value==MAX: Expected json type 'i32'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.processId = value;
        }
        else if (tokens[*index+1].type == JSMN_OBJECT || tokens[*index+1].type == JSMN_ARRAY) {
            *index += 1;
            json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);
        } else {
            *index += 2;
        }
    }

    if (num_parsed_fields != 3) {
        fprintf(stderr, "JSON parse error: Expected 3 fields, got %ld\n", num_parsed_fields);
    }

    return new_struct;
}
void serialize_json_LspInitializeRequestParams(Arena *arena, LspInitializeRequestParams *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    *index += snprintf(buf + *index, buf_size - *index, "\"capabilities\":");
    serialize_json_LspClientCapabilities(arena, &data->capabilities, buf, buf_size, index);
    serialize_string_field_optional(arena, buf, buf_size, index, "rootUri", data->rootUri, true);
    serialize_integer_field(arena, buf, buf_size, index, "processId", data->processId, true);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}
GenerateOptionStructSerializeFunc(serialize_json_LspInitializeRequestParams, LspInitializeRequestParams);

typedef enum LspRequestMethodVariant {
    LspRequestMethod_Initialize,
    LspRequestMethod_Initialized,
    LspRequestMethod_Shutdown,
    LspRequestMethod_Exit,
    LspRequestMethod_OpenFile,
    LspRequestMethod_GetDocumentSymbols,
} LspRequestMethodVariant;
typedef struct LspRequestMethod {
    LspRequestMethodVariant type;
    union {
    LspInitializeRequestParams Initialize;
    LspDidOpenTextDocumentParams OpenFile;
    LspDocumentSymbolsParams GetDocumentSymbols;
    };
} LspRequestMethod;
GenerateOptionType(LspRequestMethod);
LspRequestMethod parse_json_LspRequestMethod(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {}
void serialize_json_LspRequestMethod(Arena *arena, LspRequestMethod *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    switch (data->type) {
        case LspRequestMethod_Initialize:
    serialize_json_LspInitializeRequestParams(arena, &data->Initialize, buf, buf_size, index);
            *index += snprintf(buf + *index, buf_size - *index, ",\"method\": \"initialize\"");
    break;
        case LspRequestMethod_Initialized:
            *index += snprintf(buf + *index, buf_size - *index, "null");
            *index += snprintf(buf + *index, buf_size - *index, ",\"method\": \"initialized\"");
    break;
        case LspRequestMethod_Shutdown:
            *index += snprintf(buf + *index, buf_size - *index, "null");
            *index += snprintf(buf + *index, buf_size - *index, ",\"method\": \"shutdown\"");
    break;
        case LspRequestMethod_Exit:
            *index += snprintf(buf + *index, buf_size - *index, "null");
            *index += snprintf(buf + *index, buf_size - *index, ",\"method\": \"exit\"");
    break;
        case LspRequestMethod_OpenFile:
    serialize_json_LspDidOpenTextDocumentParams(arena, &data->OpenFile, buf, buf_size, index);
            *index += snprintf(buf + *index, buf_size - *index, ",\"method\": \"textDocument/didOpen\"");
    break;
        case LspRequestMethod_GetDocumentSymbols:
    serialize_json_LspDocumentSymbolsParams(arena, &data->GetDocumentSymbols, buf, buf_size, index);
            *index += snprintf(buf + *index, buf_size - *index, ",\"method\": \"textDocument/documentSymbol\"");
    break;
    }
}
GenerateOptionStructSerializeFunc(serialize_json_LspRequestMethod, LspRequestMethod);

typedef enum LspNotificationMethodVariant {
    LspNotificationMethod_Initialized,
    LspNotificationMethod_Exit,
    LspNotificationMethod_OpenFile,
} LspNotificationMethodVariant;
typedef struct LspNotificationMethod {
    LspNotificationMethodVariant type;
    union {
    LspDidOpenTextDocumentParams OpenFile;
    };
} LspNotificationMethod;
GenerateOptionType(LspNotificationMethod);
LspNotificationMethod parse_json_LspNotificationMethod(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {}
void serialize_json_LspNotificationMethod(Arena *arena, LspNotificationMethod *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    switch (data->type) {
        case LspNotificationMethod_Initialized:
            *index += snprintf(buf + *index, buf_size - *index, "null");
            *index += snprintf(buf + *index, buf_size - *index, ",\"method\": \"initialized\"");
    break;
        case LspNotificationMethod_Exit:
            *index += snprintf(buf + *index, buf_size - *index, "null");
            *index += snprintf(buf + *index, buf_size - *index, ",\"method\": \"exit\"");
    break;
        case LspNotificationMethod_OpenFile:
    serialize_json_LspDidOpenTextDocumentParams(arena, &data->OpenFile, buf, buf_size, index);
            *index += snprintf(buf + *index, buf_size - *index, ",\"method\": \"textDocument/didOpen\"");
    break;
    }
}
GenerateOptionStructSerializeFunc(serialize_json_LspNotificationMethod, LspNotificationMethod);

typedef struct LspRequest {
    long id;
    JsonString jsonrpc;
    LspRequestMethod params;
} LspRequest;
GenerateOptionType(LspRequest);
LspRequest parse_json_LspRequest(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspRequest new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "id", 2) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            long value = 0;
            errno = 0;
            value = strtol(json + tokens[*index].start, 0, 10);
            if (errno != 0 && value == 0) {
                fprintf(stderr, "JSON parse error: errno!=0: Expected json type 'i32'\n");
                exit(1);
            } else if (value == LONG_MIN || value == LONG_MAX) {
                fprintf(stderr, "JSON parse error: value==MAX: Expected json type 'i32'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.id = value;
        }
        else if (is_jsoneq(json, &tokens[*index], "jsonrpc", 7) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            num_parsed_fields += 1;
            new_struct.jsonrpc = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            *index += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "params", 6) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.params = parse_json_LspRequestMethod(arena, json, tokens, index);
            num_parsed_fields += 1;
        }
        else if (tokens[*index+1].type == JSMN_OBJECT || tokens[*index+1].type == JSMN_ARRAY) {
            *index += 1;
            json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);
        } else {
            *index += 2;
        }
    }

    if (num_parsed_fields != 3) {
        fprintf(stderr, "JSON parse error: Expected 3 fields, got %ld\n", num_parsed_fields);
    }

    return new_struct;
}
void serialize_json_LspRequest(Arena *arena, LspRequest *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_integer_field(arena, buf, buf_size, index, "id", data->id, false);
    serialize_string_field(arena, buf, buf_size, index, "jsonrpc", data->jsonrpc, true);
    *index += snprintf(buf + *index, buf_size - *index, ",\"params\":");
    serialize_json_LspRequestMethod(arena, &data->params, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}
GenerateOptionStructSerializeFunc(serialize_json_LspRequest, LspRequest);

typedef struct LspNotification {
    JsonString jsonrpc;
    LspNotificationMethod params;
} LspNotification;
GenerateOptionType(LspNotification);
LspNotification parse_json_LspNotification(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspNotification new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "jsonrpc", 7) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            num_parsed_fields += 1;
            new_struct.jsonrpc = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            *index += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "params", 6) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.params = parse_json_LspNotificationMethod(arena, json, tokens, index);
            num_parsed_fields += 1;
        }
        else if (tokens[*index+1].type == JSMN_OBJECT || tokens[*index+1].type == JSMN_ARRAY) {
            *index += 1;
            json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);
        } else {
            *index += 2;
        }
    }

    if (num_parsed_fields != 2) {
        fprintf(stderr, "JSON parse error: Expected 2 fields, got %ld\n", num_parsed_fields);
    }

    return new_struct;
}
void serialize_json_LspNotification(Arena *arena, LspNotification *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_string_field(arena, buf, buf_size, index, "jsonrpc", data->jsonrpc, false);
    *index += snprintf(buf + *index, buf_size - *index, ",\"params\":");
    serialize_json_LspNotificationMethod(arena, &data->params, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}
GenerateOptionStructSerializeFunc(serialize_json_LspNotification, LspNotification);

typedef struct LspServerInfo {
    JsonString name;
    JsonString version;
} LspServerInfo;
GenerateOptionType(LspServerInfo);
LspServerInfo parse_json_LspServerInfo(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspServerInfo new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "name", 4) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            num_parsed_fields += 1;
            new_struct.name = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            *index += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "version", 7) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            num_parsed_fields += 1;
            new_struct.version = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            *index += 1;
        }
        else if (tokens[*index+1].type == JSMN_OBJECT || tokens[*index+1].type == JSMN_ARRAY) {
            *index += 1;
            json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);
        } else {
            *index += 2;
        }
    }

    if (num_parsed_fields != 2) {
        fprintf(stderr, "JSON parse error: Expected 2 fields, got %ld\n", num_parsed_fields);
    }

    return new_struct;
}
void serialize_json_LspServerInfo(Arena *arena, LspServerInfo *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_string_field(arena, buf, buf_size, index, "name", data->name, false);
    serialize_string_field(arena, buf, buf_size, index, "version", data->version, true);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}
GenerateOptionStructSerializeFunc(serialize_json_LspServerInfo, LspServerInfo);

typedef struct LspCapabilities {
} LspCapabilities;
GenerateOptionType(LspCapabilities);
LspCapabilities parse_json_LspCapabilities(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspCapabilities new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
 if (tokens[*index+1].type == JSMN_OBJECT || tokens[*index+1].type == JSMN_ARRAY) {
            *index += 1;
            json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);
        } else {
            *index += 2;
        }
    }

    if (num_parsed_fields != 0) {
        fprintf(stderr, "JSON parse error: Expected 0 fields, got %ld\n", num_parsed_fields);
    }

    return new_struct;
}
void serialize_json_LspCapabilities(Arena *arena, LspCapabilities *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    *index += snprintf(buf + *index, buf_size - *index, "}");
}
GenerateOptionStructSerializeFunc(serialize_json_LspCapabilities, LspCapabilities);

typedef struct LspInitializeResult {
    LspCapabilities capabilities;
    LspServerInfo serverInfo;
} LspInitializeResult;
GenerateOptionType(LspInitializeResult);
LspInitializeResult parse_json_LspInitializeResult(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspInitializeResult new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "capabilities", 12) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.capabilities = parse_json_LspCapabilities(arena, json, tokens, index);
            num_parsed_fields += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "serverInfo", 10) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.serverInfo = parse_json_LspServerInfo(arena, json, tokens, index);
            num_parsed_fields += 1;
        }
        else if (tokens[*index+1].type == JSMN_OBJECT || tokens[*index+1].type == JSMN_ARRAY) {
            *index += 1;
            json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);
        } else {
            *index += 2;
        }
    }

    if (num_parsed_fields != 2) {
        fprintf(stderr, "JSON parse error: Expected 2 fields, got %ld\n", num_parsed_fields);
    }

    return new_struct;
}
void serialize_json_LspInitializeResult(Arena *arena, LspInitializeResult *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    *index += snprintf(buf + *index, buf_size - *index, "\"capabilities\":");
    serialize_json_LspCapabilities(arena, &data->capabilities, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, ",\"serverInfo\":");
    serialize_json_LspServerInfo(arena, &data->serverInfo, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}
GenerateOptionStructSerializeFunc(serialize_json_LspInitializeResult, LspInitializeResult);

typedef struct LspInitializeResponse {
    long id;
    JsonString jsonrpc;
    LspInitializeResult result;
} LspInitializeResponse;
GenerateOptionType(LspInitializeResponse);
LspInitializeResponse parse_json_LspInitializeResponse(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspInitializeResponse new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "id", 2) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            long value = 0;
            errno = 0;
            value = strtol(json + tokens[*index].start, 0, 10);
            if (errno != 0 && value == 0) {
                fprintf(stderr, "JSON parse error: errno!=0: Expected json type 'i32'\n");
                exit(1);
            } else if (value == LONG_MIN || value == LONG_MAX) {
                fprintf(stderr, "JSON parse error: value==MAX: Expected json type 'i32'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.id = value;
        }
        else if (is_jsoneq(json, &tokens[*index], "jsonrpc", 7) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            num_parsed_fields += 1;
            new_struct.jsonrpc = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            *index += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "result", 6) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.result = parse_json_LspInitializeResult(arena, json, tokens, index);
            num_parsed_fields += 1;
        }
        else if (tokens[*index+1].type == JSMN_OBJECT || tokens[*index+1].type == JSMN_ARRAY) {
            *index += 1;
            json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);
        } else {
            *index += 2;
        }
    }

    if (num_parsed_fields != 3) {
        fprintf(stderr, "JSON parse error: Expected 3 fields, got %ld\n", num_parsed_fields);
    }

    return new_struct;
}
void serialize_json_LspInitializeResponse(Arena *arena, LspInitializeResponse *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_integer_field(arena, buf, buf_size, index, "id", data->id, false);
    serialize_string_field(arena, buf, buf_size, index, "jsonrpc", data->jsonrpc, true);
    *index += snprintf(buf + *index, buf_size - *index, ",\"result\":");
    serialize_json_LspInitializeResult(arena, &data->result, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}
GenerateOptionStructSerializeFunc(serialize_json_LspInitializeResponse, LspInitializeResponse);

