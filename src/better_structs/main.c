#include <assert.h>
#include <stdbool.h>
#include <md.h>
#include <md.c>
#include "better_structs.h"

GenerateOptionType(MD_String8);

static MD_Arena *arena = 0;

typedef enum FieldType {
    FIELD_TYPE_I32,
    FIELD_TYPE_F32,
    FIELD_TYPE_BOOL,
    FIELD_TYPE_STRING,
    FIELD_TYPE_STRUCT,
} FieldType;
GenerateOptionType(FieldType);

typedef struct Field {
    bool is_array;
    MD_String8 array_count_name;

    bool is_optional;
    Option(FieldType) type;

    MD_Node *struct_field_type_ref;
    MD_String8 json_name;
    MD_String8 name;
} Field;

typedef struct Struct {
    MD_String8 name;
    unsigned int field_count;
    Field *fields;
} Struct;

typedef struct Enum {
    MD_String8 name;
    Option(MD_String8) tag_name;
    unsigned int variant_count;
    Field *variants;
} Enum;

void write_field_to_file(Field *f, FILE *out_file) {
    if (f->is_array && f->is_optional) {
        fprintf(out_file, "    long %.*s;\n", MD_S8VArg(f->array_count_name));
        switch (f->type.value) {
            case FIELD_TYPE_I32:
                fprintf(out_file, "    Option(long *)");
                break;
            case FIELD_TYPE_F32:
                fprintf(out_file, "    Option(float *)");
                break;
            case FIELD_TYPE_BOOL:
                fprintf(out_file, "    Option(_Bool *)");
                break;
            case FIELD_TYPE_STRING:
                fprintf(out_file, "    Option(JsonString *)");
                break;
            case FIELD_TYPE_STRUCT:
                fprintf(out_file, "    Option(%.*s *)", MD_S8VArg(f->struct_field_type_ref->string));
                break;
        }
    } else if (f->is_optional) {
        switch (f->type.value) {
            case FIELD_TYPE_I32:
                fprintf(out_file, "    Option(long)");
                break;
            case FIELD_TYPE_F32:
                fprintf(out_file, "    Option(float)");
                break;
            case FIELD_TYPE_BOOL:
                fprintf(out_file, "    Option(_Bool)");
                break;
            case FIELD_TYPE_STRING:
                fprintf(out_file, "    Option(JsonString)");
                break;
            case FIELD_TYPE_STRUCT:
                fprintf(out_file, "    Option(%.*s)", MD_S8VArg(f->struct_field_type_ref->string));
                break;
        }
    } else if (f->is_array) {
        fprintf(out_file, "    long %.*s;\n", MD_S8VArg(f->array_count_name));
        switch (f->type.value) {
            case FIELD_TYPE_I32:
                fprintf(out_file, "    long *");
                break;
            case FIELD_TYPE_F32:
                fprintf(out_file, "    float *");
                break;
            case FIELD_TYPE_BOOL:
                fprintf(out_file, "    _Bool *");
                break;
            case FIELD_TYPE_STRING:
                fprintf(out_file, "    JsonString *");
                break;
            case FIELD_TYPE_STRUCT:
                fprintf(out_file, "    %.*s *", MD_S8VArg(f->struct_field_type_ref->string));
                break;
        }
    } else {
        switch (f->type.value) {
            case FIELD_TYPE_I32:
                fprintf(out_file, "    long");
                break;
            case FIELD_TYPE_F32:
                fprintf(out_file, "    float");
                break;
            case FIELD_TYPE_BOOL:
                fprintf(out_file, "    _Bool");
                break;
            case FIELD_TYPE_STRING:
                fprintf(out_file, "    JsonString");
                break;
            case FIELD_TYPE_STRUCT:
                fprintf(out_file, "    %.*s", MD_S8VArg(f->struct_field_type_ref->string));
                break;
        }
    }
    fprintf(out_file, " %.*s;\n", MD_S8VArg(f->name));
}

void write_enum_to_file(Enum *e, FILE *out_file) {
    if (out_file == 0) {
        out_file = stdout;
    }

    // Create discrimination enum
    fprintf(out_file, "typedef enum %.*sVariant {\n", MD_S8VArg(e->name));

    for (int i=0;i<e->variant_count;i++) {
        Field *f = &e->variants[i];

        fprintf(out_file, "    %.*s_%.*s,\n", MD_S8VArg(e->name), MD_S8VArg(f->name));
    }
    fprintf(out_file, "} %.*sVariant;\n", MD_S8VArg(e->name));
    fprintf(out_file, "GenerateOptionType(%.*sVariant);\n", MD_S8VArg(e->name));

    // Create struct that holds the data
    fprintf(out_file, "typedef struct %.*s {\n", MD_S8VArg(e->name));
    fprintf(out_file, "    %.*sVariant type;\n", MD_S8VArg(e->name));
    fprintf(out_file, "    union {\n");
    for (int i=0;i<e->variant_count;i++) {
        Field *f = &e->variants[i];

        if (is_some(f->type)) {
            write_field_to_file(f, out_file);
        }
    }
    fprintf(out_file, "    };\n");
    fprintf(out_file, "} %.*s;\n", MD_S8VArg(e->name));

    fprintf(out_file, "GenerateOptionType(%.*s);\n", MD_S8VArg(e->name));
}

