#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>

typedef enum{
    tok_str,
    tok_num,
    tok_reserved,
    tok_name,
    tok_operator,
    tok_separator
} Token;

const char* tokenStrings[6] = {
    "niz",
    "stevilo",
    "rezerviranka",
    "ime",
    "operator",
    "locilo",
};

const char* reservedKeywords[7] = {
    "int",
    "char",
    "if",
    "else",
    "for",
    "return",
    "while",
};

#endif