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
Option(LspTextDocument) parse_json_LspTextDocument(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index, unsigned int parent_index) {
    int this_index = *index;
    LspTextDocument new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "uri", 3) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            new_struct.uri = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            num_parsed_fields += 1;
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
        fprintf(stderr, "JSON parse error: Expected 1 fields, got %ld for LspTextDocument\n", num_parsed_fields);
        return None(LspTextDocument);
    }

    return Some(LspTextDocument, new_struct);
}
void serialize_json_LspTextDocument(Arena *arena, LspTextDocument *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_string_field(arena, buf, buf_size, index, "uri", data->uri, false);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}
GenerateOptionStructSerializeFunc(serialize_json_LspTextDocument, LspTextDocument);

typedef struct LspDocumentSymbolsParams {
    LspTextDocument document;
} LspDocumentSymbolsParams;
GenerateOptionType(LspDocumentSymbolsParams);
Option(LspDocumentSymbolsParams) parse_json_LspDocumentSymbolsParams(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index, unsigned int parent_index) {
    int this_index = *index;
    LspDocumentSymbolsParams new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "document", 8) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            Option(LspTextDocument) parsed_struct = parse_json_LspTextDocument(arena, json, tokens, index, this_index);
            if (is_none(parsed_struct)) {
                fprintf(stderr, "JSON Parse Error: failed to parse object LspTextDocument\n");
                return None(LspDocumentSymbolsParams);
            }
            new_struct.document = parsed_struct.value;
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
        fprintf(stderr, "JSON parse error: Expected 1 fields, got %ld for LspDocumentSymbolsParams\n", num_parsed_fields);
        return None(LspDocumentSymbolsParams);
    }

    return Some(LspDocumentSymbolsParams, new_struct);
}
void serialize_json_LspDocumentSymbolsParams(Arena *arena, LspDocumentSymbolsParams *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    *index += snprintf(buf + *index, buf_size - *index, "\"textDocument\":");
    serialize_json_LspTextDocument(arena, &data->document, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}
GenerateOptionStructSerializeFunc(serialize_json_LspDocumentSymbolsParams, LspDocumentSymbolsParams);

typedef struct LspTextDocumentItem {
    JsonString uri;
    JsonString language_id;
    long version;
    JsonString text;
} LspTextDocumentItem;
GenerateOptionType(LspTextDocumentItem);
Option(LspTextDocumentItem) parse_json_LspTextDocumentItem(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index, unsigned int parent_index) {
    int this_index = *index;
    LspTextDocumentItem new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "uri", 3) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            new_struct.uri = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            num_parsed_fields += 1;
            *index += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "language_id", 11) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            new_struct.language_id = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            num_parsed_fields += 1;
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
            new_struct.version = value;
            num_parsed_fields += 1;
    }
        else if (is_jsoneq(json, &tokens[*index], "text", 4) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            new_struct.text = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            num_parsed_fields += 1;
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
        fprintf(stderr, "JSON parse error: Expected 4 fields, got %ld for LspTextDocumentItem\n", num_parsed_fields);
        return None(LspTextDocumentItem);
    }

    return Some(LspTextDocumentItem, new_struct);
}
void serialize_json_LspTextDocumentItem(Arena *arena, LspTextDocumentItem *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_string_field(arena, buf, buf_size, index, "uri", data->uri, false);
    serialize_string_field(arena, buf, buf_size, index, "languageId", data->language_id, true);
    serialize_integer_field(arena, buf, buf_size, index, "version", data->version, true);
    serialize_string_field(arena, buf, buf_size, index, "text", data->text, true);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}
GenerateOptionStructSerializeFunc(serialize_json_LspTextDocumentItem, LspTextDocumentItem);