void write_struct_to_file(Struct *s, FILE *out_file) {
    if (out_file == 0) {
        out_file = stdout;
    }

    fprintf(out_file, "typedef struct %.*s {\n", MD_S8VArg(s->name));

    for (int i=0;i<s->field_count;i++) {
        Field *f = &s->fields[i];
        assert(is_some(f->type) && "struct requires type");

        write_field_to_file(f, out_file);
    }
    fprintf(out_file, "} %.*s;\n", MD_S8VArg(s->name));
    fprintf(out_file, "GenerateOptionType(%.*s);\n", MD_S8VArg(s->name));
}

void write_serialized_field_to_file(Field *f, bool leading_comma, bool write_field_name, FILE *out_file) {
    if (f->is_array) {
        if (write_field_name) {
            if (leading_comma) {
                fprintf(out_file, "    *index += snprintf(buf + *index, buf_size - *index, \",\\\"%.*s\\\":[\");\n", MD_S8VArg(f->json_name));
            } else {
                fprintf(out_file, "    *index += snprintf(buf + *index, buf_size - *index, \"\\\"%.*s\\\":[\");\n", MD_S8VArg(f->json_name));
            }
        }
        fprintf(out_file, "    for(int i=0;i<data->%.*s;i++) {\n", MD_S8VArg(f->array_count_name));
        switch (f->type.value) {
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
                fprintf(out_file, "        serialize_string_value(arena, buf, buf_size, index, data->%.*s[i], i > 0);\n", MD_S8VArg(f->name));
                break;
            case FIELD_TYPE_STRUCT:
                fprintf(out_file, "        serialize_json_%.*s(arena, &data->%.*s[i], buf, buf_size, index);\n", MD_S8VArg(f->struct_field_type_ref->string), MD_S8VArg(f->name));
                break;
        }
        fprintf(out_file, "    }\n");
        fprintf(out_file, "    *index += snprintf(buf + *index, buf_size - *index, \"]\");\n");
    } else {
        const char *bool_string = leading_comma ? "true" : "false";

        if (f->is_optional) {
            switch (f->type.value) {
                case FIELD_TYPE_I32:
                    fprintf(out_file, "    serialize_integer_field_optional(arena, buf, buf_size, index, \"%.*s\", data->%.*s, %s);\n", MD_S8VArg(f->json_name), MD_S8VArg(f->name), bool_string);
                    break;
                case FIELD_TYPE_F32:
                    fprintf(out_file, "    serialize_float_field_optional(arena, buf, buf_size, index, \"%.*s\", data->%.*s, %s);\n", MD_S8VArg(f->json_name), MD_S8VArg(f->name), bool_string);
                    break;
                case FIELD_TYPE_BOOL:
                    fprintf(out_file, "    serialize_bool_field_optional(arena, buf, buf_size, index, \"%.*s\", data->%.*s, %s);\n", MD_S8VArg(f->json_name), MD_S8VArg(f->name), bool_string);
                    break;
                case FIELD_TYPE_STRING:
                    fprintf(out_file, "    serialize_string_field_optional(arena, buf, buf_size, index, \"%.*s\", data->%.*s, %s);\n", MD_S8VArg(f->json_name), MD_S8VArg(f->name), bool_string);
                    break;
                case FIELD_TYPE_STRUCT:
                    if (write_field_name) {
                        if (leading_comma) {

                            fprintf(out_file, "    *index += snprintf(buf + *index, buf_size - *index, \",\\\"%.*s\\\":\");\n", MD_S8VArg(f->json_name));
                        } else {
                            fprintf(out_file, "    *index += snprintf(buf + *index, buf_size - *index, \"\\\"%.*s\\\":\");\n", MD_S8VArg(f->json_name));
                        }
                    }
                    fprintf(out_file, "    serialize_json_%.*s_optional(arena, &data->%.*s, buf, buf_size, index);\n", MD_S8VArg(f->struct_field_type_ref->string), MD_S8VArg(f->name));
                    break;
            }
        } else {
            switch (f->type.value) {
                case FIELD_TYPE_I32:
                    fprintf(out_file, "    serialize_integer_field(arena, buf, buf_size, index, \"%.*s\", data->%.*s, %s);\n", MD_S8VArg(f->json_name), MD_S8VArg(f->name), bool_string);
                    break;
                case FIELD_TYPE_F32:
                    fprintf(out_file, "    serialize_float_field(arena, buf, buf_size, index, \"%.*s\", data->%.*s, %s);\n", MD_S8VArg(f->json_name), MD_S8VArg(f->name), bool_string);
                    break;
                case FIELD_TYPE_BOOL:
                    fprintf(out_file, "    serialize_bool_field(arena, buf, buf_size, index, \"%.*s\", data->%.*s, %s);\n", MD_S8VArg(f->json_name), MD_S8VArg(f->name), bool_string);
                    break;
                case FIELD_TYPE_STRING:
                    fprintf(out_file, "    serialize_string_field(arena, buf, buf_size, index, \"%.*s\", data->%.*s, %s);\n", MD_S8VArg(f->json_name), MD_S8VArg(f->name), bool_string);
                    break;
                case FIELD_TYPE_STRUCT:
                    if (write_field_name) {
                        if (leading_comma) {

                            fprintf(out_file, "    *index += snprintf(buf + *index, buf_size - *index, \",\\\"%.*s\\\":\");\n", MD_S8VArg(f->json_name));
                        } else {
                            fprintf(out_file, "    *index += snprintf(buf + *index, buf_size - *index, \"\\\"%.*s\\\":\");\n", MD_S8VArg(f->json_name));
                        }
                    }
                    fprintf(out_file, "    serialize_json_%.*s(arena, &data->%.*s, buf, buf_size, index);\n", MD_S8VArg(f->struct_field_type_ref->string), MD_S8VArg(f->name));
                    break;
            }
        }
    }
}

