#ifndef PARSER_H
#define PARSER_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include "../bplustree/map.h"
#include "../queue/MyQueue.h"
#include "../bplustree/multimap.h"
#include "../tokenizer/state_machine_functions.h"
#include "../tokenizer/stokenize.h"
#include "../table/table.h"
#include "../table/typedefs.h"

using namespace std;

class Parser{
    public: 
        Parser();
        Parser(char* strArg);
        mmap_ss parse_tree();
        void set_string(char* c);
        Queue<string> createInputQueue();
        void printParseTree();
        bool getSuccessFlag();
        string errorThrown = "";
    private: 
        map_sl keywordsMap;
        int _adjacencyMatrix[MAX_ROWS][MAX_COLUMNS];
        bool successFlag; //turns on when a success state is hit
        char* str;
        void build_keywords_list();
        void make_state_machine();
        enum keys{
            BEGINNING,
            SELECT,
            STAR,
            FROM,
            WHERE,
            OPERATOR,
            AND_OR_OR,
            INSERT,
            INTO,
            VALUES,
            MAKE,
            TABLE,
            FIELDS,
            SYMBOL,
            SPACE,
            COMMA
        };
};

#endif