typedef struct LspDidOpenTextDocumentParams {
    LspTextDocumentItem document;
} LspDidOpenTextDocumentParams;
GenerateOptionType(LspDidOpenTextDocumentParams);
Option(LspDidOpenTextDocumentParams) parse_json_LspDidOpenTextDocumentParams(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index, unsigned int parent_index) {
    int this_index = *index;
    LspDidOpenTextDocumentParams new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "document", 8) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            Option(LspTextDocumentItem) parsed_struct = parse_json_LspTextDocumentItem(arena, json, tokens, index, this_index);
            if (is_none(parsed_struct)) {
                fprintf(stderr, "JSON Parse Error: failed to parse object LspTextDocumentItem\n");
                return None(LspDidOpenTextDocumentParams);
            }
            new_struct.document = parsed_struct.value;
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
        fprintf(stderr, "JSON parse error: Expected 1 fields, got %ld for LspDidOpenTextDocumentParams\n", num_parsed_fields);
        return None(LspDidOpenTextDocumentParams);
    }

    return Some(LspDidOpenTextDocumentParams, new_struct);
}
void serialize_json_LspDidOpenTextDocumentParams(Arena *arena, LspDidOpenTextDocumentParams *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    *index += snprintf(buf + *index, buf_size - *index, "\"textDocument\":");
    serialize_json_LspTextDocumentItem(arena, &data->document, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}
GenerateOptionStructSerializeFunc(serialize_json_LspDidOpenTextDocumentParams, LspDidOpenTextDocumentParams);

typedef struct LspClientCapabilitiesWorkspace {
} LspClientCapabilitiesWorkspace;
GenerateOptionType(LspClientCapabilitiesWorkspace);
Option(LspClientCapabilitiesWorkspace) parse_json_LspClientCapabilitiesWorkspace(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index, unsigned int parent_index) {
    int this_index = *index;
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
        fprintf(stderr, "JSON parse error: Expected 0 fields, got %ld for LspClientCapabilitiesWorkspace\n", num_parsed_fields);
        return None(LspClientCapabilitiesWorkspace);
    }

    return Some(LspClientCapabilitiesWorkspace, new_struct);
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
Option(LspClientCapabilities) parse_json_LspClientCapabilities(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index, unsigned int parent_index) {
    int this_index = *index;
    LspClientCapabilities new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "workspace", 9) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            Option(LspClientCapabilitiesWorkspace) parsed_struct = parse_json_LspClientCapabilitiesWorkspace(arena, json, tokens, index, this_index);
            if (is_none(parsed_struct)) {
                fprintf(stderr, "JSON Parse Error: failed to parse object LspClientCapabilitiesWorkspace\n");
                return None(LspClientCapabilities);
            }
            new_struct.workspace = parsed_struct;
        }
        else if (tokens[*index+1].type == JSMN_OBJECT || tokens[*index+1].type == JSMN_ARRAY) {
            *index += 1;
            json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);
        } else {
            *index += 2;
        }
    }

    if (num_parsed_fields != 0) {
        fprintf(stderr, "JSON parse error: Expected 0 fields, got %ld for LspClientCapabilities\n", num_parsed_fields);
        return None(LspClientCapabilities);
    }

    return Some(LspClientCapabilities, new_struct);
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
    Option(JsonString) root_uri;
    long process_id;
} LspInitializeRequestParams;
GenerateOptionType(LspInitializeRequestParams);
Option(LspInitializeRequestParams) parse_json_LspInitializeRequestParams(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index, unsigned int parent_index) {
    int this_index = *index;
    LspInitializeRequestParams new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "capabilities", 12) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            Option(LspClientCapabilities) parsed_struct = parse_json_LspClientCapabilities(arena, json, tokens, index, this_index);
            if (is_none(parsed_struct)) {
                fprintf(stderr, "JSON Parse Error: failed to parse object LspClientCapabilities\n");
                return None(LspInitializeRequestParams);
            }
            new_struct.capabilities = parsed_struct.value;
            num_parsed_fields += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "root_uri", 8) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            new_struct.root_uri = Some(JsonString, ((JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start }));
            *index += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "process_id", 10) && tokens[*index+1].type == JSMN_PRIMITIVE) {
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
            new_struct.process_id = value;
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
        fprintf(stderr, "JSON parse error: Expected 2 fields, got %ld for LspInitializeRequestParams\n", num_parsed_fields);
        return None(LspInitializeRequestParams);
    }

    return Some(LspInitializeRequestParams, new_struct);
}
void serialize_json_LspInitializeRequestParams(Arena *arena, LspInitializeRequestParams *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    *index += snprintf(buf + *index, buf_size - *index, "\"capabilities\":");
    serialize_json_LspClientCapabilities(arena, &data->capabilities, buf, buf_size, index);
    serialize_string_field_optional(arena, buf, buf_size, index, "rootUri", data->root_uri, true);
    serialize_integer_field(arena, buf, buf_size, index, "processId", data->process_id, true);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}
GenerateOptionStructSerializeFunc(serialize_json_LspInitializeRequestParams, LspInitializeRequestParams);