void write_enum_serializer_to_file(Enum *e, FILE *out_file) {
    if (out_file == 0) {
        out_file = stdout;
    }

    fprintf(out_file, "void serialize_json_%.*s(Arena *arena, %.*s *data, char *buf, const unsigned int buf_size, unsigned int *index) {\n", MD_S8VArg(e->name), MD_S8VArg(e->name));

    fprintf(out_file, "    switch (data->type) {\n");
    for (int i=0;i<e->variant_count;i++) {
        Field *f = &e->variants[i];

        fprintf(out_file, "        case %.*s_%.*s:\n", MD_S8VArg(e->name), MD_S8VArg(f->name));
        if (is_some(f->type)) {
            write_serialized_field_to_file(f, i>0, false, out_file);

            if (is_some(e->tag_name)) {
                fprintf(out_file, "            *index += snprintf(buf + *index, buf_size - *index, \",\\\"%.*s\\\": \\\"%.*s\\\"\");\n", MD_S8VArg(e->tag_name.value), MD_S8VArg(f->json_name));
            }
        } else if (is_some(e->tag_name)) {
            fprintf(out_file, "            *index += snprintf(buf + *index, buf_size - *index, \"null\");\n");
            fprintf(out_file, "            *index += snprintf(buf + *index, buf_size - *index, \",\\\"%.*s\\\": \\\"%.*s\\\"\");\n", MD_S8VArg(e->tag_name.value), MD_S8VArg(f->json_name));
        } else {
            fprintf(out_file, "            *index += snprintf(buf + *index, buf_size - *index, \"\\\"%.*s\\\"\");\n", MD_S8VArg(f->json_name));
        }

        fprintf(out_file, "    break;\n");
    }
    fprintf(out_file, "    }\n");

    fprintf(out_file, "}\n");
    fprintf(out_file, "GenerateOptionStructSerializeFunc(serialize_json_%.*s, %.*s);\n", MD_S8VArg(e->name), MD_S8VArg(e->name));
}

void write_struct_serializer_to_file(Struct *s, FILE *out_file) {
    if (out_file == 0) {
        out_file = stdout;
    }

    fprintf(out_file, "void serialize_json_%.*s(Arena *arena, %.*s *data, char *buf, const unsigned int buf_size, unsigned int *index) {\n", MD_S8VArg(s->name), MD_S8VArg(s->name));
    fprintf(out_file, "    *index += snprintf(buf + *index, buf_size - *index, \"{\");\n");

    for (int i=0;i<s->field_count;i++) {
        Field *f = &s->fields[i];
        assert(is_some(f->type) && "struct requires type");

        write_serialized_field_to_file(f, i!=0, true, out_file);
    }

    fprintf(out_file, "    *index += snprintf(buf + *index, buf_size - *index, \"}\");\n");
    fprintf(out_file, "}\n");
    fprintf(out_file, "GenerateOptionStructSerializeFunc(serialize_json_%.*s, %.*s);\n", MD_S8VArg(s->name), MD_S8VArg(s->name));
}

