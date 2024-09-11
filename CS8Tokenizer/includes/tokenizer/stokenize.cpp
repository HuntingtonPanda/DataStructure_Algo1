#include "stokenize.h"
using namespace std;

int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

STokenizer::STokenizer():_pos(0), _buffer(""){
    make_table(_table);
    //print_table(_table);
}
STokenizer::STokenizer(char str[]):_pos(0), _buffer(""){
    assert(strlen(str) <= MAX_BUFFER);
    make_table(_table);
    //print_table(_table);
    strcpy(_buffer, str);
}
bool STokenizer::done(){
    return _pos >= strlen(_buffer);
}            //true: there are no more tokens
bool STokenizer::more(){
    return _pos <= strlen(_buffer);
}            //true: there are more tokens

//set a new string as the input string
void STokenizer::set_string(char str[]){
    assert(strlen(str) <= MAX_BUFFER);
    strcpy(_buffer, str);
}

    //create table for all the tokens we will recognize
    //                      (e.g. doubles, words, etc.)
void STokenizer::make_table(int _table[][MAX_COLUMNS]){
    init_table(_table);
    
    mark_fail(_table, 0);
    mark_success(_table, 1);
    mark_success(_table, 2);
    mark_success(_table, 3);
    mark_success(_table, 4);
    mark_success(_table, 5);
    mark_fail(_table, 6);
    mark_success(_table, 7);

    //ROW 0
    mark_cells(0, _table, DIGITS, 1);
    mark_cells(0, _table, ALFA, 2);
    mark_cell(0, _table, ' ', 3);
    mark_cells(0, _table, OPERATORS, 4);
    mark_cells(0, _table, PUNC, 5);

    //ROW 1
    mark_cells(1, _table, DIGITS, 1);
    mark_cell(1, _table, '.', 6);

    //ROW 2
    mark_cells(2, _table, ALFA, 2);

    //ROW 3

    //ROW 4

    //ROW 5

    //ROW 6
    mark_cells(6, _table, DIGITS, 7);

    //ROW 7
    mark_cells(7, _table, DIGITS, 7);
}

//extract the longest string that match
//     one of the acceptable token types

// bool STokenizer::get_token(int& start_state, string& token){
//     int current_state = 0;
//     int last_success = -1;
//     int last_success_state = 0;
//     int start_pos = _pos;

//     while (more()) {
//         char current_char = _buffer[_pos];

//         int next_state = _table[current_state][static_cast<int>(current_char)];
//         if(_pos == strlen(_buffer) && is_success(_table, next_state)){
//             token = string(_buffer + start_pos, _buffer + last_success);
//             start_state = last_success_state;
//             _pos = last_success;
//             //cout << _buffer[last_success];     
//             return true; 
//         } 
//         ++_pos;
//         // || _buffer[_pos] == '\n'
//         if (next_state == -1) {
//             break;
//         }

        
//         //|| (_buffer[_pos] == NULL && is_success(_table, next_state))
//         if (is_success(_table, next_state) ) {
//             last_success = _pos;
//             last_success_state = next_state;

//         }

//         current_state = next_state;
//     }
//     //|| (_buffer[_pos] == NULL && last_success != -1 )
//     if (last_success != -1 ) {
//         token = string(_buffer + start_pos, _buffer + last_success);
//         start_state = last_success_state;
//         _pos = last_success;
//         //cout << _buffer[last_success];

//         return true;
//     }
    

//     return false; 
// }

//V.2

//extract the longest string that match one of the acceptable token types
bool STokenizer::get_token(int& start_state, string& token){
    return get_token(_buffer, _pos, start_state, _table, token);
}

bool STokenizer::get_token(char str[], int& pos, int& state, int table[][MAX_COLUMNS], string& t){
    int temp_state = -1;
    int temp_pos = pos;
    string possibleString = "";

    while(more())    
    {
        if (str[pos] < 0 || str[pos] > 127){
            if (possibleString == ""){
                pos++;
                continue;
            }
            else{
               t = possibleString;
               pos++;
               return true;
            }
        }
        
        state = table[state][str[pos]]; 

        if (pos == strlen(str)){
            if (is_success(table, state)){
                state = temp_state; 
                t = possibleString;
                return true;
            }
            else{
                state = temp_state;
                t = possibleString; 
                pos = temp_pos;
                if (t == ""){pos++;}
                return true;
            }
        }

        if (state == -1){
            state = temp_state;  
            pos = temp_pos;
            t = possibleString;
            break;
        }

        t += str[pos];
        pos++; 

        if (is_success(table, state)){
            temp_state = state;
            temp_pos = pos;
            possibleString = t;
        }  
    }

    if (state == -1){
        t = "";
        return false;
    }
    else
        return true;
}









//---------------------------------
