#include "parser.h"
Parser::Parser(){
    str[0] = '\0';
    successFlag = 0;
    build_keywords_list();
    make_state_machine();
}

Parser::Parser(char* c){
    str = c;
    successFlag = 0;
    build_keywords_list();
    make_state_machine();
}

mmap_ss Parser::parse_tree(){
    Queue<string> thisInputQueue = this->createInputQueue(); //queue of strings/tokens entered by the user
    mmap_ss pTree;
    string temp = "";
    string nextExpectedElementName = "";
    long currentEnum_col = BEGINNING;
    int currentState_row = 0;

    while(!thisInputQueue.empty()){
        //are we in a success_state?
        if(currentState_row == -1){
            successFlag = false;
            break;
        }
        if(is_success(_adjacencyMatrix, currentState_row))
            successFlag = true;
        else
            successFlag = false;

        //pop the queue and assign the appropriate enumeration
        temp = thisInputQueue.pop();
        if(keywordsMap.contains(temp)){
            currentEnum_col = keywordsMap[temp];
        }
        else{
            if(temp == ","){
                currentEnum_col = COMMA;
            }
            else if(temp == " " || temp == "\0" || temp == "\t" || temp == "\n"){
                currentEnum_col = SPACE;
            }
            else{
                currentEnum_col = SYMBOL;
            }
        }

        switch (currentEnum_col)
        {
        case SPACE:
            break;
        case COMMA:
            break;
        case SYMBOL:
            if(temp.at(0) == '\"')
                temp = temp.substr(1, temp.size() - 2);
            pTree.insert(nextExpectedElementName, temp);
            break;
        case SELECT:
            pTree.insert("command", "select");
            nextExpectedElementName = "fields";
            break;
        case STAR:
            pTree.insert(nextExpectedElementName, "*");
            break;
        case FROM:
            nextExpectedElementName = "table_name";
            break;
        case WHERE:
            pTree.insert("where", "yes");
            nextExpectedElementName = "condition";
            break;
        case INSERT:
            pTree.insert("command", "insert");
            break;
        case INTO:
            nextExpectedElementName = "table_name";
            break;
        case VALUES:
            nextExpectedElementName = "values";
            break;
        case MAKE:
            pTree.insert("command", "make");
            break;
        case TABLE:
            nextExpectedElementName = "table_name";
            break;
        case FIELDS:
            nextExpectedElementName = "fields";
            break;
        default:
            throw runtime_error("INVALID ENUMERATION");
            break;
        }
        //get the next stateRow for the next iteration
        currentState_row = _adjacencyMatrix[currentState_row][currentEnum_col];
    }
    return pTree;
}

void Parser::set_string(char* c){
    str = c;
}

Queue<string> Parser::createInputQueue(){
    //tokenizes the string str, and returns a queue of unique tokens
    Queue<string> inputQ;
    STokenizer s = STokenizer(str);
    Token t;
    while(!s.done()){
        s >> t;          
        inputQ.push(t.token_str());
    }
    return inputQ;
}

void Parser::build_keywords_list(){
    keywordsMap["select"] = SELECT;
    keywordsMap["*"] = STAR;
    keywordsMap["from"] = FROM;
    keywordsMap["where"] = WHERE;
    keywordsMap["insert"] = INSERT;
    keywordsMap["into"] = INTO;
    keywordsMap["values"] = VALUES;
    keywordsMap["make"] = MAKE;
    keywordsMap["table"] = TABLE;
    keywordsMap["fields"] = FIELDS;
    /*
            BEGINNING, (missing)
            SELECT,
            STAR,
            FROM,
            WHERE,
            OPERATOR,  (missing)
            AND_OR_OR, (missing)
            INSERT,
            INTO,
            VALUES,
            MAKE,
            TABLE,
            FIELDS,
            SYMBOL, (missing)
            SPACE (missing)
    */
}