void write_field_parser_to_file(Field *f, MD_String8 field_parent_name, bool check_field_name, FILE *out_file) {
    if (out_file == 0) {
        out_file = stdout;
    }

    if (f->is_array) {
        switch (f->type.value) {
            case FIELD_TYPE_I32:
                if (check_field_name) {
                    fprintf(out_file,
                            "if (is_jsoneq(json, &tokens[*index], \"%.*s\", %llu) && tokens[*index+1].type == JSMN_ARRAY) {\n", MD_S8VArg(f->name), f->name.size);
                }
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
                        "                        fprintf(stderr, \"JSON parse error: errno!=0: Expected json type 'i32' for '%.*s', found object\\n\");\n"
                        "                        exit(1);\n"
                        "                    } else if (value == LONG_MIN || value == LONG_MAX) {\n"
                        "                        fprintf(stderr, \"JSON parse error: value==MAX: Expected json type 'i32' for '%.*s', found object\\n\");\n"
                        "                        exit(1);\n"
                        "                    }\n\n"
                        "                    *index += 1;\n"
                        "                    new_struct.%.*s[i] = value;\n"
                        "                } else {\n"
                        "                    fprintf(stderr, \"JSON parse error: Expected json type 'i32' for '%.*s', found object\\n\");\n"
                        "                    exit(1);\n"
                        "                }\n"
                        , MD_S8VArg(f->name), MD_S8VArg(f->name), MD_S8VArg(f->name), MD_S8VArg(f->name));

                fprintf(out_file,
                        "            }\n"
                        "            num_parsed_fields += 1;\n");

                if (check_field_name) {
                    fprintf(out_file,
                            "        }\n");
                }
                break;
            case FIELD_TYPE_F32:
                if (check_field_name) {
                    fprintf(out_file,
                            "if (is_jsoneq(json, &tokens[*index], \"%.*s\", %llu) && tokens[*index+1].type == JSMN_ARRAY) {\n", MD_S8VArg(f->name), f->name.size);
                }
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
                        "            num_parsed_fields += 1;\n");

                if (check_field_name) {
                    fprintf(out_file,
                            "        }\n");
                }
                break;
            case FIELD_TYPE_BOOL:
                if (check_field_name) {
                    fprintf(out_file, "if (is_jsoneq(json, &tokens[*index], \"%.*s\", %llu) && tokens[*index+1].type == JSMN_ARRAY) {\n", MD_S8VArg(f->name), f->name.size);
                }
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
                        "            num_parsed_fields += 1;\n");

                if (check_field_name) {
                    fprintf(out_file,
                            "        }\n");
                }
                break;
            case FIELD_TYPE_STRING:
                if (check_field_name) {
                    fprintf(out_file,
                            "if (is_jsoneq(json, &tokens[*index], \"%.*s\", %llu) && tokens[*index+1].type == JSMN_ARRAY) {\n", MD_S8VArg(f->name), f->name.size);
                }
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
                        "            num_parsed_fields += 1;\n");

                if (check_field_name) {
                    fprintf(out_file,
                            "        }\n");
                }
                break;
            case FIELD_TYPE_STRUCT:
                if (check_field_name) {
                    fprintf(out_file,
                            "if (is_jsoneq(json, &tokens[*index], \"%.*s\", %llu) && tokens[*index+1].type == JSMN_ARRAY) {\n", MD_S8VArg(f->name), f->name.size);
                }
                fprintf(out_file,
                        "            const int array_size = tokens[*index+1].size;\n"
                        "            *index += 2;\n"
                        "            new_struct.%.*s = arena_allocate_block(arena, sizeof(%.*s) * array_size);\n"
                        "            new_struct.%.*s = array_size;\n"
                        "            for (int i=0;i<array_size;i++) {\n"
                        , MD_S8VArg(f->name), MD_S8VArg(f->struct_field_type_ref->string), MD_S8VArg(f->array_count_name));

                fprintf(out_file,
                        "                if(tokens[*index].type == JSMN_OBJECT) {\n"
                        "                    Option(%.*s) parsed_struct = parse_json_%.*s(arena, json, tokens, index, this_index);\n"
                        "                    if (is_none(parsed_struct)) {\n"
                        "                        fprintf(stderr, \"JSON Parse Error: failed to parse object %.*s in array\\n\");\n"
                        "                        return None(%.*s);\n"
                        "                    }\n"
                        "                    new_struct.%.*s[i] = parsed_struct.value;\n"
                        "                } else {\n"
                        "                    fprintf(stderr, \"JSON parse error: Expected json type '%.*s' in array '%.*s'\\n\");\n"
                        "                    exit(1);\n"
                        "                }\n"
                        , MD_S8VArg(f->struct_field_type_ref->string), MD_S8VArg(f->struct_field_type_ref->string), MD_S8VArg(f->struct_field_type_ref->string), MD_S8VArg(field_parent_name), MD_S8VArg(f->name), MD_S8VArg(f->struct_field_type_ref->string), MD_S8VArg(f->name));

                fprintf(out_file,
                        "            }\n"
                        "            num_parsed_fields += 1;\n");

                if (check_field_name) {
                    fprintf(out_file,
                            "        }\n");
                }
                break;
        }
    } else {
        switch (f->type.value) {
            case FIELD_TYPE_I32:
                if (check_field_name) {
                    fprintf(out_file,
                            "if (is_jsoneq(json, &tokens[*index], \"%.*s\", %llu) && tokens[*index+1].type == JSMN_PRIMITIVE) {\n", MD_S8VArg(f->name), f->name.size);
                }
                fprintf(out_file, "            *index += 1;\n");
                fprintf(out_file,
                        "            long value = 0;\n"
                        "            errno = 0;\n"
                        "            value = strtol(json + tokens[*index].start, 0, 10);\n"
                        "            if (errno != 0 && value == 0) {\n"
                        "                fprintf(stderr, \"JSON parse error: errno!=0: Expected json type 'i32'\\n\");\n"
                        "                exit(1);\n"
                        "            } else if (value == LONG_MIN || value == LONG_MAX) {\n"
                        "                fprintf(stderr, \"JSON parse error: value==MAX: Expected json type 'i32'\\n\");\n"
                        "                exit(1);\n"
                        "            }\n\n"
                        "            *index += 1;\n");

                if (f->is_optional) {
                    fprintf(out_file,
                            "            new_struct.%.*s = Some(long, value);\n",
                            MD_S8VArg(f->name));
                } else {
                    fprintf(out_file,
                            "            new_struct.%.*s = value;\n",
                            MD_S8VArg(f->name));
                    fprintf(out_file, "            num_parsed_fields += 1;\n");
                }

                if (check_field_name) {
                    fprintf(out_file, "    }\n");
                }
                break;
            case FIELD_TYPE_F32:
                if (check_field_name) {
                    fprintf(out_file,
                            "if (is_jsoneq(json, &tokens[*index], \"%.*s\", %llu) && tokens[*index+1].type == JSMN_PRIMITIVE) {\n", MD_S8VArg(f->name), f->name.size);
                }
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
                        "            *index += 1;\n");

                if (f->is_optional) {
                    fprintf(out_file,
                            "            new_struct.%.*s = Some(float, value);\n" ,
                            MD_S8VArg(f->name));
                } else {
                    fprintf(out_file,
                            "            new_struct.%.*s = value;\n" ,
                            MD_S8VArg(f->name));
                    fprintf(out_file, "            num_parsed_fields += 1;\n");
                }

                if (check_field_name) {
                    fprintf(out_file, "    }\n");
                }
                break;
            case FIELD_TYPE_BOOL:
                if (check_field_name) {
                    fprintf(out_file,
                            "if (is_jsoneq(json, &tokens[*index], \"%.*s\", %llu) && tokens[*index+1].type == JSMN_PRIMITIVE) {\n", MD_S8VArg(f->name), f->name.size);
                }
                fprintf(out_file, "            *index += 1;\n");
                fprintf(out_file,
                        "            char text = json[tokens[*index].start];\n"
                        "            if (text != 't' && text != 'f') {\n"
                        "                fprintf(stderr, \"JSON parse error: Expected json type 'bool'\\n\");\n"
                        "                exit(1);\n"
                        "            }\n\n"
                        "            *index += 1;\n");

                if (f->is_optional) {
                    fprintf(out_file,
                            "            new_struct.%.*s = Some(_Bool, text == 't');\n" ,
                            MD_S8VArg(f->name));
                } else {
                    fprintf(out_file,
                            "            new_struct.%.*s = text == 't';\n",
                            MD_S8VArg(f->name));
                    fprintf(out_file, "            num_parsed_fields += 1;\n");
                }

                if (check_field_name) {
                    fprintf(out_file, "    }\n");
                }
                break;
            case FIELD_TYPE_STRING:
                if (check_field_name) {
                    fprintf(out_file,
                            "if (is_jsoneq(json, &tokens[*index], \"%.*s\", %llu) && tokens[*index+1].type == JSMN_STRING) {\n", MD_S8VArg(f->name), f->name.size);
                }
                fprintf(out_file,
                        "            *index += 1;\n");

                if (f->is_optional) {
                    fprintf(out_file,
                            "            new_struct.%.*s = Some(JsonString, ((JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start }));\n", MD_S8VArg(f->name));
                } else {
                    fprintf(out_file,
                            "            new_struct.%.*s = (JsonString){ tokens[*index].end - tokens[*index].start, json+tokens[*index].start };\n", MD_S8VArg(f->name));
                    fprintf(out_file, "            num_parsed_fields += 1;\n");
                }

                fprintf(out_file,
                        "            *index += 1;\n");
                if (check_field_name) {
                    fprintf(out_file, "        }\n");
                }
                break;
            case FIELD_TYPE_STRUCT:
                if (check_field_name) {
                    fprintf(out_file,
                            "if (is_jsoneq(json, &tokens[*index], \"%.*s\", %llu) && tokens[*index+1].type == JSMN_OBJECT) {\n", MD_S8VArg(f->name), f->name.size);
                }
                fprintf(out_file,
                        "            *index += 1;\n");

                fprintf(out_file,
                        "            Option(%.*s) parsed_struct = parse_json_%.*s(arena, json, tokens, index, this_index);\n"
                        "            if (is_none(parsed_struct)) {\n"
                        "                fprintf(stderr, \"JSON Parse Error: failed to parse object %.*s\\n\");\n"
                        "                return None(%.*s);\n"
                        "            }\n"
                        , MD_S8VArg(f->struct_field_type_ref->string), MD_S8VArg(f->struct_field_type_ref->string), MD_S8VArg(f->struct_field_type_ref->string), MD_S8VArg(field_parent_name));

                if (f->is_optional) {
                    fprintf(out_file,
                            "            new_struct.%.*s = parsed_struct;\n"
                            , MD_S8VArg(f->name));
                } else {
                    fprintf(out_file,
                            "            new_struct.%.*s = parsed_struct.value;\n"
                            , MD_S8VArg(f->name));
                    fprintf(out_file, "            num_parsed_fields += 1;\n");
                }

                if (check_field_name) {
                    fprintf(out_file, "        }\n");
                }
                break;
        }
    }
}

