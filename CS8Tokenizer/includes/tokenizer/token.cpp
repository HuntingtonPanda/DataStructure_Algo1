#include "token.h"
#include "constants.h"
using namespace std;

Token::Token():_token(""), _type(-1){}
Token::Token(string str, int type):_token(str), _type(type){}
int Token::type() const{return _type;}
string Token::type_string() const{
    string type = "";
    switch(_type){
        case TOKEN_NUMBER:
        case 7: 
            type = "NUMBER";
            break;
        case TOKEN_ALPHA: 
            type = "ALPHA";
            break;
        case TOKEN_SPACE: 
            type = "SPACE";
            break;
        case TOKEN_OPERATOR: 
            type = "OPERATOR";
            break;
        case TOKEN_PUNC: 
            type = "PUNC";
            break;
        case TOKEN_UNKNOWN: 
            type = "UNKNOWN";
            break;
        case TOKEN_END: 
            type = "END";
            break;
    }
    return type;
}
string Token::token_str() const{return _token;}