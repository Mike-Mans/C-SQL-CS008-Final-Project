#include "stokenize.h"

int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

STokenizer::STokenizer(){
    set_string("");
    make_table(_table);
    _pos = 0;
}

STokenizer::STokenizer(char str[]){
    set_string(str); //set _buffer to given character array str
    make_table(_table);
    _pos = 0;
}

void STokenizer::print_buffer(){
    for(int i = 0; i < MAX_BUFFER; i++){
        cout << _buffer[i];
    }
}

bool STokenizer::done(){ 
    return _pos > strlen(_buffer); //if position is past the last position (where null character is)
}

bool STokenizer::more(){
    return !done();
}

//extract one token (very similar to the way cin >> works)
STokenizer& operator >> (STokenizer& s, Token& t){
    string token = "";
    int start_state = 0;
    s.get_token(start_state, token);
    t = Token(token, start_state);
    return s;
}

//set a new string as the input string
void STokenizer::set_string(char str[]){
    strcpy(_buffer, str); //use strcopy from cstrng class
    _pos = 0;
}

void STokenizer::make_table(int _table[][MAX_COLUMNS]){
    init_table(_table);

    //doubles:
    mark_fail(_table, 0);            //Mark states 0 and 2 as fail states
    mark_success(_table, 1);         //Mark states 1 and 3 as success states
    mark_fail(_table, 2);
    mark_success(_table, 3);
    mark_cells(0, _table, DIGITS, 1);    //state [0] --- DIGITS ---> [1]
    mark_cells(0, _table, '.', '.', 2);  //state [0] --- '.' ------> [2] 
    mark_cells(1, _table, DIGITS, 1);    //state [1] --- DIGITS ---> [1]
    mark_cells(1, _table, '.', '.', 2);  //state [1] --- '.' ------> [2] 
    mark_cells(2, _table, DIGITS, 3);    //state [2] --- DIGITS ---> [3]
    mark_cells(3, _table, DIGITS, 3);    //state [3] --- DIGITS ---> [3]

    mark_success(_table, 4);
    mark_cells(0, _table, ALFA, 4);
    mark_cells(4, _table, ALFA, 4);

    mark_success(_table, 5);
    mark_cells(0, _table, SPACES, 5);

    mark_success(_table, 6);
    mark_cells(0, _table, PUNC, 6);
    mark_cells(0, _table, '.', '.', 7);

    mark_success(_table, 7);
    mark_cells(7, _table,  DIGITS , 3);

    mark_fail(_table, 8);
    mark_cell(0, _table, '\"', 8);
    mark_cells(8, _table, ALFA, 8);
    mark_cells(8, _table, SPACES, 8);
    mark_cells(8, _table, DIGITS, 8);
    mark_cell(8, _table, '.', 8);

    mark_success(_table, 9);
    mark_cell(8, _table, '\"', 9);

    mark_success(_table, 10);
    mark_cells(0, _table, OPERATORS, 10);
    mark_cells(10, _table, OPERATORS, 10);
    mark_cell(10, _table, '(', 11);
    mark_cell(10, _table, ')', 11);
}

bool STokenizer::get_token(int& start_state, string& token){
    // assert(strlen(_buffer) != 0 && "STRING IS EMPTY");
    // show_string(_buffer, _pos);
    int startingPos = _pos;
    string tempToken = ""; // initialize the initial token to an empty tring
    int lastSuccessPos = -1; // initialize the last success position to -1
    int lastSuccessState = -1;
    char currChar;
    do{
        // cout << "POS: " << _pos << endl;
        // cout << "STATE: " << start_state << endl;
        // cout << "currChar: " << currChar << endl;
        // cout << "last_success: " << lastSuccessPos << endl;
        // cout << "tempToken: " << tempToken << endl;
        //show_string(_buffer, _pos);
        //cout << endl;

        // if(start_state == -1){ //fail
        //     _pos = lastSuccessPos;
        //     break;
        // }
        if(is_success(_table, start_state)){ //success
            token = tempToken;
            lastSuccessPos = _pos;
            lastSuccessState = start_state;
        }
        
        //otherwise, it's an intermediate state
        currChar = _buffer[_pos];
        tempToken += currChar;
        start_state = _table[start_state][currChar];
        _pos++;
    }while(_pos <= strlen(_buffer) && start_state != -1);

    start_state = lastSuccessState;

    // if(lastSuccessPos != -1 && _pos <= strlen(_buffer)){ //found a success state and didnt go out of bounds
    //     _pos = lastSuccessPos;
    //     return true;
    // }
    // else if(lastSuccessPos != -1){ //found a success but loop went out of bounds
    //     _pos = lastSuccessPos;
    // }
    // else //didnt find a success
    //     _pos = startingPos;

    if(lastSuccessPos != -1){
        _pos = lastSuccessPos;
        return true;
    }
    else{
        _pos = startingPos + 1;
    }

    //show_string(_buffer, _pos);
    return false;
}