void write_struct_parser_to_file(Struct *s, FILE *out_file) {
    if (out_file == 0) {
        out_file = stdout;
    }

    fprintf(out_file, "Option(%.*s) parse_json_%.*s(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index, unsigned int parent_index) {\n", MD_S8VArg(s->name), MD_S8VArg(s->name));
    fprintf(out_file, "    int this_index = *index;\n");
    fprintf(out_file, "    %.*s new_struct = {};\n", MD_S8VArg(s->name));
    fprintf(out_file, "    int num_children = tokens[*index].size;\n    *index += 1;\n");
    fprintf(out_file, "    long num_parsed_fields = 0;\n");

    int num_required_fields = 0;
    for (int i=0;i<s->field_count;i++) {
        Field *f = &s->fields[i];
        assert(is_some(f->type) && "struct requires type");

        if (f->is_optional == false) {
            // TODO
            // fprintf(out_file, "    new_struct.%.*s = None(long);\n", MD_S8VArg(f->name));
            num_required_fields += 1; 
        }

    }

    fprintf(out_file, "    for(int i=0;i<num_children;i++) {\n");
    for (int i=0;i<s->field_count;i++) {
        Field *f = &s->fields[i];
        assert(is_some(f->type) && "struct requires type");

        if (i > 0) {
            fprintf(out_file, "        else ");
        } else {
            fprintf(out_file, "        ");
        }

        // TODO: check for duplicate fields
        write_field_parser_to_file(f, s->name, true, out_file);
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
            "        fprintf(stderr, \"JSON parse error: Expected %d fields, got %%ld for %.*s\\n\", num_parsed_fields);\n"
            "        return None(%.*s);\n"
            "    }\n"
            , num_required_fields, num_required_fields, MD_S8VArg(s->name), MD_S8VArg(s->name));
    fprintf(out_file, "\n    return Some(%.*s, new_struct);\n", MD_S8VArg(s->name));
    fprintf(out_file, "}\n");
}

