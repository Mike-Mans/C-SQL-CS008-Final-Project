#include "token.h"

Token::Token(){
    _token = "";
    _type = 0;
}

Token::Token(string str, int type){
    _token = str;
    _type = type;
}

ostream& operator <<(ostream& outs, const Token& t){
    outs << "|" << t.token_str() << "|";
    return outs;
}

int Token::type() const{
    return _type;
}

string Token::type_string() const{
    if(_type == 1 || _type == 3)
        return "NUMBER";
    else if(_type == 4)
        return "ALPHA";
    else if(_type == 5)
        return "SPACE";
    else if(_type == 6)
        return "PUNC";
    else if(_type == 7)
        return "PUNC";
    else if(_type == -1)
        return "TOKEN_UNKNOWN";
    else if(_type == -2)
        return "TOKEN_END";
    return "Not proper enumeration";
}

string Token::token_str() const{
    return _token;
}
