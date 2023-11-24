#include <stdbool.h>
#include <md.h>
#include <md.c>

static MD_Arena *arena = 0;

typedef enum FieldType {
    FIELD_TYPE_I32,
    FIELD_TYPE_F32,
    FIELD_TYPE_BOOL,
    FIELD_TYPE_STRING,
    FIELD_TYPE_STRUCT,
} FieldType;

typedef struct Field {
    bool is_array;
    MD_String8 array_count_name;

    bool is_optional;
    FieldType type;

    MD_Node *struct_field_type_ref;
    MD_String8 name;
} Field;

typedef struct Struct {
    MD_String8 name;
    unsigned int field_count;
    Field *fields;
} Struct;

void write_struct_to_file(Struct *s, FILE *out_file) {
    if (out_file == 0) {
        out_file = stdout;
    }

    fprintf(out_file, "typedef struct %.*s {\n", MD_S8VArg(s->name));

    for (int i=0;i<s->field_count;i++) {
        Field *f = &s->fields[i];

        // TODO: implement generated Option<T>'s
        if (f->is_optional) {
            fprintf(out_file, "    bool %.*s_is_some;\n", MD_S8VArg(f->name));
        }

        if (f->is_array) {
            fprintf(out_file, "    long %.*s;\n", MD_S8VArg(f->array_count_name));
            switch (f->type) {
                case FIELD_TYPE_I32:
                    fprintf(out_file, "    long *%.*s;\n", MD_S8VArg(f->name));
                    break;
                case FIELD_TYPE_F32:
                    fprintf(out_file, "    float *%.*s;\n", MD_S8VArg(f->name));
                    break;
                case FIELD_TYPE_BOOL:
                    fprintf(out_file, "    bool *%.*s;\n", MD_S8VArg(f->name));
                    break;
                case FIELD_TYPE_STRING:
                    fprintf(out_file, "    JsonString *%.*s;\n", MD_S8VArg(f->name));
                    break;
                case FIELD_TYPE_STRUCT:
                    fprintf(out_file, "    %.*s *%.*s;\n", MD_S8VArg(f->struct_field_type_ref->string), MD_S8VArg(f->name));
                    break;
            }
        } else {
            switch (f->type) {
                case FIELD_TYPE_I32:
                    fprintf(out_file, "    long %.*s;\n", MD_S8VArg(f->name));
                    break;
                case FIELD_TYPE_F32:
                    fprintf(out_file, "    float %.*s;\n", MD_S8VArg(f->name));
                    break;
                case FIELD_TYPE_BOOL:
                    fprintf(out_file, "    bool %.*s;\n", MD_S8VArg(f->name));
                    break;
                case FIELD_TYPE_STRING:
                    fprintf(out_file, "    JsonString %.*s;\n", MD_S8VArg(f->name));
                    break;
                case FIELD_TYPE_STRUCT:
                    fprintf(out_file, "    %.*s %.*s;\n", MD_S8VArg(f->struct_field_type_ref->string), MD_S8VArg(f->name));
                    break;
            }
        }
    }
    fprintf(out_file, "} %.*s;\n", MD_S8VArg(s->name));
}