// FIXME: this will only work for structs variants
void write_enum_parser_to_file(Enum *e, FILE *out_file) {
    if (out_file == 0) {
        out_file = stdout;
    }


    fprintf(out_file, "Option(%.*sVariant) %.*sVariant_from_string(JsonString json_tag) {\n", MD_S8VArg(e->name), MD_S8VArg(e->name));
    for (int i=0;i<e->variant_count;++i) {
        Field *f = &e->variants[i];
        if (i > 0) {
            fprintf(out_file, "    else ");
        } else {
            fprintf(out_file, "    ");
        }

        fprintf(out_file, "if (MatchString(MakeString(\"%.*s\"), json_tag)) {\n", MD_S8VArg(f->json_name));
        fprintf(out_file, "        return Some(%.*sVariant, %.*s_%.*s);\n", MD_S8VArg(e->name), MD_S8VArg(e->name), MD_S8VArg(f->name));
        fprintf(out_file, "    }\n");
    }
    fprintf(out_file, "    return None(%.*sVariant);\n", MD_S8VArg(e->name));
    fprintf(out_file, "}\n");

    fprintf(out_file, "Option(%.*s) parse_json_%.*s(Arena *arena, const char *json, const jsmntok_t *tokens, unsigned int *index, unsigned int parent_index) {\n", MD_S8VArg(e->name), MD_S8VArg(e->name));
    fprintf(out_file, "    int this_index = *index;\n");
    fprintf(out_file, "    %.*s new_struct = {};\n", MD_S8VArg(e->name));
    fprintf(out_file, "    int num_children = tokens[*index].size;\n");
    fprintf(out_file, "    long num_parsed_fields = 0;\n");

    if (is_some(e->tag_name)) {
        // Find the enum tag from the parent object
        fprintf(out_file, "    int num_parent_children = tokens[parent_index].size;\n    parent_index += 1;\n");
        fprintf(out_file, "    bool found_enum_tag = false;\n");
        fprintf(out_file, "    for(int i=0;i<num_parent_children;i++) {\n");
        fprintf(out_file,
                "        if (is_jsoneq(json, &tokens[parent_index], \"%.*s\", %llu) && tokens[parent_index+1].type == JSMN_STRING) {\n", MD_S8VArg(e->tag_name.value), e->tag_name.value.size);
        fprintf(out_file, "            parent_index += 1;\n");
        fprintf(out_file, "            JsonString variant_name = (JsonString){ tokens[parent_index].end - tokens[parent_index].start, json+tokens[parent_index].start };\n");
        fprintf(out_file, "            Option(%.*sVariant) variant = %.*sVariant_from_string(variant_name);\n", MD_S8VArg(e->name), MD_S8VArg(e->name));
        fprintf(out_file, "            if (is_some(variant)) {\n");
        fprintf(out_file, "                new_struct.type = variant.value;\n");
        //fprintf(out_file,
        //        "            new_struct.%.*s = (JsonString){ tokens[parent_index].end - tokens[parent_index].start, json+tokens[parent_index].start };\n", MD_S8VArg(e->name));
        fprintf(out_file, "                found_enum_tag = true;\n");
        fprintf(out_file, "            } else { printf(\"no variant %%.*s for %.*sVariant\", variant_name.length, variant_name.text); exit(1); }\n", MD_S8VArg(e->name));
        fprintf(out_file, "        } else if (tokens[parent_index+1].type == JSMN_OBJECT || tokens[parent_index+1].type == JSMN_ARRAY) {\n"
            "        parent_index += 1;\n"
            "        json_skip_object(json, tokens, &parent_index, tokens[parent_index].type == JSMN_ARRAY);\n"
            "    } else {\n"
            "        parent_index += 2;\n"
            "    }\n");
        fprintf(out_file, "    }\n");

        bool already_if = false;
        for (int i=0;i<e->variant_count;i++) {
            Field *f = &e->variants[i];

            if (is_some(f->type)) {
                if (already_if) {
                    fprintf(out_file, "    else ");
                } else {
                    already_if = true;
                    fprintf(out_file, "    ");
                }
                fprintf(out_file, "if (new_struct.type == %.*s_%.*s) {\n", MD_S8VArg(e->name), MD_S8VArg(f->name));

                // TODO: check for duplicate fields
                write_field_parser_to_file(f, e->name, false, out_file);

                fprintf(out_file, "\n    return Some(%.*s, new_struct);\n", MD_S8VArg(e->name));
                fprintf(out_file, "    }\n");
            }
        }
    } else {
        for (int i=0;i<e->variant_count;i++) {
            Field *f = &e->variants[i];

            fprintf(out_file, "    {\n");
            fprintf(out_file,
                    "        Option(%.*s) parsed_struct = None(%.*s);\n"
                    , MD_S8VArg(f->struct_field_type_ref->string), MD_S8VArg(f->struct_field_type_ref->string));

            fprintf(out_file,
                    "        parsed_struct = parse_json_%.*s(arena, json, tokens, index, this_index);\n"
                    "        if (is_some(parsed_struct)) {\n"
                    "            new_struct.type = %.*s_%.*s;\n"
                    "            new_struct.%.*s = parsed_struct.value;\n"
                    "            return Some(%.*s, new_struct);\n"
                    "        }\n"
                    "        *index = parent_index;\n"
                    "    }\n"
                    , MD_S8VArg(f->struct_field_type_ref->string), MD_S8VArg(e->name), MD_S8VArg(f->name), MD_S8VArg(f->name), MD_S8VArg(e->name));
        }
    }

    fprintf(out_file,
            "    if (tokens[*index+1].type == JSMN_OBJECT || tokens[*index+1].type == JSMN_ARRAY) {\n"
            "        *index += 1;\n"
            "        json_skip_object(json, tokens, index, tokens[*index].type == JSMN_ARRAY);\n"
            "    } else {\n"
            "        *index += 2;\n"
            "    }\n");
    fprintf(out_file, "\n    return None(%.*s);\n", MD_S8VArg(e->name));
    fprintf(out_file, "}\n");
}

