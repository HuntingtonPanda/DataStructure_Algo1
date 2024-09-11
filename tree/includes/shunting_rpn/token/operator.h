#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include "assert.h"

#include "token.h"
#include "integer.h"
#include "constant.h"

class Operator:public Token{
    public:
    //integer type is 1: these are enums!
        Operator(string op):Token(op, OPERATION){
            //or stod
            oper = op;
            _prec = find_prec(op);
        }
        //const string& op
        int find_prec(const string& op){
            switch(token()[0]){
                case '+': return PLUS;
                case '-': return MINUS;

                case '*': return MULTI;
                case '/': return DIV;

                case '^': return 4;

            }

            return -1;
        }

        int get_prec(){
            return _prec;
        }

        void print()const{cout << oper;}

        Token* eval(Token* right, Token* left){
            Integer* l = static_cast<Integer*> (left);
            Integer* r = static_cast<Integer*> (right);


            double num_1 = l->getVal();
            double num_2 = r->getVal();

            switch(token()[0]){
                case '+': return new Integer(num_1 + num_2);
                          
                case '-': return new Integer(num_1 - num_2);
                          

                case '*': return new Integer(num_1 * num_2);
                          
                case '/': return new Integer(num_1 / num_2);
                          

                case '^': return new Integer(pow(num_1, num_2));
                          
                default:
                        assert(false);
            }
        }
    private:
        string oper;
        int _prec;
};

#endif