void write_struct_serializer_to_file(Struct *s, FILE *out_file) {
    if (out_file == 0) {
        out_file = stdout;
    }

    fprintf(out_file, "void serialize_json_%.*s(Arena *arena, %.*s *data, char *buf, const unsigned int buf_size, unsigned int *index) {\n", MD_S8VArg(s->name), MD_S8VArg(s->name));
    fprintf(out_file, "    *index += snprintf(buf + *index, buf_size - *index, \"{\");\n");

    for (int i=0;i<s->field_count;i++) {
        Field *f = &s->fields[i];

        if (f->is_array) {
            if (i > 0) {
                fprintf(out_file, "    *index += snprintf(buf + *index, buf_size - *index, \",\\\"%.*s\\\":[\");\n", MD_S8VArg(f->name));
            } else {
                fprintf(out_file, "    *index += snprintf(buf + *index, buf_size - *index, \"\\\"%.*s\\\":[\");\n", MD_S8VArg(f->name));
            }
            fprintf(out_file, "    for(int i=0;i<data->%.*s;i++) {\n", MD_S8VArg(f->array_count_name));
            switch (f->type) {
                case FIELD_TYPE_I32:
                    fprintf(out_file, "        serialize_integer_value(arena, buf, buf_size, index, data->%.*s[i], i > 0);\n", MD_S8VArg(f->name));
                    break;
                case FIELD_TYPE_F32:
                    fprintf(out_file, "        serialize_float_value(arena, buf, buf_size, index, data->%.*s[i], i > 0);\n", MD_S8VArg(f->name));
                    break;
                case FIELD_TYPE_BOOL:
                    fprintf(out_file, "        serialize_bool_value(arena, buf, buf_size, index, data->%.*s[i], i > 0);\n", MD_S8VArg(f->name));
                    break;
                case FIELD_TYPE_STRING:
                    fprintf(out_file, "        serialize_string_value(arena, buf, buf_size, index, &data->%.*s[i], i > 0);\n", MD_S8VArg(f->name));
                    break;
                case FIELD_TYPE_STRUCT:
                    fprintf(out_file, "        serialize_json_%.*s(arena, &data->%.*s[i], buf, buf_size, index);\n", MD_S8VArg(f->struct_field_type_ref->string), MD_S8VArg(f->name));
                    break;
            }
            fprintf(out_file, "    }\n");
            fprintf(out_file, "    *index += snprintf(buf + *index, buf_size - *index, \"]\");\n");
        } else {
            const char *leading_comma = i > 0 ? "true" : "false";

            switch (f->type) {
                case FIELD_TYPE_I32:
                    fprintf(out_file, "    serialize_integer_field(arena, buf, buf_size, index, \"%.*s\", data->%.*s, %s);\n", MD_S8VArg(f->name), MD_S8VArg(f->name), leading_comma);
                    break;
                case FIELD_TYPE_F32:
                    fprintf(out_file, "    serialize_float_field(arena, buf, buf_size, index, \"%.*s\", data->%.*s, %s);\n", MD_S8VArg(f->name), MD_S8VArg(f->name), leading_comma);
                    break;
                case FIELD_TYPE_BOOL:
                    fprintf(out_file, "    serialize_bool_field(arena, buf, buf_size, index, \"%.*s\", data->%.*s, %s);\n", MD_S8VArg(f->name), MD_S8VArg(f->name), leading_comma);
                    break;
                case FIELD_TYPE_STRING:
                    fprintf(out_file, "    serialize_string_field(arena, buf, buf_size, index, \"%.*s\", &data->%.*s, %s);\n", MD_S8VArg(f->name), MD_S8VArg(f->name), leading_comma);
                    break;
                case FIELD_TYPE_STRUCT:
                    if (i > 0) {

                        fprintf(out_file, "    *index += snprintf(buf + *index, buf_size - *index, \",\\\"%.*s\\\":\");\n", MD_S8VArg(f->name));
                    } else {
                        fprintf(out_file, "    *index += snprintf(buf + *index, buf_size - *index, \"\\\"%.*s\\\":\");\n", MD_S8VArg(f->name));
                    }
                    fprintf(out_file, "    serialize_json_%.*s(arena, &data->%.*s, buf, buf_size, index);\n", MD_S8VArg(f->struct_field_type_ref->string), MD_S8VArg(f->name));
                    break;
            }

        }

    }

    fprintf(out_file, "    *index += snprintf(buf + *index, buf_size - *index, \"}\");\n");
    fprintf(out_file, "}\n");
}