Field generate_field(MD_Arena *arena, MD_Node *node) {
    Field new_field = {0};
    new_field.name = node->string;

    MD_Node *rename_tag = MD_TagFromString(node, MD_S8Lit("jsonRename"), 0);
    if(!MD_NodeIsNil(rename_tag)) {
        new_field.json_name = rename_tag->first_child->string;
    } else {
        new_field.json_name = node->string;
    }

    MD_Node *type_node = node->first_child;
    if (!MD_NodeIsNil(type_node)) {
        MD_Node *option_tag = MD_TagFromString(type_node, MD_S8Lit("option"), 0);
        new_field.is_optional = !MD_NodeIsNil(option_tag);

        MD_Node *array_tag = MD_TagFromString(type_node, MD_S8Lit("array"), 0);
        if (!MD_NodeIsNil(array_tag)) {
            new_field.is_array = true;
            new_field.array_count_name = array_tag->first_child->string;
        }

        if (MD_S8Match(type_node->string, MD_S8Lit("i32"), 0)) {
            new_field.type = Some(FieldType, FIELD_TYPE_I32);
        } else if (MD_S8Match(type_node->string, MD_S8Lit("f32"), 0)) {
            new_field.type = Some(FieldType, FIELD_TYPE_F32);
        } else if (MD_S8Match(type_node->string, MD_S8Lit("bool"), 0)) {
            new_field.type = Some(FieldType, FIELD_TYPE_BOOL);
        } else if (MD_S8Match(type_node->string, MD_S8Lit("string"), 0)) {
            new_field.type = Some(FieldType, FIELD_TYPE_STRING);
        } else {
            new_field.type = Some(FieldType, FIELD_TYPE_STRUCT);
            new_field.struct_field_type_ref = type_node;
        }
    } else {
        new_field.type = None(FieldType);
    }

    return new_field;
}

