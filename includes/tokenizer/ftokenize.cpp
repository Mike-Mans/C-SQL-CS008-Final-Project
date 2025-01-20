#include "ftokenize.h"

FTokenizer::FTokenizer(string fname){
    //initialize the input file stream
    _f = ifstream(fname);
    _stk = STokenizer();
    assert(_f.is_open() && "FAILED TO OPEN FILE");
    get_new_block();
    _stk.print_buffer();
    _pos = 0;
    _blockPos = 0; 
    _more = true;
}

Token FTokenizer::next_token(){
    if(_stk.done() && !get_new_block()){
        _more = false;
        return Token();
    }
    Token t;
    _stk >> t;
    _pos += t.token_str().length();
    _blockPos += t.token_str().length();
    return t;
}

bool FTokenizer::more(){
    return _more;
}

int FTokenizer::pos(){
    return _pos;
}

int FTokenizer::block_pos(){
    return _blockPos;
} 

FTokenizer& operator >> (FTokenizer& f, Token& t){
    t = f.next_token();
    return f;
}

bool FTokenizer::get_new_block(){
    //reset _blockPos to beginning
    _blockPos = 0;

    //read in next MAX_BLOCK characters
    char arr[MAX_BUFFER];
    _f.read(arr, MAX_BLOCK);

    //if the file read nothing, set more to false and return false
    //else, more stays true and return true
    if(_f.gcount() == 0){
        return false;
    }
    //if the file read something successfully
    //place null character at the end
    arr[_f.gcount()] = '\0';

    //set stk's buffer to read in array, and increment file position by 1
    _stk.set_string(arr);
    _pos++;
    return true;
}