#ifndef __C_BETTER_STRUCTS_HEADER__
#define __C_BETTER_STRUCTS_HEADER__

#include <stdbool.h>
#include <arena/arena.h>

typedef enum {
    OPTION_NONE,
    OPTION_SOME,
} OptionValue;

#define Option(T) struct T ## Option
#define GenerateOptionType(T) Option(T){\
    OptionValue option_value;\
    T value;\
};\
Option(T) T ## None(){\
    Option(T) this;\
    this.option_value = OPTION_NONE;\
    return this;\
}\
Option(T) T ## Some(T value){\
    Option(T) this;\
    this.option_value = OPTION_SOME;\
    this.value = value;\
    return this;\
}
#define Some(T, value) T ## Some(value)
#define None(T) T ## None()
#define is_some(value) value.option_value==OPTION_SOME
#define is_none(value) value.option_value==OPTION_NONE
#define match_option(T, value, some_block, none_block) \
    if (is_some(value)) some_block \
    else if (is_none(value)) none_block

typedef struct JsonString {
    unsigned int length;
    const char *text;
} JsonString;

#define MakeString(string) ((JsonString) { strlen(string), string })

GenerateOptionType(char);
GenerateOptionType(int);
GenerateOptionType(long);
GenerateOptionType(_Bool);
GenerateOptionType(float);
GenerateOptionType(JsonString);

JsonString escape_string(Arena *arena, JsonString string) {
    int num_escaped = 0;
    int num_control_codes = 0;

    for(int i=0;i<string.length;++i) {
        if (string.text[i] == '"' || string.text[i] == '\\') {
            num_escaped += 1;
        }
        else if(string.text[i] == '\r' || string.text[i] == '\n') {
            num_control_codes += 1;
        }
    }

    JsonString escaped = (JsonString) { string.length+num_escaped+(num_control_codes*2), NULL };
    char *text = arena_allocate_block(arena, sizeof(char)*escaped.length);

    int index = 0;
    for(int i=0;i<string.length;++i) {
        if (string.text[i] == '"' || string.text[i] == '\\') {
            text[index] = '\\';
            index += 1;
        }
        else if(string.text[i] == '\n') {
            text[index] = '\\';
            text[index+1] = 'n';

            index += 2;

            continue;
        } else if (string.text[i] == '\r') {
            continue;
        }

        text[index] = string.text[i];

        index += 1;
    }

    //printf("string: %.*s, escaped length: %d\n", string.length, text, escaped.length);
    escaped.text = text;

    return escaped;
}

#define GenerateOptionSerializeFunc(func_name, type) \
    void func_name ## _optional(Arena *arena, char *buf, const unsigned int buf_size, unsigned int *index, const char *field_name, const Option(type) value, const bool leading_comma) {\
        if (is_some(value)) {\
            func_name(arena, buf, buf_size, index, field_name, value.value, leading_comma);\
        }\
    }
#define GenerateOptionStructSerializeFunc(func_name, type) \
    void func_name ## _optional(Arena *arena, Option(type) *value, char *buf, const unsigned int buf_size, unsigned int *index) {\
        if (is_some((*value))) {\
            func_name(arena, &value->value, buf, buf_size, index);\
        } else {\
            *index += snprintf(buf + *index, buf_size - *index, "null");\
        }\
    }

void serialize_integer_value(Arena *arena, char *buf, const unsigned int buf_size, unsigned int *index, const long value, const bool leading_comma) {
    *index += snprintf(buf + *index, buf_size - *index, "%s%ld", leading_comma ? "," : "", value);
}

void serialize_float_value(Arena *arena, char *buf, const unsigned int buf_size, unsigned int *index, const float value, const bool leading_comma) {
    *index += snprintf(buf + *index, buf_size - *index, "%s\"%f\"", leading_comma ? "," : "", value);
}

void serialize_bool_value(Arena *arena, char *buf, const unsigned int buf_size, unsigned int *index, const bool value, const bool leading_comma) {
    *index += snprintf(buf + *index, buf_size - *index, "%s%s", leading_comma ? "," : "", value ? "true" : "false");
}

void serialize_string_value(Arena *arena, char *buf, const unsigned int buf_size, unsigned int *index, const JsonString value, const bool leading_comma) {
    JsonString escaped_value = escape_string(arena, value);
    *index += snprintf(buf + *index, buf_size - *index, "%s\"%.*s\"", leading_comma ? "," : "", escaped_value.length, escaped_value.text);
}

void serialize_integer_field(Arena *arena, char *buf, const unsigned int buf_size, unsigned int *index, const char *field_name, const long value, const bool leading_comma) {
    *index += snprintf(buf + *index, buf_size - *index, "%s\"%s\":", leading_comma ? "," : "", field_name);
    serialize_integer_value(arena, buf, buf_size, index, value, false);
}
GenerateOptionSerializeFunc(serialize_integer_field, long);

void serialize_float_field(Arena *arena, char *buf, const unsigned int buf_size, unsigned int *index, const char *field_name, const float value, const bool leading_comma) {
    *index += snprintf(buf + *index, buf_size - *index, "%s\"%s\":", leading_comma ? "," : "", field_name);
    serialize_float_value(arena, buf, buf_size, index, value, false);
}
GenerateOptionSerializeFunc(serialize_float_field, float);

void serialize_bool_field(Arena *arena, char *buf, const unsigned int buf_size, unsigned int *index, const char *field_name, const bool value, const bool leading_comma) {
    *index += snprintf(buf + *index, buf_size - *index, "%s\"%s\":", leading_comma ? "," : "", field_name);
    serialize_bool_value(arena, buf, buf_size, index, value, false);
}
GenerateOptionSerializeFunc(serialize_bool_field, bool);

void serialize_string_field(Arena *arena, char *buf, const unsigned int buf_size, unsigned int *index, const char *field_name, const JsonString value, const bool leading_comma) {
    *index += snprintf(buf + *index, buf_size - *index, "%s\"%s\":", leading_comma ? "," : "", field_name);
    serialize_string_value(arena, buf, buf_size, index, value, false);
}
GenerateOptionSerializeFunc(serialize_string_field, JsonString);

bool is_jsoneq(const char *json, const jsmntok_t *token, const char *str, const unsigned int str_len) {
    const int token_size = token->end - token->start;

    //printf("attempting to match struct field '%.*s' with json field '%.*s'\n", str_len, str, token_size, json+token->start);

    if (token_size != str_len) {
        //printf("token->type: %d, token length: %u, token->size: %d, str_len: %u\n", token->type, token_size, token->size, str_len);
        return false;
    };

    for (int i=0;i<token_size;i++) {
        if (json[token->start+i] != str[i]) {
            return false;
        }
    }

    return true;
}

#endif
