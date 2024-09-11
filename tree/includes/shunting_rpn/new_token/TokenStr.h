#ifndef Co_TOKENSTR_H
#define Co_TOKENSTR_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include "assert.h"

#include "../token/token.h"

using namespace std;

class TokenStr:public Token{
    public:
    //TokenStr type is 1: these are enums!
        TokenStr(double i=0):Token(to_string(i), 1),_value(i){}
        TokenStr(string n="0.0"):Token(n, INTEGER), _value(stod(n)){
            //or stod
        }

        double getVal(){
            return _value;
        }
        void print()const{cout << _value;}
    private:
        double _value;
};



#endif