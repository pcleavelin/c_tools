// DO NOT EDIT - This file was automatically generated

#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <jsmn.h>
#include <better_structs/better_structs.h>

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
typedef struct LspTextDocumentSync {
    long change;
    bool openClose;
    bool save;
} LspTextDocumentSync;
LspTextDocumentSync parse_json_LspTextDocumentSync(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspTextDocumentSync new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "change", 6) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            long value = 0;
            errno = 0;
            value = strtol(json + tokens[*index].start, 0, 10);
            if (errno != 0 && value == 0) {
                fprintf(stderr, "JSON parse error: Expected json type 'i32'\n");
                exit(1);
            } else if (value == LONG_MIN || value == LONG_MAX) {
                fprintf(stderr, "JSON parse error: Expected json type 'i32'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.change = value;
        }
        else if (is_jsoneq(json, &tokens[*index], "openClose", 9) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            char text = json[tokens[*index].start];
            if (text != 't' && text != 'f') {
                fprintf(stderr, "JSON parse error: Expected json type 'bool'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.openClose = text == 't';
        }
        else if (is_jsoneq(json, &tokens[*index], "save", 4) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            char text = json[tokens[*index].start];
            if (text != 't' && text != 'f') {
                fprintf(stderr, "JSON parse error: Expected json type 'bool'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.save = text == 't';
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
void serialize_json_LspTextDocumentSync(Arena *arena, LspTextDocumentSync *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_integer_field(arena, buf, buf_size, index, "change", data->change, false);
    serialize_bool_field(arena, buf, buf_size, index, "openClose", data->openClose, true);
    serialize_bool_field(arena, buf, buf_size, index, "save", data->save, true);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct LspSignatureHelpProvider {
    long numTriggerCharacters;
    JsonString *triggerCharacters;
} LspSignatureHelpProvider;
LspSignatureHelpProvider parse_json_LspSignatureHelpProvider(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspSignatureHelpProvider new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "triggerCharacters", 17) && tokens[*index+1].type == JSMN_ARRAY) {
            const int array_size = tokens[*index+1].size;
            *index += 2;
            new_struct.triggerCharacters = arena_allocate_block(arena, sizeof(JsonString) * array_size);
            new_struct.numTriggerCharacters = array_size;
            for (int i=0;i<array_size;i++) {
                if(tokens[*index].type == JSMN_STRING) {
                    new_struct.triggerCharacters[i] = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
                    *index += 1;
                } else {
                    fprintf(stderr, "JSON parse error: Expected json type 'string' in array 'triggerCharacters'\n");
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
void serialize_json_LspSignatureHelpProvider(Arena *arena, LspSignatureHelpProvider *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    *index += snprintf(buf + *index, buf_size - *index, "\"triggerCharacters\":[");
    for(int i=0;i<data->numTriggerCharacters;i++) {
        serialize_string_value(arena, buf, buf_size, index, &data->triggerCharacters[i], i > 0);
    }
    *index += snprintf(buf + *index, buf_size - *index, "]");
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct LspSemanticTokensProviderLegend {
    long numTokenModifiers;
    JsonString *tokenModifiers;
    long numTokenTypes;
    JsonString *tokenTypes;
} LspSemanticTokensProviderLegend;
LspSemanticTokensProviderLegend parse_json_LspSemanticTokensProviderLegend(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspSemanticTokensProviderLegend new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "tokenModifiers", 14) && tokens[*index+1].type == JSMN_ARRAY) {
            const int array_size = tokens[*index+1].size;
            *index += 2;
            new_struct.tokenModifiers = arena_allocate_block(arena, sizeof(JsonString) * array_size);
            new_struct.numTokenModifiers = array_size;
            for (int i=0;i<array_size;i++) {
                if(tokens[*index].type == JSMN_STRING) {
                    new_struct.tokenModifiers[i] = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
                    *index += 1;
                } else {
                    fprintf(stderr, "JSON parse error: Expected json type 'string' in array 'tokenModifiers'\n");
                    exit(1);
                }
            }
            num_parsed_fields += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "tokenTypes", 10) && tokens[*index+1].type == JSMN_ARRAY) {
            const int array_size = tokens[*index+1].size;
            *index += 2;
            new_struct.tokenTypes = arena_allocate_block(arena, sizeof(JsonString) * array_size);
            new_struct.numTokenTypes = array_size;
            for (int i=0;i<array_size;i++) {
                if(tokens[*index].type == JSMN_STRING) {
                    new_struct.tokenTypes[i] = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
                    *index += 1;
                } else {
                    fprintf(stderr, "JSON parse error: Expected json type 'string' in array 'tokenTypes'\n");
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

    if (num_parsed_fields != 2) {
        fprintf(stderr, "JSON parse error: Expected 2 fields, got %ld\n", num_parsed_fields);
    }

    return new_struct;
}
void serialize_json_LspSemanticTokensProviderLegend(Arena *arena, LspSemanticTokensProviderLegend *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    *index += snprintf(buf + *index, buf_size - *index, "\"tokenModifiers\":[");
    for(int i=0;i<data->numTokenModifiers;i++) {
        serialize_string_value(arena, buf, buf_size, index, &data->tokenModifiers[i], i > 0);
    }
    *index += snprintf(buf + *index, buf_size - *index, "]");
    *index += snprintf(buf + *index, buf_size - *index, ",\"tokenTypes\":[");
    for(int i=0;i<data->numTokenTypes;i++) {
        serialize_string_value(arena, buf, buf_size, index, &data->tokenTypes[i], i > 0);
    }
    *index += snprintf(buf + *index, buf_size - *index, "]");
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct LspSematicTokensProviderFull {
    bool delta;
} LspSematicTokensProviderFull;
LspSematicTokensProviderFull parse_json_LspSematicTokensProviderFull(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspSematicTokensProviderFull new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "delta", 5) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            char text = json[tokens[*index].start];
            if (text != 't' && text != 'f') {
                fprintf(stderr, "JSON parse error: Expected json type 'bool'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.delta = text == 't';
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
void serialize_json_LspSematicTokensProviderFull(Arena *arena, LspSematicTokensProviderFull *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_bool_field(arena, buf, buf_size, index, "delta", data->delta, false);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct LspSemanticTokensProvider {
    LspSematicTokensProviderFull full;
    LspSemanticTokensProviderLegend legend;
    bool range;
} LspSemanticTokensProvider;
LspSemanticTokensProvider parse_json_LspSemanticTokensProvider(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspSemanticTokensProvider new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "full", 4) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.full = parse_json_LspSematicTokensProviderFull(arena, json, tokens, index);
            num_parsed_fields += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "legend", 6) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.legend = parse_json_LspSemanticTokensProviderLegend(arena, json, tokens, index);
            num_parsed_fields += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "range", 5) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            char text = json[tokens[*index].start];
            if (text != 't' && text != 'f') {
                fprintf(stderr, "JSON parse error: Expected json type 'bool'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.range = text == 't';
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
void serialize_json_LspSemanticTokensProvider(Arena *arena, LspSemanticTokensProvider *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    *index += snprintf(buf + *index, buf_size - *index, "\"full\":");
    serialize_json_LspSematicTokensProviderFull(arena, &data->full, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, ",\"legend\":");
    serialize_json_LspSemanticTokensProviderLegend(arena, &data->legend, buf, buf_size, index);
    serialize_bool_field(arena, buf, buf_size, index, "range", data->range, true);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct LspExecuteCommandProvider {
    long numCommands;
    JsonString *commands;
} LspExecuteCommandProvider;
LspExecuteCommandProvider parse_json_LspExecuteCommandProvider(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspExecuteCommandProvider new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "commands", 8) && tokens[*index+1].type == JSMN_ARRAY) {
            const int array_size = tokens[*index+1].size;
            *index += 2;
            new_struct.commands = arena_allocate_block(arena, sizeof(JsonString) * array_size);
            new_struct.numCommands = array_size;
            for (int i=0;i<array_size;i++) {
                if(tokens[*index].type == JSMN_STRING) {
                    new_struct.commands[i] = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
                    *index += 1;
                } else {
                    fprintf(stderr, "JSON parse error: Expected json type 'string' in array 'commands'\n");
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
void serialize_json_LspExecuteCommandProvider(Arena *arena, LspExecuteCommandProvider *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    *index += snprintf(buf + *index, buf_size - *index, "\"commands\":[");
    for(int i=0;i<data->numCommands;i++) {
        serialize_string_value(arena, buf, buf_size, index, &data->commands[i], i > 0);
    }
    *index += snprintf(buf + *index, buf_size - *index, "]");
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct LspDocumentOnTypeFormattingProvider {
    JsonString firstTriggerCharacter;
    long numMoreTriggerCharacters;
    JsonString *moreTriggerCharacter;
} LspDocumentOnTypeFormattingProvider;
LspDocumentOnTypeFormattingProvider parse_json_LspDocumentOnTypeFormattingProvider(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspDocumentOnTypeFormattingProvider new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "firstTriggerCharacter", 21) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            num_parsed_fields += 1;
            new_struct.firstTriggerCharacter = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            *index += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "moreTriggerCharacter", 20) && tokens[*index+1].type == JSMN_ARRAY) {
            const int array_size = tokens[*index+1].size;
            *index += 2;
            new_struct.moreTriggerCharacter = arena_allocate_block(arena, sizeof(JsonString) * array_size);
            new_struct.numMoreTriggerCharacters = array_size;
            for (int i=0;i<array_size;i++) {
                if(tokens[*index].type == JSMN_STRING) {
                    new_struct.moreTriggerCharacter[i] = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
                    *index += 1;
                } else {
                    fprintf(stderr, "JSON parse error: Expected json type 'string' in array 'moreTriggerCharacter'\n");
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

    if (num_parsed_fields != 2) {
        fprintf(stderr, "JSON parse error: Expected 2 fields, got %ld\n", num_parsed_fields);
    }

    return new_struct;
}
void serialize_json_LspDocumentOnTypeFormattingProvider(Arena *arena, LspDocumentOnTypeFormattingProvider *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_string_field(arena, buf, buf_size, index, "firstTriggerCharacter", &data->firstTriggerCharacter, false);
    *index += snprintf(buf + *index, buf_size - *index, ",\"moreTriggerCharacter\":[");
    for(int i=0;i<data->numMoreTriggerCharacters;i++) {
        serialize_string_value(arena, buf, buf_size, index, &data->moreTriggerCharacter[i], i > 0);
    }
    *index += snprintf(buf + *index, buf_size - *index, "]");
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct LspDocumentLinkProvider {
    bool resolveProvider;
} LspDocumentLinkProvider;
LspDocumentLinkProvider parse_json_LspDocumentLinkProvider(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspDocumentLinkProvider new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "resolveProvider", 15) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            char text = json[tokens[*index].start];
            if (text != 't' && text != 'f') {
                fprintf(stderr, "JSON parse error: Expected json type 'bool'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.resolveProvider = text == 't';
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
void serialize_json_LspDocumentLinkProvider(Arena *arena, LspDocumentLinkProvider *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_bool_field(arena, buf, buf_size, index, "resolveProvider", data->resolveProvider, false);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct LspCompletionProvider {
    long numCommitCharacters;
    JsonString *allCommitCharacters;
    bool resolveProvider;
    long numTriggerCharacters;
    JsonString *triggerCharacters;
} LspCompletionProvider;
LspCompletionProvider parse_json_LspCompletionProvider(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspCompletionProvider new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "allCommitCharacters", 19) && tokens[*index+1].type == JSMN_ARRAY) {
            const int array_size = tokens[*index+1].size;
            *index += 2;
            new_struct.allCommitCharacters = arena_allocate_block(arena, sizeof(JsonString) * array_size);
            new_struct.numCommitCharacters = array_size;
            for (int i=0;i<array_size;i++) {
                if(tokens[*index].type == JSMN_STRING) {
                    new_struct.allCommitCharacters[i] = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
                    *index += 1;
                } else {
                    fprintf(stderr, "JSON parse error: Expected json type 'string' in array 'allCommitCharacters'\n");
                    exit(1);
                }
            }
            num_parsed_fields += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "resolveProvider", 15) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            char text = json[tokens[*index].start];
            if (text != 't' && text != 'f') {
                fprintf(stderr, "JSON parse error: Expected json type 'bool'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.resolveProvider = text == 't';
        }
        else if (is_jsoneq(json, &tokens[*index], "triggerCharacters", 17) && tokens[*index+1].type == JSMN_ARRAY) {
            const int array_size = tokens[*index+1].size;
            *index += 2;
            new_struct.triggerCharacters = arena_allocate_block(arena, sizeof(JsonString) * array_size);
            new_struct.numTriggerCharacters = array_size;
            for (int i=0;i<array_size;i++) {
                if(tokens[*index].type == JSMN_STRING) {
                    new_struct.triggerCharacters[i] = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
                    *index += 1;
                } else {
                    fprintf(stderr, "JSON parse error: Expected json type 'string' in array 'triggerCharacters'\n");
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

    if (num_parsed_fields != 3) {
        fprintf(stderr, "JSON parse error: Expected 3 fields, got %ld\n", num_parsed_fields);
    }

    return new_struct;
}
void serialize_json_LspCompletionProvider(Arena *arena, LspCompletionProvider *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    *index += snprintf(buf + *index, buf_size - *index, "\"allCommitCharacters\":[");
    for(int i=0;i<data->numCommitCharacters;i++) {
        serialize_string_value(arena, buf, buf_size, index, &data->allCommitCharacters[i], i > 0);
    }
    *index += snprintf(buf + *index, buf_size - *index, "]");
    serialize_bool_field(arena, buf, buf_size, index, "resolveProvider", data->resolveProvider, true);
    *index += snprintf(buf + *index, buf_size - *index, ",\"triggerCharacters\":[");
    for(int i=0;i<data->numTriggerCharacters;i++) {
        serialize_string_value(arena, buf, buf_size, index, &data->triggerCharacters[i], i > 0);
    }
    *index += snprintf(buf + *index, buf_size - *index, "]");
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct LspCapabilities {
    JsonString positionEncoding;
    bool codeActionProvider;
    LspCompletionProvider completionProvider;
    bool declarationProvider;
    bool definitionProvider;
    bool documentFormattingProvider;
    bool documentHighlightProvider;
    LspDocumentLinkProvider documentLinkProvider;
    LspDocumentOnTypeFormattingProvider documentOnTypeFormattingProvider;
    bool documentRangeFormattingProvider;
    bool documentSymbolProvider;
    LspExecuteCommandProvider executeCommandProvider;
    bool hoverProvider;
    bool referencesProvider;
    bool renameProvider;
    bool selectionRangeProvider;
    LspSemanticTokensProvider semanticTokensProvider;
    LspSignatureHelpProvider signatureHelpProvider;
    LspTextDocumentSync textDocumentSync;
    bool typeHierarchyProvider;
    bool workspaceSymbolProvider;
} LspCapabilities;
LspCapabilities parse_json_LspCapabilities(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    LspCapabilities new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "positionEncoding", 16) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            num_parsed_fields += 1;
            new_struct.positionEncoding = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            *index += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "codeActionProvider", 18) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            char text = json[tokens[*index].start];
            if (text != 't' && text != 'f') {
                fprintf(stderr, "JSON parse error: Expected json type 'bool'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.codeActionProvider = text == 't';
        }
        else if (is_jsoneq(json, &tokens[*index], "completionProvider", 18) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.completionProvider = parse_json_LspCompletionProvider(arena, json, tokens, index);
            num_parsed_fields += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "declarationProvider", 19) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            char text = json[tokens[*index].start];
            if (text != 't' && text != 'f') {
                fprintf(stderr, "JSON parse error: Expected json type 'bool'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.declarationProvider = text == 't';
        }
        else if (is_jsoneq(json, &tokens[*index], "definitionProvider", 18) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            char text = json[tokens[*index].start];
            if (text != 't' && text != 'f') {
                fprintf(stderr, "JSON parse error: Expected json type 'bool'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.definitionProvider = text == 't';
        }
        else if (is_jsoneq(json, &tokens[*index], "documentFormattingProvider", 26) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            char text = json[tokens[*index].start];
            if (text != 't' && text != 'f') {
                fprintf(stderr, "JSON parse error: Expected json type 'bool'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.documentFormattingProvider = text == 't';
        }
        else if (is_jsoneq(json, &tokens[*index], "documentHighlightProvider", 25) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            char text = json[tokens[*index].start];
            if (text != 't' && text != 'f') {
                fprintf(stderr, "JSON parse error: Expected json type 'bool'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.documentHighlightProvider = text == 't';
        }
        else if (is_jsoneq(json, &tokens[*index], "documentLinkProvider", 20) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.documentLinkProvider = parse_json_LspDocumentLinkProvider(arena, json, tokens, index);
            num_parsed_fields += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "documentOnTypeFormattingProvider", 32) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.documentOnTypeFormattingProvider = parse_json_LspDocumentOnTypeFormattingProvider(arena, json, tokens, index);
            num_parsed_fields += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "documentRangeFormattingProvider", 31) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            char text = json[tokens[*index].start];
            if (text != 't' && text != 'f') {
                fprintf(stderr, "JSON parse error: Expected json type 'bool'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.documentRangeFormattingProvider = text == 't';
        }
        else if (is_jsoneq(json, &tokens[*index], "documentSymbolProvider", 22) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            char text = json[tokens[*index].start];
            if (text != 't' && text != 'f') {
                fprintf(stderr, "JSON parse error: Expected json type 'bool'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.documentSymbolProvider = text == 't';
        }
        else if (is_jsoneq(json, &tokens[*index], "executeCommandProvider", 22) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.executeCommandProvider = parse_json_LspExecuteCommandProvider(arena, json, tokens, index);
            num_parsed_fields += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "hoverProvider", 13) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            char text = json[tokens[*index].start];
            if (text != 't' && text != 'f') {
                fprintf(stderr, "JSON parse error: Expected json type 'bool'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.hoverProvider = text == 't';
        }
        else if (is_jsoneq(json, &tokens[*index], "referencesProvider", 18) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            char text = json[tokens[*index].start];
            if (text != 't' && text != 'f') {
                fprintf(stderr, "JSON parse error: Expected json type 'bool'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.referencesProvider = text == 't';
        }
        else if (is_jsoneq(json, &tokens[*index], "renameProvider", 14) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            char text = json[tokens[*index].start];
            if (text != 't' && text != 'f') {
                fprintf(stderr, "JSON parse error: Expected json type 'bool'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.renameProvider = text == 't';
        }
        else if (is_jsoneq(json, &tokens[*index], "selectionRangeProvider", 22) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            char text = json[tokens[*index].start];
            if (text != 't' && text != 'f') {
                fprintf(stderr, "JSON parse error: Expected json type 'bool'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.selectionRangeProvider = text == 't';
        }
        else if (is_jsoneq(json, &tokens[*index], "semanticTokensProvider", 22) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.semanticTokensProvider = parse_json_LspSemanticTokensProvider(arena, json, tokens, index);
            num_parsed_fields += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "signatureHelpProvider", 21) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.signatureHelpProvider = parse_json_LspSignatureHelpProvider(arena, json, tokens, index);
            num_parsed_fields += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "textDocumentSync", 16) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.textDocumentSync = parse_json_LspTextDocumentSync(arena, json, tokens, index);
            num_parsed_fields += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "typeHierarchyProvider", 21) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            char text = json[tokens[*index].start];
            if (text != 't' && text != 'f') {
                fprintf(stderr, "JSON parse error: Expected json type 'bool'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.typeHierarchyProvider = text == 't';
        }
        else if (is_jsoneq(json, &tokens[*index], "workspaceSymbolProvider", 23) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            char text = json[tokens[*index].start];
            if (text != 't' && text != 'f') {
                fprintf(stderr, "JSON parse error: Expected json type 'bool'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.workspaceSymbolProvider = text == 't';
        }
        else if (tokens[*index+1].type == JSMN_OBJECT || tokens[*index+1].type == JSMN_ARRAY) {
            *index += 1;
            json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);
        } else {
            *index += 2;
        }
    }

    if (num_parsed_fields != 21) {
        fprintf(stderr, "JSON parse error: Expected 21 fields, got %ld\n", num_parsed_fields);
    }

    return new_struct;
}
void serialize_json_LspCapabilities(Arena *arena, LspCapabilities *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_string_field(arena, buf, buf_size, index, "positionEncoding", &data->positionEncoding, false);
    serialize_bool_field(arena, buf, buf_size, index, "codeActionProvider", data->codeActionProvider, true);
    *index += snprintf(buf + *index, buf_size - *index, ",\"completionProvider\":");
    serialize_json_LspCompletionProvider(arena, &data->completionProvider, buf, buf_size, index);
    serialize_bool_field(arena, buf, buf_size, index, "declarationProvider", data->declarationProvider, true);
    serialize_bool_field(arena, buf, buf_size, index, "definitionProvider", data->definitionProvider, true);
    serialize_bool_field(arena, buf, buf_size, index, "documentFormattingProvider", data->documentFormattingProvider, true);
    serialize_bool_field(arena, buf, buf_size, index, "documentHighlightProvider", data->documentHighlightProvider, true);
    *index += snprintf(buf + *index, buf_size - *index, ",\"documentLinkProvider\":");
    serialize_json_LspDocumentLinkProvider(arena, &data->documentLinkProvider, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, ",\"documentOnTypeFormattingProvider\":");
    serialize_json_LspDocumentOnTypeFormattingProvider(arena, &data->documentOnTypeFormattingProvider, buf, buf_size, index);
    serialize_bool_field(arena, buf, buf_size, index, "documentRangeFormattingProvider", data->documentRangeFormattingProvider, true);
    serialize_bool_field(arena, buf, buf_size, index, "documentSymbolProvider", data->documentSymbolProvider, true);
    *index += snprintf(buf + *index, buf_size - *index, ",\"executeCommandProvider\":");
    serialize_json_LspExecuteCommandProvider(arena, &data->executeCommandProvider, buf, buf_size, index);
    serialize_bool_field(arena, buf, buf_size, index, "hoverProvider", data->hoverProvider, true);
    serialize_bool_field(arena, buf, buf_size, index, "referencesProvider", data->referencesProvider, true);
    serialize_bool_field(arena, buf, buf_size, index, "renameProvider", data->renameProvider, true);
    serialize_bool_field(arena, buf, buf_size, index, "selectionRangeProvider", data->selectionRangeProvider, true);
    *index += snprintf(buf + *index, buf_size - *index, ",\"semanticTokensProvider\":");
    serialize_json_LspSemanticTokensProvider(arena, &data->semanticTokensProvider, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, ",\"signatureHelpProvider\":");
    serialize_json_LspSignatureHelpProvider(arena, &data->signatureHelpProvider, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, ",\"textDocumentSync\":");
    serialize_json_LspTextDocumentSync(arena, &data->textDocumentSync, buf, buf_size, index);
    serialize_bool_field(arena, buf, buf_size, index, "typeHierarchyProvider", data->typeHierarchyProvider, true);
    serialize_bool_field(arena, buf, buf_size, index, "workspaceSymbolProvider", data->workspaceSymbolProvider, true);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct LspServerInfo {
    JsonString name;
    JsonString version;
} LspServerInfo;
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
    serialize_string_field(arena, buf, buf_size, index, "name", &data->name, false);
    serialize_string_field(arena, buf, buf_size, index, "version", &data->version, true);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct InitializeResult {
    LspCapabilities capabilities;
    LspServerInfo serverInfo;
} InitializeResult;
InitializeResult parse_json_InitializeResult(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    InitializeResult new_struct = {};
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
void serialize_json_InitializeResult(Arena *arena, InitializeResult *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    *index += snprintf(buf + *index, buf_size - *index, "\"capabilities\":");
    serialize_json_LspCapabilities(arena, &data->capabilities, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, ",\"serverInfo\":");
    serialize_json_LspServerInfo(arena, &data->serverInfo, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct InitializeResponse {
    long id;
    JsonString jsonrpc;
    InitializeResult result;
} InitializeResponse;
InitializeResponse parse_json_InitializeResponse(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    InitializeResponse new_struct = {};
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
                fprintf(stderr, "JSON parse error: Expected json type 'i32'\n");
                exit(1);
            } else if (value == LONG_MIN || value == LONG_MAX) {
                fprintf(stderr, "JSON parse error: Expected json type 'i32'\n");
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
            new_struct.result = parse_json_InitializeResult(arena, json, tokens, index);
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
void serialize_json_InitializeResponse(Arena *arena, InitializeResponse *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_integer_field(arena, buf, buf_size, index, "id", data->id, false);
    serialize_string_field(arena, buf, buf_size, index, "jsonrpc", &data->jsonrpc, true);
    *index += snprintf(buf + *index, buf_size - *index, ",\"result\":");
    serialize_json_InitializeResult(arena, &data->result, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct Error {
    long code;
    JsonString message;
} Error;
Error parse_json_Error(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    Error new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "code", 4) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            long value = 0;
            errno = 0;
            value = strtol(json + tokens[*index].start, 0, 10);
            if (errno != 0 && value == 0) {
                fprintf(stderr, "JSON parse error: Expected json type 'i32'\n");
                exit(1);
            } else if (value == LONG_MIN || value == LONG_MAX) {
                fprintf(stderr, "JSON parse error: Expected json type 'i32'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.code = value;
        }
        else if (is_jsoneq(json, &tokens[*index], "message", 7) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            num_parsed_fields += 1;
            new_struct.message = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
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
void serialize_json_Error(Arena *arena, Error *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_integer_field(arena, buf, buf_size, index, "code", data->code, false);
    serialize_string_field(arena, buf, buf_size, index, "message", &data->message, true);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct ShutdownResponse {
    long id;
    JsonString jsonrpc;
    Error error;
} ShutdownResponse;
ShutdownResponse parse_json_ShutdownResponse(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    ShutdownResponse new_struct = {};
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
                fprintf(stderr, "JSON parse error: Expected json type 'i32'\n");
                exit(1);
            } else if (value == LONG_MIN || value == LONG_MAX) {
                fprintf(stderr, "JSON parse error: Expected json type 'i32'\n");
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
        else if (is_jsoneq(json, &tokens[*index], "error", 5) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.error = parse_json_Error(arena, json, tokens, index);
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
void serialize_json_ShutdownResponse(Arena *arena, ShutdownResponse *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_integer_field(arena, buf, buf_size, index, "id", data->id, false);
    serialize_string_field(arena, buf, buf_size, index, "jsonrpc", &data->jsonrpc, true);
    *index += snprintf(buf + *index, buf_size - *index, ",\"error\":");
    serialize_json_Error(arena, &data->error, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct Position {
    long line;
    long character;
} Position;
Position parse_json_Position(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    Position new_struct = {};
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
                fprintf(stderr, "JSON parse error: Expected json type 'i32'\n");
                exit(1);
            } else if (value == LONG_MIN || value == LONG_MAX) {
                fprintf(stderr, "JSON parse error: Expected json type 'i32'\n");
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
                fprintf(stderr, "JSON parse error: Expected json type 'i32'\n");
                exit(1);
            } else if (value == LONG_MIN || value == LONG_MAX) {
                fprintf(stderr, "JSON parse error: Expected json type 'i32'\n");
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
void serialize_json_Position(Arena *arena, Position *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_integer_field(arena, buf, buf_size, index, "line", data->line, false);
    serialize_integer_field(arena, buf, buf_size, index, "character", data->character, true);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct Range {
    Position start;
    Position end;
} Range;
Range parse_json_Range(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    Range new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "start", 5) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.start = parse_json_Position(arena, json, tokens, index);
            num_parsed_fields += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "end", 3) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.end = parse_json_Position(arena, json, tokens, index);
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
void serialize_json_Range(Arena *arena, Range *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    *index += snprintf(buf + *index, buf_size - *index, "\"start\":");
    serialize_json_Position(arena, &data->start, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, ",\"end\":");
    serialize_json_Position(arena, &data->end, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct Location {
    JsonString uri;
    Range range;
} Location;
Location parse_json_Location(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    Location new_struct = {};
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
            new_struct.range = parse_json_Range(arena, json, tokens, index);
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
void serialize_json_Location(Arena *arena, Location *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_string_field(arena, buf, buf_size, index, "uri", &data->uri, false);
    *index += snprintf(buf + *index, buf_size - *index, ",\"range\":");
    serialize_json_Range(arena, &data->range, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct SymbolInformation {
    JsonString name;
    long kind;
    Location location;
} SymbolInformation;
SymbolInformation parse_json_SymbolInformation(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    SymbolInformation new_struct = {};
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
                fprintf(stderr, "JSON parse error: Expected json type 'i32'\n");
                exit(1);
            } else if (value == LONG_MIN || value == LONG_MAX) {
                fprintf(stderr, "JSON parse error: Expected json type 'i32'\n");
                exit(1);
            }

            *index += 1;
            num_parsed_fields += 1;
            new_struct.kind = value;
        }
        else if (is_jsoneq(json, &tokens[*index], "location", 8) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.location = parse_json_Location(arena, json, tokens, index);
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
void serialize_json_SymbolInformation(Arena *arena, SymbolInformation *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_string_field(arena, buf, buf_size, index, "name", &data->name, false);
    serialize_integer_field(arena, buf, buf_size, index, "kind", data->kind, true);
    *index += snprintf(buf + *index, buf_size - *index, ",\"location\":");
    serialize_json_Location(arena, &data->location, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct DocumentSymbolsResponse {
    long count;
    SymbolInformation *result;
} DocumentSymbolsResponse;
DocumentSymbolsResponse parse_json_DocumentSymbolsResponse(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    DocumentSymbolsResponse new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "result", 6) && tokens[*index+1].type == JSMN_ARRAY) {
            const int array_size = tokens[*index+1].size;
            *index += 2;
            new_struct.result = arena_allocate_block(arena, sizeof(SymbolInformation) * array_size);
            new_struct.count = array_size;
            for (int i=0;i<array_size;i++) {
                if(tokens[*index].type == JSMN_OBJECT) {
                    new_struct.result[i] = parse_json_SymbolInformation(arena, json, tokens, index);
                } else {
                    fprintf(stderr, "JSON parse error: Expected json type 'SymbolInformation' in array 'result'\n");
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
void serialize_json_DocumentSymbolsResponse(Arena *arena, DocumentSymbolsResponse *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    *index += snprintf(buf + *index, buf_size - *index, "\"result\":[");
    for(int i=0;i<data->count;i++) {
        serialize_json_SymbolInformation(arena, &data->result[i], buf, buf_size, index);
    }
    *index += snprintf(buf + *index, buf_size - *index, "]");
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct Empty {
} Empty;
Empty parse_json_Empty(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    Empty new_struct = {};
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
void serialize_json_Empty(Arena *arena, Empty *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct InitializeRequestParams {
    Empty capabilities;
    JsonString rootUri;
    long processId;
} InitializeRequestParams;
InitializeRequestParams parse_json_InitializeRequestParams(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    InitializeRequestParams new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "capabilities", 12) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.capabilities = parse_json_Empty(arena, json, tokens, index);
            num_parsed_fields += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "rootUri", 7) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            num_parsed_fields += 1;
            new_struct.rootUri = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            *index += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "processId", 9) && tokens[*index+1].type == JSMN_PRIMITIVE) {
            *index += 1;
            long value = 0;
            errno = 0;
            value = strtol(json + tokens[*index].start, 0, 10);
            if (errno != 0 && value == 0) {
                fprintf(stderr, "JSON parse error: Expected json type 'i32'\n");
                exit(1);
            } else if (value == LONG_MIN || value == LONG_MAX) {
                fprintf(stderr, "JSON parse error: Expected json type 'i32'\n");
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
void serialize_json_InitializeRequestParams(Arena *arena, InitializeRequestParams *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    *index += snprintf(buf + *index, buf_size - *index, "\"capabilities\":");
    serialize_json_Empty(arena, &data->capabilities, buf, buf_size, index);
    serialize_string_field(arena, buf, buf_size, index, "rootUri", &data->rootUri, true);
    serialize_integer_field(arena, buf, buf_size, index, "processId", data->processId, true);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct InitializeRequest {
    long id;
    JsonString jsonrpc;
    JsonString method;
    InitializeRequestParams params;
} InitializeRequest;
InitializeRequest parse_json_InitializeRequest(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    InitializeRequest new_struct = {};
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
                fprintf(stderr, "JSON parse error: Expected json type 'i32'\n");
                exit(1);
            } else if (value == LONG_MIN || value == LONG_MAX) {
                fprintf(stderr, "JSON parse error: Expected json type 'i32'\n");
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
        else if (is_jsoneq(json, &tokens[*index], "method", 6) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            num_parsed_fields += 1;
            new_struct.method = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            *index += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "params", 6) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.params = parse_json_InitializeRequestParams(arena, json, tokens, index);
            num_parsed_fields += 1;
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
void serialize_json_InitializeRequest(Arena *arena, InitializeRequest *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_integer_field(arena, buf, buf_size, index, "id", data->id, false);
    serialize_string_field(arena, buf, buf_size, index, "jsonrpc", &data->jsonrpc, true);
    serialize_string_field(arena, buf, buf_size, index, "method", &data->method, true);
    *index += snprintf(buf + *index, buf_size - *index, ",\"params\":");
    serialize_json_InitializeRequestParams(arena, &data->params, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct InitializedNotification {
    JsonString jsonrpc;
    JsonString method;
    Empty params;
} InitializedNotification;
InitializedNotification parse_json_InitializedNotification(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    InitializedNotification new_struct = {};
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
        else if (is_jsoneq(json, &tokens[*index], "method", 6) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            num_parsed_fields += 1;
            new_struct.method = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            *index += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "params", 6) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.params = parse_json_Empty(arena, json, tokens, index);
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
void serialize_json_InitializedNotification(Arena *arena, InitializedNotification *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_string_field(arena, buf, buf_size, index, "jsonrpc", &data->jsonrpc, false);
    serialize_string_field(arena, buf, buf_size, index, "method", &data->method, true);
    *index += snprintf(buf + *index, buf_size - *index, ",\"params\":");
    serialize_json_Empty(arena, &data->params, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct ShutdownRequest {
    long id;
    JsonString jsonrpc;
    JsonString method;
} ShutdownRequest;
ShutdownRequest parse_json_ShutdownRequest(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    ShutdownRequest new_struct = {};
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
                fprintf(stderr, "JSON parse error: Expected json type 'i32'\n");
                exit(1);
            } else if (value == LONG_MIN || value == LONG_MAX) {
                fprintf(stderr, "JSON parse error: Expected json type 'i32'\n");
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
        else if (is_jsoneq(json, &tokens[*index], "method", 6) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            num_parsed_fields += 1;
            new_struct.method = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            *index += 1;
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
void serialize_json_ShutdownRequest(Arena *arena, ShutdownRequest *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_integer_field(arena, buf, buf_size, index, "id", data->id, false);
    serialize_string_field(arena, buf, buf_size, index, "jsonrpc", &data->jsonrpc, true);
    serialize_string_field(arena, buf, buf_size, index, "method", &data->method, true);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct ExitNotification {
    JsonString jsonrpc;
    JsonString method;
} ExitNotification;
ExitNotification parse_json_ExitNotification(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    ExitNotification new_struct = {};
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
        else if (is_jsoneq(json, &tokens[*index], "method", 6) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            num_parsed_fields += 1;
            new_struct.method = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
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
void serialize_json_ExitNotification(Arena *arena, ExitNotification *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_string_field(arena, buf, buf_size, index, "jsonrpc", &data->jsonrpc, false);
    serialize_string_field(arena, buf, buf_size, index, "method", &data->method, true);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct TextDocumentItem {
    JsonString uri;
    JsonString languageId;
    long version;
    JsonString text;
} TextDocumentItem;
TextDocumentItem parse_json_TextDocumentItem(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    TextDocumentItem new_struct = {};
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
                fprintf(stderr, "JSON parse error: Expected json type 'i32'\n");
                exit(1);
            } else if (value == LONG_MIN || value == LONG_MAX) {
                fprintf(stderr, "JSON parse error: Expected json type 'i32'\n");
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
void serialize_json_TextDocumentItem(Arena *arena, TextDocumentItem *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_string_field(arena, buf, buf_size, index, "uri", &data->uri, false);
    serialize_string_field(arena, buf, buf_size, index, "languageId", &data->languageId, true);
    serialize_integer_field(arena, buf, buf_size, index, "version", data->version, true);
    serialize_string_field(arena, buf, buf_size, index, "text", &data->text, true);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct DidOpenTextDocumentParams {
    TextDocumentItem textDocument;
} DidOpenTextDocumentParams;
DidOpenTextDocumentParams parse_json_DidOpenTextDocumentParams(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    DidOpenTextDocumentParams new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "textDocument", 12) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.textDocument = parse_json_TextDocumentItem(arena, json, tokens, index);
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
void serialize_json_DidOpenTextDocumentParams(Arena *arena, DidOpenTextDocumentParams *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    *index += snprintf(buf + *index, buf_size - *index, "\"textDocument\":");
    serialize_json_TextDocumentItem(arena, &data->textDocument, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct DidOpenTextDocumentNotification {
    JsonString jsonrpc;
    JsonString method;
    DidOpenTextDocumentParams params;
} DidOpenTextDocumentNotification;
DidOpenTextDocumentNotification parse_json_DidOpenTextDocumentNotification(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    DidOpenTextDocumentNotification new_struct = {};
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
        else if (is_jsoneq(json, &tokens[*index], "method", 6) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            num_parsed_fields += 1;
            new_struct.method = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            *index += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "params", 6) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.params = parse_json_DidOpenTextDocumentParams(arena, json, tokens, index);
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
void serialize_json_DidOpenTextDocumentNotification(Arena *arena, DidOpenTextDocumentNotification *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_string_field(arena, buf, buf_size, index, "jsonrpc", &data->jsonrpc, false);
    serialize_string_field(arena, buf, buf_size, index, "method", &data->method, true);
    *index += snprintf(buf + *index, buf_size - *index, ",\"params\":");
    serialize_json_DidOpenTextDocumentParams(arena, &data->params, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct TextDocument {
    JsonString uri;
} TextDocument;
TextDocument parse_json_TextDocument(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    TextDocument new_struct = {};
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
void serialize_json_TextDocument(Arena *arena, TextDocument *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_string_field(arena, buf, buf_size, index, "uri", &data->uri, false);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct DocumentSymbolsParams {
    TextDocument textDocument;
} DocumentSymbolsParams;
DocumentSymbolsParams parse_json_DocumentSymbolsParams(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    DocumentSymbolsParams new_struct = {};
    int num_children = tokens[*index].size;
    *index += 1;
    long num_parsed_fields = 0;
    for(int i=0;i<num_children;i++) {
        if (is_jsoneq(json, &tokens[*index], "textDocument", 12) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.textDocument = parse_json_TextDocument(arena, json, tokens, index);
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
void serialize_json_DocumentSymbolsParams(Arena *arena, DocumentSymbolsParams *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    *index += snprintf(buf + *index, buf_size - *index, "\"textDocument\":");
    serialize_json_TextDocument(arena, &data->textDocument, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

typedef struct DocumentSymbolsRequest {
    long id;
    JsonString jsonrpc;
    JsonString method;
    DocumentSymbolsParams params;
} DocumentSymbolsRequest;
DocumentSymbolsRequest parse_json_DocumentSymbolsRequest(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {
    DocumentSymbolsRequest new_struct = {};
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
                fprintf(stderr, "JSON parse error: Expected json type 'i32'\n");
                exit(1);
            } else if (value == LONG_MIN || value == LONG_MAX) {
                fprintf(stderr, "JSON parse error: Expected json type 'i32'\n");
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
        else if (is_jsoneq(json, &tokens[*index], "method", 6) && tokens[*index+1].type == JSMN_STRING) {
            *index += 1;
            num_parsed_fields += 1;
            new_struct.method = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };
            *index += 1;
        }
        else if (is_jsoneq(json, &tokens[*index], "params", 6) && tokens[*index+1].type == JSMN_OBJECT) {
            *index += 1;
            new_struct.params = parse_json_DocumentSymbolsParams(arena, json, tokens, index);
            num_parsed_fields += 1;
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
void serialize_json_DocumentSymbolsRequest(Arena *arena, DocumentSymbolsRequest *data, char *buf, const unsigned int buf_size, unsigned int *index) {
    *index += snprintf(buf + *index, buf_size - *index, "{");
    serialize_integer_field(arena, buf, buf_size, index, "id", data->id, false);
    serialize_string_field(arena, buf, buf_size, index, "jsonrpc", &data->jsonrpc, true);
    serialize_string_field(arena, buf, buf_size, index, "method", &data->method, true);
    *index += snprintf(buf + *index, buf_size - *index, ",\"params\":");
    serialize_json_DocumentSymbolsParams(arena, &data->params, buf, buf_size, index);
    *index += snprintf(buf + *index, buf_size - *index, "}");
}