typedef struct LspPosition {
    long line;
    long character;
} LspPosition;
GenerateOptionType(LspPosition);
Option(LspPosition) parse_json_LspPosition(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index, unsigned int parent_index) {
    int this_index = *index;
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
            new_struct.line = value;
            num_parsed_fields += 1;
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
            new_struct.character = value;
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
        fprintf(stderr, "JSON parse error: Expected 2 fields, got %ld for LspPosition\n", num_parsed_fields);
        return None(LspPosition);
    }

    return Some(LspPosition, new_struct);
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
Option(LspRange) parse_json_LspRange(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index, unsigned int parent_index) {
    int this_index = *index;
    LspRange new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "start", 5) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            Option(LspPosition) parsed_struct = parse_json_LspPosition(arena, json, tokens, index, this_index);
            if (is_none(parsed_struct)) {
                fprintf(stderr, "JSON Parse Error: failed to parse object LspPosition\n");
                return None(LspRange);
            }
            new_struct.start = parsed_struct.value;
            num_parsed_fields += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "end", 3) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            Option(LspPosition) parsed_struct = parse_json_LspPosition(arena, json, tokens, index, this_index);
            if (is_none(parsed_struct)) {
                fprintf(stderr, "JSON Parse Error: failed to parse object LspPosition\n");
                return None(LspRange);
            }
            new_struct.end = parsed_struct.value;
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
        fprintf(stderr, "JSON parse error: Expected 2 fields, got %ld for LspRange\n", num_parsed_fields);
        return None(LspRange);
    }

    return Some(LspRange, new_struct);
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
Option(LspLocation) parse_json_LspLocation(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index, unsigned int parent_index) {
    int this_index = *index;
    LspLocation new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "uri", 3) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            new_struct.uri = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            num_parsed_fields += 1;
            *index += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "range", 5) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            Option(LspRange) parsed_struct = parse_json_LspRange(arena, json, tokens, index, this_index);
            if (is_none(parsed_struct)) {
                fprintf(stderr, "JSON Parse Error: failed to parse object LspRange\n");
                return None(LspLocation);
            }
            new_struct.range = parsed_struct.value;
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
        fprintf(stderr, "JSON parse error: Expected 2 fields, got %ld for LspLocation\n", num_parsed_fields);
        return None(LspLocation);
    }

    return Some(LspLocation, new_struct);
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
Option(LspSymbolInformation) parse_json_LspSymbolInformation(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index, unsigned int parent_index) {
    int this_index = *index;
    LspSymbolInformation new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "name", 4) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            new_struct.name = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            num_parsed_fields += 1;
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
            new_struct.kind = value;
            num_parsed_fields += 1;
    }
        else if (is_jsoneq(json, &tokens[*index], "location", 8) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            Option(LspLocation) parsed_struct = parse_json_LspLocation(arena, json, tokens, index, this_index);
            if (is_none(parsed_struct)) {
                fprintf(stderr, "JSON Parse Error: failed to parse object LspLocation\n");
                return None(LspSymbolInformation);
            }
            new_struct.location = parsed_struct.value;
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
        fprintf(stderr, "JSON parse error: Expected 3 fields, got %ld for LspSymbolInformation\n", num_parsed_fields);
        return None(LspSymbolInformation);
    }

    return Some(LspSymbolInformation, new_struct);
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
Option(LspDocumentSymbolsResponse) parse_json_LspDocumentSymbolsResponse(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index, unsigned int parent_index) {
    int this_index = *index;
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
                    Option(LspSymbolInformation) parsed_struct = parse_json_LspSymbolInformation(arena, json, tokens, index, this_index);
                    if (is_none(parsed_struct)) {
                        fprintf(stderr, "JSON Parse Error: failed to parse object LspSymbolInformation in array\n");
                        return None(LspDocumentSymbolsResponse);
                    }
                    new_struct.result[i] = parsed_struct.value;
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
        fprintf(stderr, "JSON parse error: Expected 1 fields, got %ld for LspDocumentSymbolsResponse\n", num_parsed_fields);
        return None(LspDocumentSymbolsResponse);
    }

    return Some(LspDocumentSymbolsResponse, new_struct);
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

typedef struct LspDiagnosticsParams {
} LspDiagnosticsParams;
GenerateOptionType(LspDiagnosticsParams);
Option(LspDiagnosticsParams) parse_json_LspDiagnosticsParams(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index, unsigned int parent_index) {
    int this_index = *index;
    LspDiagnosticsParams new_struct = {};
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
        fprintf(stderr, "JSON parse error: Expected 0 fields, got %ld for LspDiagnosticsParams\n", num_parsed_fields);
        return None(LspDiagnosticsParams);
    }

    return Some(LspDiagnosticsParams, new_struct);
}
void serialize_json_LspDiagnosticsParams(Arena *arena, LspDiagnosticsParams *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    *index += snprintf(buf + *index, buf_size - *index, "}");
}
GenerateOptionStructSerializeFunc(serialize_json_LspDiagnosticsParams, LspDiagnosticsParams);

