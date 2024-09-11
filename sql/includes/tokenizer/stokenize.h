#ifndef STOKENIZER_H
#define STOKENIZER_H

#include "assert.h"
#include "constants.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include "../shunting_rpn/new_token/token.h"
#include "state_machine_functions.h"

using namespace std;

class STokenizer
{
public:
    STokenizer();
    STokenizer(char str[]);
    bool done();            //true: there are no more tokens
    bool more();            //true: there are more tokens
    //

    //---------------
    //extract one token (very similar to the way cin >> works)
    friend STokenizer& operator >> (STokenizer& s, Token& t){
        string token;
        int start_state = 0; // Default start state is 0
        if (s.get_token(start_state, token)) { // Start from state 0
            t = Token(token, start_state); // Create a token object with the extracted string
        }
        return s;
    }

    //set a new string as the input string
    void set_string(char str[]);

    int get_post(){
        return _pos;
    }

private:
    //create table for all the tokens we will recognize
    //                      (e.g. doubles, words, etc.)
    void make_table(int _table[][MAX_COLUMNS]);

    //extract the longest string that match
    //     one of the acceptable token types
    bool get_token(int& start_state, string& token);

    bool get_token(char str[], int& pos, int& state, int table[][MAX_COLUMNS], string& t);

    //---------------------------------
    char _buffer[MAX_BUFFER];       //input string
    int _pos;                       //current position in the string
    static int _table[MAX_ROWS][MAX_COLUMNS];
};

#endif