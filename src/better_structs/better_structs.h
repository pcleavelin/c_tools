#ifndef __C_BETTER_STRUCTS_HEADER__
#define __C_BETTER_STRUCTS_HEADER__

#include <stdbool.h>

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

#endif