void Parser::make_state_machine(){
    init_table(_adjacencyMatrix);
    mark_fail(_adjacencyMatrix, 0);
    mark_fail(_adjacencyMatrix, 1);
    mark_fail(_adjacencyMatrix, 2);
    mark_fail(_adjacencyMatrix, 3);
    mark_success(_adjacencyMatrix, 4); //SUCCESS
    mark_success(_adjacencyMatrix, 5); //SUCCESS
    mark_fail(_adjacencyMatrix, 6);
    mark_fail(_adjacencyMatrix, 7);
    mark_success(_adjacencyMatrix, 8); //SUCCESS
    mark_fail(_adjacencyMatrix, 9);
    mark_fail(_adjacencyMatrix, 10);
    mark_fail(_adjacencyMatrix, 11);
    mark_fail(_adjacencyMatrix, 12);
    mark_success(_adjacencyMatrix, 13); //SUCCESS
    mark_fail(_adjacencyMatrix, 14);
    mark_fail(_adjacencyMatrix, 15);
    mark_fail(_adjacencyMatrix, 16);
    mark_fail(_adjacencyMatrix, 17);
    mark_success(_adjacencyMatrix, 18); //SUCCESS
    mark_fail(_adjacencyMatrix, 19);
    mark_fail(_adjacencyMatrix, 20);

    mark_cell(0, _adjacencyMatrix, SELECT, 1);
    mark_cell(0, _adjacencyMatrix, INSERT, 9);
    mark_cell(0, _adjacencyMatrix, MAKE, 14);

    mark_cell(1, _adjacencyMatrix, STAR, 2);
    mark_cell(1, _adjacencyMatrix, SYMBOL, 3);

    mark_cell(2, _adjacencyMatrix, FROM, 19);

    mark_cell(3, _adjacencyMatrix, COMMA, 1);
    mark_cell(3, _adjacencyMatrix, FROM, 19);

    mark_cell(4, _adjacencyMatrix, WHERE, 20);

    mark_cell(5, _adjacencyMatrix, SYMBOL, 5);

    // mark_cell(6, _adjacencyMatrix, OPERATOR, 7);
    // mark_cell(7, _adjacencyMatrix, SYMBOL, 8);
    // mark_cell(8, _adjacencyMatrix, AND_OR_OR, 5);

    mark_cell(9, _adjacencyMatrix, INTO, 10);

    mark_cell(10, _adjacencyMatrix, SYMBOL, 11);

    mark_cell(11, _adjacencyMatrix, VALUES, 12);

    mark_cell(12, _adjacencyMatrix, SYMBOL, 13);

    mark_cell(13, _adjacencyMatrix, SYMBOL, 13);

    mark_cell(14, _adjacencyMatrix, TABLE, 15);

    mark_cell(15, _adjacencyMatrix, SYMBOL, 16);

    mark_cell(16, _adjacencyMatrix, FIELDS, 17);

    mark_cell(17, _adjacencyMatrix, SYMBOL, 18);

    mark_cell(18, _adjacencyMatrix, SYMBOL, 18);

    mark_cell(19, _adjacencyMatrix, SYMBOL, 4);

    mark_cell(20, _adjacencyMatrix, SYMBOL, 5);

    mark_cell(0, _adjacencyMatrix, SPACE, 0);
    mark_cell(1, _adjacencyMatrix, SPACE, 1);
    mark_cell(2, _adjacencyMatrix, SPACE, 2);
    mark_cell(3, _adjacencyMatrix, SPACE, 3);
    mark_cell(4, _adjacencyMatrix, SPACE, 4);
    mark_cell(5, _adjacencyMatrix, SPACE, 5);
    mark_cell(6, _adjacencyMatrix, SPACE, 6);
    mark_cell(7, _adjacencyMatrix, SPACE, 7);
    mark_cell(8, _adjacencyMatrix, SPACE, 8);
    mark_cell(9, _adjacencyMatrix, SPACE, 9);
    mark_cell(10, _adjacencyMatrix, SPACE, 10);
    mark_cell(11, _adjacencyMatrix, SPACE, 11);
    mark_cell(12, _adjacencyMatrix, SPACE, 12);
    mark_cell(13, _adjacencyMatrix, SPACE, 13);
    mark_cell(14, _adjacencyMatrix, SPACE, 14);
    mark_cell(15, _adjacencyMatrix, SPACE, 15);
    mark_cell(16, _adjacencyMatrix, SPACE, 16);
    mark_cell(17, _adjacencyMatrix, SPACE, 17);
    mark_cell(18, _adjacencyMatrix, SPACE, 18);
    mark_cell(19, _adjacencyMatrix, SPACE, 19);
    mark_cell(20, _adjacencyMatrix, SPACE, 20);

    mark_cell(6, _adjacencyMatrix, SYMBOL, 6);
    mark_cell(8, _adjacencyMatrix, SYMBOL, 8);

    mark_cell(13, _adjacencyMatrix, COMMA, 12);
    mark_cell(18, _adjacencyMatrix, COMMA, 17);
}

void Parser::printParseTree(){
    parse_tree().print_lookup();
}

bool Parser::getSuccessFlag(){
    return successFlag;
}