void write_struct_parser_to_file(Struct *s, FILE *out_file) {
    if (out_file == 0) {
        out_file = stdout;
    }

    fprintf(out_file, "%.*s parse_json_%.*s(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index) {\n", MD_S8VArg(s->name), MD_S8VArg(s->name));
    fprintf(out_file, "    %.*s new_struct = {};\n", MD_S8VArg(s->name));
    fprintf(out_file, "    int num_children = tokens[*index].size;\n    *index += 1;\n");
    fprintf(out_file, "    long num_parsed_fields = 0;\n");
    fprintf(out_file, "    for(int i=0;i<num_children;i++) {\n");

    for (int i=0;i<s->field_count;i++) {
        Field *f = &s->fields[i];

        if (f->is_optional) {
            // fprintf(out_file, "    bool %.*s_is_some;\n", MD_S8VArg(f->name));
        }

        if (i > 0) {
            fprintf(out_file, "        else ");
        } else {
            fprintf(out_file, "        ");
        }

        // TODO: check for duplicate fields
        if (f->is_array) {
            switch (f->type) {
                case FIELD_TYPE_I32:
                    fprintf(out_file,
                        "if (is_jsoneq(json, &tokens[*index], \"%.*s\", %llu) && tokens[*index+1].type == JSMN_ARRAY) {\n", MD_S8VArg(f->name), f->name.size);
                    fprintf(out_file,
                        "            const int array_size = tokens[*index+1].size;\n"
                        "            *index += 2;\n"
                        "            new_struct.%.*s = arena_allocate_block(arena, sizeof(long) * array_size);\n"
                        "            new_struct.%.*s = array_size;\n"
                        "            for (int i=0;i<array_size;i++) {\n"
                    , MD_S8VArg(f->name), MD_S8VArg(f->array_count_name));

                    fprintf(out_file,
                        "                if(tokens[*index].type == JSMN_PRIMITIVE) {\n"
                        "                    long value = 0;\n"
                        "                    errno = 0;\n"
                        "                    value = strtol(json + tokens[*index].start, 0, 10);\n"
                        "                    if (errno != 0 && value == 0) {\n"
                        "                        fprintf(stderr, \"JSON parse error: Expected json type 'i32' for '%.*s'\\n\");\n"
                        "                        exit(1);\n"
                        "                    } else if (value == LONG_MIN || value == LONG_MAX) {\n"
                        "                        fprintf(stderr, \"JSON parse error: Expected json type 'i32' for '%.*s'\\n\");\n"
                        "                        exit(1);\n"
                        "                    }\n\n"
                        "                    *index += 1;\n"
                        "                    new_struct.%.*s[i] = value;\n"
                        "                } else {\n"
                        "                    fprintf(stderr, \"JSON parse error: Expected json type 'i32' for '%.*s'\\n\");\n"
                        "                    exit(1);\n"
                        "                }\n"
                    , MD_S8VArg(f->name), MD_S8VArg(f->name), MD_S8VArg(f->name), MD_S8VArg(f->name));

                    fprintf(out_file,
                        "            }\n"
                        "            num_parsed_fields += 1;\n"
                        "        }\n");
                    break;
                case FIELD_TYPE_F32:
                    fprintf(out_file,
                        "if (is_jsoneq(json, &tokens[*index], \"%.*s\", %llu) && tokens[*index+1].type == JSMN_ARRAY) {\n", MD_S8VArg(f->name), f->name.size);
                    fprintf(out_file,
                        "            const int array_size = tokens[*index+1].size;\n"
                        "            *index += 2;\n"
                        "            new_struct.%.*s = arena_allocate_block(arena, sizeof(float) * array_size);\n"
                        "            new_struct.%.*s = array_size;\n"
                        "            for (int i=0;i<array_size;i++) {\n"
                    , MD_S8VArg(f->name), MD_S8VArg(f->array_count_name));

                    fprintf(out_file,
                        "                if(tokens[*index].type == JSMN_PRIMITIVE) {\n"
                        "                    float value = 0;\n"
                        "                    errno = 0;\n"
                        "                    value = strtof(json + tokens[*index].start, 0);\n"
                        "                    if (errno != 0 && value == 0.0f) {\n"
                        "                        fprintf(stderr, \"JSON parse error: Expected json type 'f32' in array '%.*s'\\n\");\n"
                        "                        exit(1);\n"
                        "                    } else if (value == HUGE_VALF) {\n"
                        "                        fprintf(stderr, \"JSON parse error: Expected json type 'f32' in array '%.*s'\\n\");\n"
                        "                        exit(1);\n"
                        "                    }\n\n"
                        "                    *index += 1;\n"
                        "                    new_struct.%.*s[i] = value;\n"
                        "                } else {\n"
                        "                    fprintf(stderr, \"JSON parse error: Expected json type 'f32' for '%.*s'\\n\");\n"
                        "                    exit(1);\n"
                        "                }\n"
                    , MD_S8VArg(f->name), MD_S8VArg(f->name), MD_S8VArg(f->name), MD_S8VArg(f->name));

                    fprintf(out_file,
                        "            }\n"
                        "            num_parsed_fields += 1;\n"
                        "        }\n");
                    break;
                case FIELD_TYPE_BOOL:
                    fprintf(out_file,
                        "if (is_jsoneq(json, &tokens[*index], \"%.*s\", %llu) && tokens[*index+1].type == JSMN_ARRAY) {\n", MD_S8VArg(f->name), f->name.size);
                    fprintf(out_file,
                        "            const int array_size = tokens[*index+1].size;\n"
                        "            *index += 2;\n"
                        "            new_struct.%.*s = arena_allocate_block(arena, sizeof(bool) * array_size);\n"
                        "            new_struct.%.*s = array_size;\n"
                        "            for (int i=0;i<array_size;i++) {\n"
                    , MD_S8VArg(f->name), MD_S8VArg(f->array_count_name));

                    fprintf(out_file,
                        "                if(tokens[*index].type == JSMN_PRIMITIVE) {\n"
                        "                    char text = json[tokens[*index].start];\n"
                        "                    if (text != 't' && text != 'f') {\n"
                        "                        fprintf(stderr, \"JSON parse error: Expected json type 'bool' in array %.*s\\n\");\n"
                        "                        exit(1);\n"
                        "                    }\n\n"
                        "                    *index += 1;\n"
                        "                    new_struct.%.*s[i] = text == 't';\n"
                        "                } else {\n"
                        "                    fprintf(stderr, \"JSON parse error: Expected json type 'f32' for '%.*s'\\n\");\n"
                        "                    exit(1);\n"
                        "                }\n"
                    , MD_S8VArg(f->name), MD_S8VArg(f->name), MD_S8VArg(f->name));

                    fprintf(out_file,
                        "            }\n"
                        "            num_parsed_fields += 1;\n"
                        "        }\n");
                    break;
                case FIELD_TYPE_STRING:
                    fprintf(out_file,
                        "if (is_jsoneq(json, &tokens[*index], \"%.*s\", %llu) && tokens[*index+1].type == JSMN_ARRAY) {\n", MD_S8VArg(f->name), f->name.size);
                    fprintf(out_file,
                        "            const int array_size = tokens[*index+1].size;\n"
                        "            *index += 2;\n"
                        "            new_struct.%.*s = arena_allocate_block(arena, sizeof(JsonString) * array_size);\n"
                        "            new_struct.%.*s = array_size;\n"
                        "            for (int i=0;i<array_size;i++) {\n"
                    , MD_S8VArg(f->name), MD_S8VArg(f->array_count_name));

                    fprintf(out_file,
                        "                if(tokens[*index].type == JSMN_STRING) {\n"
                        "                    new_struct.%.*s[i] = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };\n"
                        "                    *index += 1;\n"
                        "                } else {\n"
                        "                    fprintf(stderr, \"JSON parse error: Expected json type 'string' in array '%.*s'\\n\");\n"
                        "                    exit(1);\n"
                        "                }\n"
                    , MD_S8VArg(f->name), MD_S8VArg(f->name));

                    fprintf(out_file,
                        "            }\n"
                        "            num_parsed_fields += 1;\n"
                        "        }\n");
                    break;
                case FIELD_TYPE_STRUCT:
                    fprintf(out_file,
                        "if (is_jsoneq(json, &tokens[*index], \"%.*s\", %llu) && tokens[*index+1].type == JSMN_ARRAY) {\n", MD_S8VArg(f->name), f->name.size);
                    fprintf(out_file,
                        "            const int array_size = tokens[*index+1].size;\n"
                        "            *index += 2;\n"
                        "            new_struct.%.*s = arena_allocate_block(arena, sizeof(%.*s) * array_size);\n"
                        "            new_struct.%.*s = array_size;\n"
                        "            for (int i=0;i<array_size;i++) {\n"
                    , MD_S8VArg(f->name), MD_S8VArg(f->struct_field_type_ref->string), MD_S8VArg(f->array_count_name));

                    fprintf(out_file,
                        "                if(tokens[*index].type == JSMN_OBJECT) {\n"
                        "                    new_struct.%.*s[i] = parse_json_%.*s(arena, json, tokens, index);\n"
                        "                } else {\n"
                        "                    fprintf(stderr, \"JSON parse error: Expected json type '%.*s' in array '%.*s'\\n\");\n"
                        "                    exit(1);\n"
                        "                }\n"
                    , MD_S8VArg(f->name), MD_S8VArg(f->struct_field_type_ref->string), MD_S8VArg(f->struct_field_type_ref->string), MD_S8VArg(f->name));

                    fprintf(out_file,
                        "            }\n"
                        "            num_parsed_fields += 1;\n"
                        "        }\n");
                    break;
            }
        } else {
            switch (f->type) {
                case FIELD_TYPE_I32:
                    fprintf(out_file,
                        "if (is_jsoneq(json, &tokens[*index], \"%.*s\", %llu) && tokens[*index+1].type == JSMN_PRIMITIVE) {\n", MD_S8VArg(f->name), f->name.size);
                    fprintf(out_file, "            *index += 1;\n");
                    fprintf(out_file,
                        "            long value = 0;\n"
                        "            errno = 0;\n"
                        "            value = strtol(json + tokens[*index].start, 0, 10);\n"
                        "            if (errno != 0 && value == 0) {\n"
                        "                fprintf(stderr, \"JSON parse error: Expected json type 'i32'\\n\");\n"
                        "                exit(1);\n"
                        "            } else if (value == LONG_MIN || value == LONG_MAX) {\n"
                        "                fprintf(stderr, \"JSON parse error: Expected json type 'i32'\\n\");\n"
                        "                exit(1);\n"
                        "            }\n\n"
                        "            *index += 1;\n"
                        "            num_parsed_fields += 1;\n"
                        "            new_struct.%.*s = value;\n"
                        "        }\n", MD_S8VArg(f->name));
                    break;
                case FIELD_TYPE_F32:
                    fprintf(out_file,
                        "if (is_jsoneq(json, &tokens[*index], \"%.*s\", %llu) && tokens[*index+1].type == JSMN_PRIMITIVE) {\n", MD_S8VArg(f->name), f->name.size);
                    fprintf(out_file, "            *index += 1;\n");
                    fprintf(out_file,
                        "            float value = 0;\n"
                        "            errno = 0;\n"
                        "            value = strtof(json + tokens[*index].start, 0);\n"
                        "            if (errno != 0 && value == 0.0f) {\n"
                        "                fprintf(stderr, \"JSON parse error: Expected json type 'f32'\\n\");\n"
                        "                exit(1);\n"
                        "            } else if (value == HUGE_VALF) {\n"
                        "                fprintf(stderr, \"JSON parse error: Expected json type 'f32'\\n\");\n"
                        "                exit(1);\n"
                        "            }\n\n"
                        "            *index += 1;\n"
                        "            num_parsed_fields += 1;\n"
                        "            new_struct.%.*s = value;\n"
                        "        }\n", MD_S8VArg(f->name));
                    break;
                case FIELD_TYPE_BOOL:
                    fprintf(out_file,
                        "if (is_jsoneq(json, &tokens[*index], \"%.*s\", %llu) && tokens[*index+1].type == JSMN_PRIMITIVE) {\n", MD_S8VArg(f->name), f->name.size);
                    fprintf(out_file, "            *index += 1;\n");
                    fprintf(out_file,
                        "            char text = json[tokens[*index].start];\n"
                        "            if (text != 't' && text != 'f') {\n"
                        "                fprintf(stderr, \"JSON parse error: Expected json type 'bool'\\n\");\n"
                        "                exit(1);\n"
                        "            }\n\n"
                        "            *index += 1;\n"
                        "            num_parsed_fields += 1;\n"
                        "            new_struct.%.*s = text == 't';\n"
                        "        }\n", MD_S8VArg(f->name));
                    break;
                case FIELD_TYPE_STRING:
                    fprintf(out_file,
                        "if (is_jsoneq(json, &tokens[*index], \"%.*s\", %llu) && tokens[*index+1].type == JSMN_STRING) {\n", MD_S8VArg(f->name), f->name.size);
                    fprintf(out_file,
                        "            *index += 1;\n"
                        "            num_parsed_fields += 1;\n"
                        "            new_struct.%.*s = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };\n"
                        "            *index += 1;\n"
                        "        }\n", MD_S8VArg(f->name));
                    break;
                case FIELD_TYPE_STRUCT:
                    fprintf(out_file,
                        "if (is_jsoneq(json, &tokens[*index], \"%.*s\", %llu) && tokens[*index+1].type == JSMN_OBJECT) {\n", MD_S8VArg(f->name), f->name.size);
                    fprintf(out_file,
                        "            *index += 1;\n"
                        "            new_struct.%.*s = parse_json_%.*s(arena, json, tokens, index);\n"
                        "            num_parsed_fields += 1;\n"
                        "        }\n", MD_S8VArg(f->name), MD_S8VArg(f->struct_field_type_ref->string));
                    break;
            }
        }
    }
    // TODO: skip unknown item
    if (s->field_count > 0) {
        fprintf(out_file,"        else");
    }

    fprintf(out_file,
            " if (tokens[*index+1].type == JSMN_OBJECT || tokens[*index+1].type == JSMN_ARRAY) {\n"
            //"            printf(\"skipping object: %%.*s\\n\", tokens[*index].end - tokens[*index].start, json+tokens[*index].start);\n"
            "            *index += 1;\n"
            "            json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);\n"
            "        } else {\n"
            //"            printf(\"skipping field: %%.*s\\n\", tokens[*index].end - tokens[*index].start, json+tokens[*index].start);\n"
            "            *index += 2;\n"
            "        }\n"
            "    }\n\n");
    fprintf(out_file,
            "    if (num_parsed_fields != %d) {\n"
            "        fprintf(stderr, \"JSON parse error: Expected %d fields, got %%ld\\n\", num_parsed_fields);\n"
            "    }\n"
            , s->field_count, s->field_count);
    fprintf(out_file, "\n    return new_struct;\n");
    fprintf(out_file, "}\n");
}

