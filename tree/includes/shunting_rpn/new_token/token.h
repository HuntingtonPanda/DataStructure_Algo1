#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <iomanip>
#include "assert.h"

#include "../node/node.h"
#include "TokenType.h"
//#include "constant.h"

class Token
{
    //I know what my type is, I know what my face looks like.
    public:
        Token(const string& s="?", int type = TOKEN):_token(s), _type(type){}
        virtual void Print(ostream& outs){
            // switch(_type){

            //     case 1: outs << "Integer: ";
            //         break;

            //     case 2: outs << "Operator: ";
            //         break;

            //     case 3: outs << "Function: ";
            //         break;
                
            //     default: break;
            // }        

            outs << "[ " << _token << " token]";
        }
        virtual int type(){return _type;}
        virtual void print()const{}

        friend ostream& operator << (ostream& outs, const Token* token){
            token->print();
            return outs;
        }
        friend ostream& operator << (ostream& outs, const Token& token){
            token.print();
            return outs;
        }
        string token(){return _token;}


    private:
    int _type;
    string _token;
};

#endif