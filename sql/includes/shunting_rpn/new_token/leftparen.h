#ifndef LEFTPAREN_H
#define LEFTPAREN_H

#include <iostream>
#include <iomanip>
#include "assert.h"

#include "token.h"

class LeftParen:public Token{
    public:
        LeftParen(const string& n="("):Token(n, LEFTPARENTH){}
};

#endif