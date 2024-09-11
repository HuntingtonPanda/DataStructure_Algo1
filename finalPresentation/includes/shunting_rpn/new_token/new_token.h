#ifndef Co_NEW_TOKEN_H
#define Co_NEW_TOKEN_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include "assert.h"

#include "TokenType.h"
#include "token.h"
#include "../../table/typedefs.h"

using namespace std;

class TokenStr:public Token{
    public:
    //TokenStr type is 1: these are enums!
        TokenStr(string n="0.0"):Token(n, STRING), word(n){
            //or stod
        }

        string get_string(){
            return word;
        }
    private:
    string word;
};

class RecordSet:public Token{
    public:
    RecordSet(vectorlong n = {}):_record_set(n), Token("FUCK", RECSET){

    }

    void set_records(vectorlong n){
        _record_set.resize(n.size());
        _record_set = n;
    }

    vectorlong& get_records(){
        return _record_set;
    }

    private:
    vectorlong _record_set;

};

class Logical:public Token{
    public:
    //Logical type is 1: these are enums!
        Logical(string n):Token(n, LOGICAL){
            //or stod
            logic = n;
            _prec = 16; // Wikipedia said this
            //_prec = find_prec(n);

            if(n == "and"){
                logicType = AND;
                _prec = 2;
            }else if(n == "or"){
                logicType = OR;
                _prec = 1;
            }else {
                logicType = _TOKEN_UNKNOWN;
            }
        }

        string get_logic(){
            return logic;
        }
        
        int get_logicType(){
            return logicType;
        }

        int get_prec(){
            return _prec;
        }

        void print()const{cout << logic;}
    private:
        string logic;
        
        int logicType;
        int _prec;
};


class Relational:public Token{
    public:
    //Relational type is 1: these are enums!
        Relational(string n):Token(n, RELATIONAL){
            //or stod
            relation = n;
            _prec = 16; // Wikipedia said this
            //_prec = find_prec(n);

            if(n == "="){
                relationType = EQ;
            }else if(n == ">"){
                relationType = G;
            }else if(n == ">="){
                relationType = GE;
            }else if(n == "<"){
                relationType = L;
            }else if(n == "<="){
                relationType = LE;
            }
        }

        // vectorlong get_records(TokenStr first, TokenStr second){
            

        // }

        string get_relation(){
            return relation;
        }

        int get_relationType(){
            return relationType;
        }

        int get_prec(){
            return _prec;
        }

        void print()const{cout << relation;}
    private:
        string relation;
        
        int relationType;
        int _prec;
};





#endif