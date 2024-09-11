#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <iomanip>
#include "assert.h"

#include "../node/node.h"
#include "TokenType.h"
#include "../../tokenizer/constants.h"
//#include "constant.h"

class Token
{
    //I know what my type is, I know what my face looks like.
    public:
        Token(const string& s="?", int type = TOKEN):_token(s), _type(type){}
        string type_string() const{
            string type = "";
            switch(_type){
                case MAKE:
                    type = "make";
                    break;
                case TABLE: 
                    type = "table";
                    break;
                case TABLE_NAME: 
                    type = "table_name";
                    break;
                case FIELDS: 
                    type = "fields";
                    break;
                case COL: 
                    type = "col";
                    break;
                case COMMA: 
                    type = "comma";
                    break;
                case INSERT: 
                    type = "insert";
                    break;
                case INTO: 
                    type = "into";
                    break;
                case VALUES: 
                    type = "values";
                    break;
                case VALS: 
                    type = "vals";
                    break;
                case SELECT: 
                    type = "select";
                    break;
                case FIELDS_LIST: 
                    type = "fields_list";
                    break;
                case STAR: 
                    type = "star";
                    break;
                case FROM: 
                    type = "from";
                    break;
                case WHERE: 
                    type = "where";
                    break;
                case CONDITIONS: 
                    type = "conditions";
                    break;
                case CREATE: 
                    type = "create";
                    break;
            }
            return type;
        }
        
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