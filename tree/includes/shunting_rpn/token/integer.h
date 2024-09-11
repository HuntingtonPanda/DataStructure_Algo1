#ifndef INTEGER_H
#define INTEGER_H

#include <iostream>
#include <iomanip>
#include "assert.h"

#include "token.h"

class Integer:public Token{
    public:
    //integer type is 1: these are enums!
        Integer(double i=0):Token(to_string(i), INTEGER),_value(i){}
        Integer(string n="0.0"):Token(n, INTEGER), _value(stod(n)){
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