Struct generate_struct(MD_Arena *arena, MD_Node *node) {
    unsigned int num_fields = MD_ChildCountFromNode(node);
    unsigned int current_field = 0;
    Struct new_struct = {
        node->string,
        num_fields,
        MD_PushArray(arena, Field, num_fields)
    };

    for (MD_EachNode(struct_field, node->first_child)) {
        MD_Node *field_child = struct_field->first_child;
        Field new_field = {};
        new_field.name = struct_field->string;

        MD_Node *option_tag = MD_TagFromString(field_child, MD_S8Lit("option"), 0);
        new_field.is_optional = !MD_NodeIsNil(option_tag);

        MD_Node *array_tag = MD_TagFromString(field_child, MD_S8Lit("array"), 0);
        if (!MD_NodeIsNil(array_tag)) {
            new_field.is_array = true;
            new_field.array_count_name = array_tag->first_child->string;
        }

        if (MD_S8Match(field_child->string, MD_S8Lit("i32"), 0)) {
            new_field.type = FIELD_TYPE_I32;
        } else if (MD_S8Match(field_child->string, MD_S8Lit("f32"), 0)) {
            new_field.type = FIELD_TYPE_F32;
        } else if (MD_S8Match(field_child->string, MD_S8Lit("bool"), 0)) {
            new_field.type = FIELD_TYPE_BOOL;
        } else if (MD_S8Match(field_child->string, MD_S8Lit("string"), 0)) {
            new_field.type = FIELD_TYPE_STRING;
        } else {
            new_field.type = FIELD_TYPE_STRUCT;
            new_field.struct_field_type_ref = field_child;
        }

        new_struct.fields[current_field] = new_field;
        current_field += 1;
    }

   return new_struct;
}