typedef struct LspServerInfo {
    JsonString name;
    JsonString version;
} LspServerInfo;
GenerateOptionType(LspServerInfo);
Option(LspServerInfo) parse_json_LspServerInfo(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index, unsigned int parent_index) {
    int this_index = *index;
    LspServerInfo new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "name", 4) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            new_struct.name = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            num_parsed_fields += 1;
            *index += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "version", 7) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            new_struct.version = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            num_parsed_fields += 1;
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
        fprintf(stderr, "JSON parse error: Expected 2 fields, got %ld for LspServerInfo\n", num_parsed_fields);
        return None(LspServerInfo);
    }

    return Some(LspServerInfo, new_struct);
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
Option(LspCapabilities) parse_json_LspCapabilities(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index, unsigned int parent_index) {
    int this_index = *index;
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
        fprintf(stderr, "JSON parse error: Expected 0 fields, got %ld for LspCapabilities\n", num_parsed_fields);
        return None(LspCapabilities);
    }

    return Some(LspCapabilities, new_struct);
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
Option(LspInitializeResult) parse_json_LspInitializeResult(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index, unsigned int parent_index) {
    int this_index = *index;
    LspInitializeResult new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "capabilities", 12) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            Option(LspCapabilities) parsed_struct = parse_json_LspCapabilities(arena, json, tokens, index, this_index);
            if (is_none(parsed_struct)) {
                fprintf(stderr, "JSON Parse Error: failed to parse object LspCapabilities\n");
                return None(LspInitializeResult);
            }
            new_struct.capabilities = parsed_struct.value;
            num_parsed_fields += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "serverInfo", 10) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            Option(LspServerInfo) parsed_struct = parse_json_LspServerInfo(arena, json, tokens, index, this_index);
            if (is_none(parsed_struct)) {
                fprintf(stderr, "JSON Parse Error: failed to parse object LspServerInfo\n");
                return None(LspInitializeResult);
            }
            new_struct.serverInfo = parsed_struct.value;
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
        fprintf(stderr, "JSON parse error: Expected 2 fields, got %ld for LspInitializeResult\n", num_parsed_fields);
        return None(LspInitializeResult);
    }

    return Some(LspInitializeResult, new_struct);
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

typedef enum LspRequestResultVariant {
    LspRequestResult_Initialize,
    LspRequestResult_DocumentSymbols,
} LspRequestResultVariant;
GenerateOptionType(LspRequestResultVariant);
typedef struct LspRequestResult {
    LspRequestResultVariant type;
    union {
    LspInitializeResult Initialize;
    LspDocumentSymbolsResponse DocumentSymbols;
    };
} LspRequestResult;
GenerateOptionType(LspRequestResult);
Option(LspRequestResultVariant) LspRequestResultVariant_from_string(JsonString json_tag) {
    if (MatchString(MakeString("Initialize"), json_tag)) {
        return Some(LspRequestResultVariant, LspRequestResult_Initialize);
    }
    else if (MatchString(MakeString("DocumentSymbols"), json_tag)) {
        return Some(LspRequestResultVariant, LspRequestResult_DocumentSymbols);
    }
    return None(LspRequestResultVariant);
}
Option(LspRequestResult) parse_json_LspRequestResult(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index, unsigned int parent_index) {
    int this_index = *index;
    LspRequestResult new_struct = {};
    int num_children = tokens[*index].size;
    long num_parsed_fields = 0;
    {
        Option(LspInitializeResult) parsed_struct = None(LspInitializeResult);
        parsed_struct = parse_json_LspInitializeResult(arena, json, tokens, index, this_index);
        if (is_some(parsed_struct)) {
            new_struct.type = LspRequestResult_Initialize;
            new_struct.Initialize = parsed_struct.value;
            return Some(LspRequestResult, new_struct);
        }
        *index = parent_index;
    }
    {
        Option(LspDocumentSymbolsResponse) parsed_struct = None(LspDocumentSymbolsResponse);
        parsed_struct = parse_json_LspDocumentSymbolsResponse(arena, json, tokens, index, this_index);
        if (is_some(parsed_struct)) {
            new_struct.type = LspRequestResult_DocumentSymbols;
            new_struct.DocumentSymbols = parsed_struct.value;
            return Some(LspRequestResult, new_struct);
        }
        *index = parent_index;
    }
    if (tokens[*index+1].type == JSMN_OBJECT || tokens[*index+1].type == JSMN_ARRAY) {
        *index += 1;
        json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);
    } else {
        *index += 2;
    }

    return None(LspRequestResult);
}
void serialize_json_LspRequestResult(Arena *arena, LspRequestResult *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    switch (data->type) {
        case LspRequestResult_Initialize:
    serialize_json_LspInitializeResult(arena, &data->Initialize, buf, buf_size, index);
    break;
        case LspRequestResult_DocumentSymbols:
    serialize_json_LspDocumentSymbolsResponse(arena, &data->DocumentSymbols, buf, buf_size, index);
    break;
    }
}
GenerateOptionStructSerializeFunc(serialize_json_LspRequestResult, LspRequestResult);

