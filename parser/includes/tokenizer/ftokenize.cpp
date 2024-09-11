#include "ftokenize.h"

FTokenizer::FTokenizer(char* fname){
    _f.open(fname);
    if  (!_f.is_open()){
        cout << "FAILED" << endl << endl;
        exit(2);
    }
    _more = true;
    _pos = 0;
    _blockPos = 0;
    get_new_block();
    
}

Token FTokenizer::next_token(){
    Token t;
    if (!_stk.more()){
        if (!get_new_block()){return t;}
    }
    _stk >> t;
    return t;
}

//returns the current value of _more
bool FTokenizer::more(){
    return (!_f.eof() || !_stk.done());
}   
     
//returns the value of _pos    
int FTokenizer::pos(){
    return _f.gcount();
}          

//returns the value of _blockPos
int FTokenizer::block_pos(){
    return _blockPos;
}     

bool FTokenizer::get_new_block(){
    if(!more()){
        return false;
    }
    char tempBuffer[MAX_BUFFER + 1];
    _f.read(tempBuffer, MAX_BUFFER);
    if (_f.gcount() == 0){
        _more = false;
        return false;
    }
    tempBuffer[_f.gcount()] = '\0';
    _stk.set_string(tempBuffer);
    //cout<< "block [" <<_f.gcount()<< "]" <<endl;
    //cout << tempBuffer <<endl;
    return true;
}