void generate_types(MD_Node *root, const char *output_path) {
    MD_Arena *arena = MD_ArenaAlloc();

    unsigned int current_struct = 0;
    unsigned int num_structs = MD_ChildCountFromNode(root);
    Struct *structs = MD_PushArray(arena, Struct, num_structs);

    FILE *file = fopen(output_path, "w");
    if (file) {
        fprintf(file,
            "// DO NOT EDIT - This file was automatically generated\n"
            "\n"
            "#include <stdio.h>\n"
            "#include <errno.h>\n"
            "#include <limits.h>\n"
            "#include <math.h>\n"
            "#include <jsmn.h>\n"
            "#include <better_structs/better_structs.h>\n\n"
            "static void json_skip_object(const char *json, const jsmntok_t *tokens, unsigned int *index, bool is_array) {\n"
            "    const int num_children = tokens[*index].size;\n"
            "    // if the object was empty\n"
            "    if (num_children == 0) {\n"
            "        *index += 1;\n"
            "        return;\n"
            "    }\n"
            "    // move into the object\n"
            "    *index += 1;\n"
            "    for (int i=0; i<num_children; i++) {\n"
            "        // Look at the field value\n"
            "        if (!is_array) {\n"
            "            *index += 1;\n"
            "        }\n"
            "        if (tokens[*index].type == JSMN_OBJECT || tokens[*index].type == JSMN_ARRAY) {\n"
            "            json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);\n"
            "        } else {\n"
            "            *index += 1;\n"
            "        }\n"
            "    }\n"
            "}\n");

    }

    for(MD_EachNode(node, root->first_child)) {
        MD_Node *struct_tag = MD_TagFromString(node, MD_S8Lit("struct"), 0);
        if (!MD_NodeIsNil(struct_tag)) {
            structs[current_struct] = generate_struct(arena, node);
            write_struct_to_file(&structs[current_struct], file);
            write_struct_parser_to_file(&structs[current_struct], file);
            write_struct_serializer_to_file(&structs[current_struct], file);
            fprintf(file, "\n");

            current_struct += 1;
        }
    }

    if (file != NULL) {
        fflush(file);
        fclose(file);
    }
}

int get_file_name_index_without_extension(const char *filename) {
    const int len = strlen(filename);

    int i=len-1;
    for (; i>=0; --i) {
        if (filename[i] == '.') {
            break;
        }
    }

    return i;
}

int main(int argc, char *argv[]) {
    arena = MD_ArenaAlloc();

    if (argc > 1) {
        for (int i=1; i<argc; ++i) {
            MD_String8 file_Name = MD_S8CString(argv[i]);
            MD_ParseResult parse_result = MD_ParseWholeFile(arena, file_Name);

            for (MD_Message *message = parse_result.errors.first;
                    message!= 0;
                    message = message->next)
            {
                MD_CodeLoc code_loc = MD_CodeLocFromNode(message->node);
                MD_PrintMessage(stdout, code_loc, message->kind, message->string);
            }

            int file_name_index = get_file_name_index_without_extension(argv[i]);
            char new_file_name[2048];
            sprintf(new_file_name, "%.*s.h", file_name_index, argv[i]);

            generate_types(parse_result.node, new_file_name);
        }
    }
}
