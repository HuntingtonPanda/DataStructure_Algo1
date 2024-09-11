#ifndef Co_TOKENTYPE_H
#define Co_TOKENTYPE_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include "assert.h"

using namespace std;

enum TokenType{
    TOKEN,
    LEFTPARENTH,
    RIGHTPARENTH,
    TOKEN_STR,
    OPERATOR,

    RECSET,

    LOGICAL,
    AND,
    OR,


    RELATIONAL,
    EQ,
    G,
    GE,
    L,
    LE,

    STRING,

    RESULT_SET,
    TOKEN_NUMBER,
    TOKEN_ALPHA,
    TOKEN_SPACE,
    TOKKEN_OPERATOR,
    TOKEN_PUNC,

    TOKEN_UNKNOWN,
    TOKEN_END
};


#endif