typedef struct LspRequestResponse {
    long id;
    JsonString jsonrpc;
    LspRequestResult result;
} LspRequestResponse;
GenerateOptionType(LspRequestResponse);
Option(LspRequestResponse) parse_json_LspRequestResponse(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index, unsigned int parent_index) {
    int this_index = *index;
    LspRequestResponse new_struct = {};
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
            new_struct.id = value;
            num_parsed_fields += 1;
    }
        else if (is_jsoneq(json, &tokens[*index], "jsonrpc", 7) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            new_struct.jsonrpc = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            num_parsed_fields += 1;
            *index += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "result", 6) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            Option(LspRequestResult) parsed_struct = parse_json_LspRequestResult(arena, json, tokens, index, this_index);
            if (is_none(parsed_struct)) {
                fprintf(stderr, "JSON Parse Error: failed to parse object LspRequestResult\n");
                return None(LspRequestResponse);
            }
            new_struct.result = parsed_struct.value;
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
        fprintf(stderr, "JSON parse error: Expected 3 fields, got %ld for LspRequestResponse\n", num_parsed_fields);
        return None(LspRequestResponse);
    }

    return Some(LspRequestResponse, new_struct);
}
void serialize_json_LspRequestResponse(Arena *arena, LspRequestResponse *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_integer_field(arena, buf, buf_size, index, "id", data->id, false);
    serialize_string_field(arena, buf, buf_size, index, "jsonrpc", data->jsonrpc, true);
    *index += snprintf(buf + *index, buf_size - *index, ",\"result\":");
    serialize_json_LspRequestResult(arena, &data->result, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}
GenerateOptionStructSerializeFunc(serialize_json_LspRequestResponse, LspRequestResponse);

typedef enum LspNotificationMethodVariant {
    LspNotificationMethod_Initialized,
    LspNotificationMethod_Exit,
    LspNotificationMethod_OpenFile,
    LspNotificationMethod_Diagnostics,
} LspNotificationMethodVariant;
GenerateOptionType(LspNotificationMethodVariant);
typedef struct LspNotificationMethod {
    LspNotificationMethodVariant type;
    union {
    LspDidOpenTextDocumentParams OpenFile;
    LspDiagnosticsParams Diagnostics;
    };
} LspNotificationMethod;
GenerateOptionType(LspNotificationMethod);
Option(LspNotificationMethodVariant) LspNotificationMethodVariant_from_string(JsonString json_tag) {
    if (MatchString(MakeString("initialized"), json_tag)) {
        return Some(LspNotificationMethodVariant, LspNotificationMethod_Initialized);
    }
    else if (MatchString(MakeString("exit"), json_tag)) {
        return Some(LspNotificationMethodVariant, LspNotificationMethod_Exit);
    }
    else if (MatchString(MakeString("textDocument/didOpen"), json_tag)) {
        return Some(LspNotificationMethodVariant, LspNotificationMethod_OpenFile);
    }
    else if (MatchString(MakeString("textDocument/publishDiagnostics"), json_tag)) {
        return Some(LspNotificationMethodVariant, LspNotificationMethod_Diagnostics);
    }
    return None(LspNotificationMethodVariant);
}
Option(LspNotificationMethod) parse_json_LspNotificationMethod(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index, unsigned int parent_index) {
    int this_index = *index;
    LspNotificationMethod new_struct = {};
    int num_children = tokens[*index].size;
    long num_parsed_fields = 0;
    int num_parent_children = tokens[parent_index].size;
    parent_index += 1;
    bool found_enum_tag = false;
    for(int i=0;i<num_parent_children;i++) {
        if (is_jsoneq(json, &tokens[parent_index], "method", 6) && tokens[parent_index+1].type == JSMN_STRING) {
            parent_index += 1;
            JsonString variant_name = (JsonString){ tokens[parent_index].end - tokens[parent_index].start, json+tokens[parent_index].start };
            Option(LspNotificationMethodVariant) variant = LspNotificationMethodVariant_from_string(variant_name);
            if (is_some(variant)) {
                new_struct.type = variant.value;
                found_enum_tag = true;
            } else { printf("no variant %.*s for LspNotificationMethodVariant", variant_name.length, variant_name.text); exit(1); }
        } else if (tokens[parent_index+1].type == JSMN_OBJECT || tokens[parent_index+1].type == JSMN_ARRAY) {
        parent_index += 1;
        json_skip_object(json, tokens, &parent_index, tokens[parent_index].type == JSMN_ARRAY);
    } else {
        parent_index += 2;
    }
    }
    if (new_struct.type == LspNotificationMethod_OpenFile) {
            *index += 1;
            Option(LspDidOpenTextDocumentParams) parsed_struct = parse_json_LspDidOpenTextDocumentParams(arena, json, tokens, index, this_index);
            if (is_none(parsed_struct)) {
                fprintf(stderr, "JSON Parse Error: failed to parse object LspDidOpenTextDocumentParams\n");
                return None(LspNotificationMethod);
            }
            new_struct.OpenFile = parsed_struct.value;
            num_parsed_fields += 1;

    return Some(LspNotificationMethod, new_struct);
    }
    else if (new_struct.type == LspNotificationMethod_Diagnostics) {
            *index += 1;
            Option(LspDiagnosticsParams) parsed_struct = parse_json_LspDiagnosticsParams(arena, json, tokens, index, this_index);
            if (is_none(parsed_struct)) {
                fprintf(stderr, "JSON Parse Error: failed to parse object LspDiagnosticsParams\n");
                return None(LspNotificationMethod);
            }
            new_struct.Diagnostics = parsed_struct.value;
            num_parsed_fields += 1;

    return Some(LspNotificationMethod, new_struct);
    }
    if (tokens[*index+1].type == JSMN_OBJECT || tokens[*index+1].type == JSMN_ARRAY) {
        *index += 1;
        json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);
    } else {
        *index += 2;
    }

    return None(LspNotificationMethod);
}
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
        case LspNotificationMethod_Diagnostics:
    serialize_json_LspDiagnosticsParams(arena, &data->Diagnostics, buf, buf_size, index);
            *index += snprintf(buf + *index, buf_size - *index, ",\"method\": \"textDocument/publishDiagnostics\"");
    break;
    }
}
GenerateOptionStructSerializeFunc(serialize_json_LspNotificationMethod, LspNotificationMethod);