Enum generate_enum(MD_Arena *arena, MD_Node *node) {
    unsigned int num_variants = MD_ChildCountFromNode(node);
    unsigned int current_variant = 0;

    Option(MD_String8) tag_name = None(MD_String8);
    MD_Node *tag_node = MD_TagFromString(node, MD_S8Lit("enum"), 0);
    if (!MD_NodeIsNil(tag_node) && !MD_NodeIsNil(tag_node->first_child)) {
        tag_name = Some(MD_String8, tag_node->first_child->string);
    }

    Enum new_enum = {
        node->string,
        tag_name,
        num_variants,
        MD_PushArray(arena, Field, num_variants)
    };

    for (MD_EachNode(enum_variant, node->first_child)) {
        new_enum.variants[current_variant] = generate_field(arena, enum_variant);
        current_variant += 1;
    }

    return new_enum;
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
        new_struct.fields[current_field] = generate_field(arena, struct_field);
        current_field += 1;
    }

    return new_struct;
}

void generate_types(MD_Node *root, const char *output_path) {
    MD_Arena *arena = MD_ArenaAlloc();

    unsigned int current_struct = 0;
    unsigned int num_structs = MD_ChildCountFromNode(root);
    Struct *structs = MD_PushArray(arena, Struct, num_structs);

    unsigned int current_enum = 0;
    unsigned int num_enums = MD_ChildCountFromNode(root);
    Enum *enums = MD_PushArray(arena, Enum, num_enums);

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
            "#include <better_structs/json.h>\n\n"
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
        if (MD_NodeHasTag(node, MD_S8Lit("struct"), 0)) {
            structs[current_struct] = generate_struct(arena, node);
            write_struct_to_file(&structs[current_struct], file);
            write_struct_parser_to_file(&structs[current_struct], file);
            write_struct_serializer_to_file(&structs[current_struct], file);
            fprintf(file, "\n");

            current_struct += 1;
        }
        else if (MD_NodeHasTag(node, MD_S8Lit("enum"), 0)) {
            enums[current_enum] = generate_enum(arena, node);
            write_enum_to_file(&enums[current_enum], file);
            write_enum_parser_to_file(&enums[current_enum], file);
            write_enum_serializer_to_file(&enums[current_enum], file);
            fprintf(file, "\n");

            current_enum += 1;
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
