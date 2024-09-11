#ifndef Co_LOGICAL_H
#define Co_LOGICAL_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include "assert.h"

#include "../token/token.h"

using namespace std;

class Logical:public Token{
    public:
    //Logical type is 1: these are enums!
        Logical(double i=0):Token(to_string(i), 1),_value(i){}
        Logical(string n="0.0"):Token(n, INTEGER), _value(stod(n)){
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