typedef struct LspNotification {
    JsonString jsonrpc;
    LspNotificationMethod params;
} LspNotification;
GenerateOptionType(LspNotification);
Option(LspNotification) parse_json_LspNotification(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index, unsigned int parent_index) {
    int this_index = *index;
    LspNotification new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "jsonrpc", 7) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            new_struct.jsonrpc = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            num_parsed_fields += 1;
            *index += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "params", 6) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            Option(LspNotificationMethod) parsed_struct = parse_json_LspNotificationMethod(arena, json, tokens, index, this_index);
            if (is_none(parsed_struct)) {
                fprintf(stderr, "JSON Parse Error: failed to parse object LspNotificationMethod\n");
                return None(LspNotification);
            }
            new_struct.params = parsed_struct.value;
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
        fprintf(stderr, "JSON parse error: Expected 2 fields, got %ld for LspNotification\n", num_parsed_fields);
        return None(LspNotification);
    }

    return Some(LspNotification, new_struct);
}
void serialize_json_LspNotification(Arena *arena, LspNotification *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_string_field(arena, buf, buf_size, index, "jsonrpc", data->jsonrpc, false);
    *index += snprintf(buf + *index, buf_size - *index, ",\"params\":");
    serialize_json_LspNotificationMethod(arena, &data->params, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}
GenerateOptionStructSerializeFunc(serialize_json_LspNotification, LspNotification);

typedef enum LspServerResponseVariant {
    LspServerResponse_Notification,
    LspServerResponse_RequestResponse,
} LspServerResponseVariant;
GenerateOptionType(LspServerResponseVariant);
typedef struct LspServerResponse {
    LspServerResponseVariant type;
    union {
    LspNotification Notification;
    LspRequestResponse RequestResponse;
    };
} LspServerResponse;
GenerateOptionType(LspServerResponse);
Option(LspServerResponseVariant) LspServerResponseVariant_from_string(JsonString json_tag) {
    if (MatchString(MakeString("Notification"), json_tag)) {
        return Some(LspServerResponseVariant, LspServerResponse_Notification);
    }
    else if (MatchString(MakeString("RequestResponse"), json_tag)) {
        return Some(LspServerResponseVariant, LspServerResponse_RequestResponse);
    }
    return None(LspServerResponseVariant);
}
Option(LspServerResponse) parse_json_LspServerResponse(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index, unsigned int parent_index) {
    int this_index = *index;
    LspServerResponse new_struct = {};
    int num_children = tokens[*index].size;
    long num_parsed_fields = 0;
    {
        Option(LspNotification) parsed_struct = None(LspNotification);
        parsed_struct = parse_json_LspNotification(arena, json, tokens, index, this_index);
        if (is_some(parsed_struct)) {
            new_struct.type = LspServerResponse_Notification;
            new_struct.Notification = parsed_struct.value;
            return Some(LspServerResponse, new_struct);
        }
        *index = parent_index;
    }
    {
        Option(LspRequestResponse) parsed_struct = None(LspRequestResponse);
        parsed_struct = parse_json_LspRequestResponse(arena, json, tokens, index, this_index);
        if (is_some(parsed_struct)) {
            new_struct.type = LspServerResponse_RequestResponse;
            new_struct.RequestResponse = parsed_struct.value;
            return Some(LspServerResponse, new_struct);
        }
        *index = parent_index;
    }
    if (tokens[*index+1].type == JSMN_OBJECT || tokens[*index+1].type == JSMN_ARRAY) {
        *index += 1;
        json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);
    } else {
        *index += 2;
    }

    return None(LspServerResponse);
}
void serialize_json_LspServerResponse(Arena *arena, LspServerResponse *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    switch (data->type) {
        case LspServerResponse_Notification:
    serialize_json_LspNotification(arena, &data->Notification, buf, buf_size, index);
    break;
        case LspServerResponse_RequestResponse:
    serialize_json_LspRequestResponse(arena, &data->RequestResponse, buf, buf_size, index);
    break;
    }
}
GenerateOptionStructSerializeFunc(serialize_json_LspServerResponse, LspServerResponse);

