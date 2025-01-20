#ifndef TOKEN_H
#define TOKEN_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include "../table/typedefs.h"

using namespace std;

enum TokenType{
    TOKEN,
    LPAREN,
    RPAREN, 
    TOKEN_STR,
    OPERATOR,
    RESULTSET,
    RELATIONAL,
    LOGICAL,
    // TOKEN_NUMBER,
    // TOKEN_ALPHA,
    // TOKEN_SPACE,
    // TOKEN_OPERATOR,
    // TOKEN_PUNC,
    // TOKEN_UNKNOWN,
    // TOKEN_END
};

enum Precedence{ 
    OR_PREC,
    AND_PREC, 
    CONDTIONAL_PREC
};

class Token{
    public: 
        Token() { 
            _type = TOKEN;
        }

        Token(string str, TokenType type = TOKEN) { 
            _token = str;
            _type = type;
        }

        TokenType type() const{
            return _type;
        }

        string get() const{
            return _token;
        }

        friend ostream& operator<<(ostream& outs, const Token& t){
            outs << t.get() << ": "<< t.type() << endl;
            return outs;
        }

    private:
        string _token;
        TokenType _type;
};

class TokenStr:public Token{
    public: 
        TokenStr(string str): Token(str, TOKEN_STR){}
};

class LParen:public Token{
    public: 
        LParen(string str): Token(str, LPAREN){}
};

class RParen:public Token{
    public: 
        RParen(string str): Token(str, RPAREN){}
};

class ResultSet:public Token{
    public: 
        ResultSet(string str, vectorlong thisRecnos = {}): Token(str, RESULTSET){
            vector_recnos = thisRecnos;
        }

        vectorlong get_recnos(){
            return vector_recnos;
        }

    private:
        vectorlong vector_recnos;
};

class Operator:public Token{
    public: 
        Operator(string str, TokenType type = OPERATOR): Token(str, type){
            if(str == "and")
                thisPrec = AND_PREC;
            else if(str  == "or")
                thisPrec = OR_PREC;
            else    
                thisPrec = CONDTIONAL_PREC;
        }
        Precedence getPrec(){
            return thisPrec;
        }
    private:
        Precedence thisPrec;
};

class Relational:public Operator{
    public: 
        Relational(string str): Operator(str, RELATIONAL){}
};

class Logical:public Operator{
    public: 
        Logical(string str): Operator(str, LOGICAL){}
};

#endif