typedef enum LspRequestMethodVariant {
    LspRequestMethod_Initialize,
    LspRequestMethod_Shutdown,
    LspRequestMethod_OpenFile,
    LspRequestMethod_GetDocumentSymbols,
} LspRequestMethodVariant;
GenerateOptionType(LspRequestMethodVariant);
typedef struct LspRequestMethod {
    LspRequestMethodVariant type;
    union {
    LspInitializeRequestParams Initialize;
    LspDidOpenTextDocumentParams OpenFile;
    LspDocumentSymbolsParams GetDocumentSymbols;
    };
} LspRequestMethod;
GenerateOptionType(LspRequestMethod);
Option(LspRequestMethodVariant) LspRequestMethodVariant_from_string(JsonString json_tag) {
    if (MatchString(MakeString("initialize"), json_tag)) {
        return Some(LspRequestMethodVariant, LspRequestMethod_Initialize);
    }
    else if (MatchString(MakeString("shutdown"), json_tag)) {
        return Some(LspRequestMethodVariant, LspRequestMethod_Shutdown);
    }
    else if (MatchString(MakeString("textDocument/didOpen"), json_tag)) {
        return Some(LspRequestMethodVariant, LspRequestMethod_OpenFile);
    }
    else if (MatchString(MakeString("textDocument/documentSymbol"), json_tag)) {
        return Some(LspRequestMethodVariant, LspRequestMethod_GetDocumentSymbols);
    }
    return None(LspRequestMethodVariant);
}
Option(LspRequestMethod) parse_json_LspRequestMethod(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index, unsigned int parent_index) {
    int this_index = *index;
    LspRequestMethod new_struct = {};
    int num_children = tokens[*index].size;
    long num_parsed_fields = 0;
    int num_parent_children = tokens[parent_index].size;
    parent_index += 1;
    bool found_enum_tag = false;
    for(int i=0;i<num_parent_children;i++) {
        if (is_jsoneq(json, &tokens[parent_index], "method", 6) && tokens[parent_index+1].type == JSMN_STRING) {
            parent_index += 1;
            JsonString variant_name = (JsonString){ tokens[parent_index].end - tokens[parent_index].start, json+tokens[parent_index].start };
            Option(LspRequestMethodVariant) variant = LspRequestMethodVariant_from_string(variant_name);
            if (is_some(variant)) {
                new_struct.type = variant.value;
                found_enum_tag = true;
            } else { printf("no variant %.*s for LspRequestMethodVariant", variant_name.length, variant_name.text); exit(1); }
        } else if (tokens[parent_index+1].type == JSMN_OBJECT || tokens[parent_index+1].type == JSMN_ARRAY) {
        parent_index += 1;
        json_skip_object(json, tokens, &parent_index, tokens[parent_index].type == JSMN_ARRAY);
    } else {
        parent_index += 2;
    }
    }
    if (new_struct.type == LspRequestMethod_Initialize) {
            *index += 1;
            Option(LspInitializeRequestParams) parsed_struct = parse_json_LspInitializeRequestParams(arena, json, tokens, index, this_index);
            if (is_none(parsed_struct)) {
                fprintf(stderr, "JSON Parse Error: failed to parse object LspInitializeRequestParams\n");
                return None(LspRequestMethod);
            }
            new_struct.Initialize = parsed_struct.value;
            num_parsed_fields += 1;

    return Some(LspRequestMethod, new_struct);
    }
    else if (new_struct.type == LspRequestMethod_OpenFile) {
            *index += 1;
            Option(LspDidOpenTextDocumentParams) parsed_struct = parse_json_LspDidOpenTextDocumentParams(arena, json, tokens, index, this_index);
            if (is_none(parsed_struct)) {
                fprintf(stderr, "JSON Parse Error: failed to parse object LspDidOpenTextDocumentParams\n");
                return None(LspRequestMethod);
            }
            new_struct.OpenFile = parsed_struct.value;
            num_parsed_fields += 1;

    return Some(LspRequestMethod, new_struct);
    }
    else if (new_struct.type == LspRequestMethod_GetDocumentSymbols) {
            *index += 1;
            Option(LspDocumentSymbolsParams) parsed_struct = parse_json_LspDocumentSymbolsParams(arena, json, tokens, index, this_index);
            if (is_none(parsed_struct)) {
                fprintf(stderr, "JSON Parse Error: failed to parse object LspDocumentSymbolsParams\n");
                return None(LspRequestMethod);
            }
            new_struct.GetDocumentSymbols = parsed_struct.value;
            num_parsed_fields += 1;

    return Some(LspRequestMethod, new_struct);
    }
    if (tokens[*index+1].type == JSMN_OBJECT || tokens[*index+1].type == JSMN_ARRAY) {
        *index += 1;
        json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);
    } else {
        *index += 2;
    }

    return None(LspRequestMethod);
}
void serialize_json_LspRequestMethod(Arena *arena, LspRequestMethod *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    switch (data->type) {
        case LspRequestMethod_Initialize:
    serialize_json_LspInitializeRequestParams(arena, &data->Initialize, buf, buf_size, index);
            *index += snprintf(buf + *index, buf_size - *index, ",\"method\": \"initialize\"");
    break;
        case LspRequestMethod_Shutdown:
            *index += snprintf(buf + *index, buf_size - *index, "null");
            *index += snprintf(buf + *index, buf_size - *index, ",\"method\": \"shutdown\"");
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

typedef struct LspRequest {
    long id;
    JsonString jsonrpc;
    LspRequestMethod params;
} LspRequest;
GenerateOptionType(LspRequest);
Option(LspRequest) parse_json_LspRequest(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index, unsigned int parent_index) {
    int this_index = *index;
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
            new_struct.id = value;
            num_parsed_fields += 1;
    }
        else if (is_jsoneq(json, &tokens[*index], "jsonrpc", 7) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            new_struct.jsonrpc = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            num_parsed_fields += 1;
            *index += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "params", 6) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            Option(LspRequestMethod) parsed_struct = parse_json_LspRequestMethod(arena, json, tokens, index, this_index);
            if (is_none(parsed_struct)) {
                fprintf(stderr, "JSON Parse Error: failed to parse object LspRequestMethod\n");
                return None(LspRequest);
            }
            new_struct.params = parsed_struct.value;
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
        fprintf(stderr, "JSON parse error: Expected 3 fields, got %ld for LspRequest\n", num_parsed_fields);
        return None(LspRequest);
    }

    return Some(LspRequest, new_struct);
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

