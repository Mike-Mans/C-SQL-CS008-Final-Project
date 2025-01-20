#include <iostream>
#include <iomanip>
#include "table.h"

Table::Table(){
    numberOfRecords = 0;

}

Table::Table(string tableName){
    numberOfRecords = 0;
    serialNumber++;
    fileName = tableName + "-" + to_string(serialNumber);
    //read the fields from the text File
    ifstream inFile(tableName + ".txt");
    string tempFieldName;
    while(getline(inFile, tempFieldName)){
        fieldVector.push_back(tempFieldName);
    }
    inFile.close();
    // Table(tableName + "-" + to_string(serialNumber), fieldVecTemp);

    /**********************FROM CONSTRUCTOR 3*******************/
    //write the elements to the textFile
    for(int i = 0; i < fieldVector.size(); i++){
        fieldMap.insert(fieldVector.at(i), i);
        indices.push_back(mmap_sl());
    }
    /***********************************************************/

    //open the binary files for reading and writing
    fstream otherFile, thisFile;
    open_fileRW(otherFile, tableName.c_str()); //original file
    open_fileW(thisFile, fileName.c_str()); //current file (empty at first)
    thisFile.close();

    FileRecord thisFileRec;

    while(thisFileRec.read(otherFile, numberOfRecords) > 0){
        this->insert_into(thisFileRec.get());
    }
    otherFile.close();
    remove(fileName.c_str());
    fileName = tableName;
    serialNumber--;
}

Table::Table(string tableName, vectorstr fields, bool pushBackMMaps){
    numberOfRecords = 0;
    //write the elements to the textFile
    ofstream textFile(tableName + ".txt");
    for(int i = 0; i < fields.size(); i++){
        textFile << fields.at(i) << endl;
    }

    //open for write to the binary file, add to the fieldMap and fieldVector, and create instances of mmaps
    fileName = tableName;
    fstream thisFile;
    open_fileW(thisFile, fileName.c_str());
    for(int i = 0; i < fields.size(); i++){
        fieldMap.insert(fields.at(i), i);
        fieldVector.push_back(fields.at(i));
        if(pushBackMMaps)
            indices.push_back(mmap_sl());
    }
    // cout << "Main MAP: " << endl << fieldMap << endl;
    thisFile.close();
}   

void Table::insert_into(vectorstr row){
    bool debug = false;
    if(debug)
        cout << "BREAKPOINT 0" << endl;


    // open a filerecord object and a fstream object, and put the row into fileRecord's 2D array for writing
    FileRecord thisFileRec(row); fstream thisFile;
    if(debug)
        cout << "BREAKPOINT 1" << endl;


    //open the file for read/write, and write to the file
    open_fileRW(thisFile, fileName.c_str());
    if(debug)
        cout << "BREAKPOINT 2" << endl;


    //holds the recordNumber
    long recordNumber = thisFileRec.write(thisFile);
    if(debug)
        cout << "BREAKPOINT 3" << endl;


    //insert the row into the multimap
    for(int i = 0; i < indices.size(); i++){
        indices[i][row.at(i)] += recordNumber;
    }
    if(debug)
        cout << "BREAKPOINT 4" << endl;
    numberOfRecords++;
    thisFile.close();
}

//makes a copy of the table
Table Table::select_all(){
    //create a new instance of table, and set the fileName appropriately
    serialNumber++;
    Table otherTable(this->fileName + "-" + to_string(serialNumber), this->fieldVector, false);
    
    //open/create the file for writing
    fstream otherFile, thisFile;
    open_fileRW(otherFile, otherTable.fileName.c_str());
    open_fileRW(thisFile, this->fileName.c_str());

    //loop and deep copy over all member variables MMaps
    for(int i = 0; i < this->fieldVector.size(); i++){
        //copy the mmaps and insert them into othertable's vector of mmaps
        mmap_sl tempMMap = this->indices.at(i).copy();
        otherTable.indices.push_back(tempMMap);
    }

    //copy the elements from the binary files
    otherTable.numberOfRecords = this->numberOfRecords;
    for(int i = 0; i < otherTable.numberOfRecords; i++){
        FileRecord thisFileRec;
        thisFileRec.read(thisFile, i);
        previouslyWrittenRecords += thisFileRec.write(otherFile);
    }

    //close the files
    thisFile.close();
    otherFile.close();
    otherTable.previouslyWrittenRecords = previouslyWrittenRecords;
    return otherTable;
}

Table Table::select(vectorstr fields, string fieldName, string oper, string description){
    //create object instances and open the files
    serialNumber++;
    //makes a deep copy of fieldVector and fieldMap
    Table otherTable(this->fileName + "-" + to_string(serialNumber), fields);
    FileRecord thisFileRec;
    //open the files
    fstream thisFile, otherFile;
    open_fileRW(thisFile, this->fileName.c_str());
    open_fileRW(otherFile, otherTable.fileName.c_str());

    //find the index of the fieldname in the map
    long index = fieldMap[fieldName];

    //go to that index/indices in the vector of multimaps, and then grab the vector of recordNumbers
    //that match the condition
    //calls select_recnos_conditional()
    previouslyWrittenRecords = select_recnos_relational(fieldName, oper, description);

    // 1)loop through previouslyWrittenRecords
    //      2) for each recordNumber, read it from thisFile
    //      3) write it to otherFile
    //      4) insert it into all the multimaps appropriately
    for(int i = 0; i < previouslyWrittenRecords.size(); i++){
        //read it from the file
        if(thisFileRec.read(thisFile, previouslyWrittenRecords.at(i)) == 0)
            assert("DID NOT READ FILE INFORMATION, MEANING RECORD DOES NOT EXIST ---- select, table");
        
        //Rearrange the vector string (since it is grabbed from the filerecord in the previous arrangement)
        vectorstr tempVec = thisFileRec.get();
        vectorstr newVec;
        for(int j = 0; j < fields.size(); j++){
            long index = this->fieldMap[fields.at(j)];
            newVec.push_back(tempVec.at(index));
        }

        //write the most recently read in entry to otherFile, and insert it into the multimaps
        //(all this is taken care of in insert_into if we convert the 2D array from FileRecord into a vectorstr)
        otherTable.insert_into(newVec);
    }

    //close the files
    thisFile.close();
    otherFile.close();
    otherTable.previouslyWrittenRecords = previouslyWrittenRecords;
    return otherTable;
}

Table Table::select(vectorstr fields, vectorstr conditions){
    bool debug = false;
    if(fields.at(0) == "*")
        fields = fieldVector;

    //if the user enters a field name that does not exist, it should throw an exception before we begin shunting
    for(int i = 0; i < fields.size(); i++){
        if(!fieldMap.contains(fields.at(i)))
            throw runtime_error("FIELD DOES NOT EXIST IN FIELDMAP");
    }

    //SHUNTING YARD ALGORITHM
    Stack<Token*> operStack;
    Queue<Token*> outputQueue;
    for(int i = 0; i < conditions.size(); i++){
        string currentStr = conditions.at(i);
        if(currentStr == "=" || currentStr == "==" || currentStr == ">=" || currentStr == "<=" || currentStr == ">" || currentStr == "<"){ //ITS A RELATIONAL OPERATOR
            if(operStack.empty())
                operStack.push(new Relational(currentStr));
            else{
                Token* fromTheVector = new Relational(currentStr);
                Token* fromTheStack = operStack.top();
                if(fromTheStack->get() == "(" || static_cast<Operator*>(fromTheStack)->getPrec() < static_cast<Operator*>(fromTheVector)->getPrec()){ //whatever is in the stack has a lower precedence
                    operStack.push(fromTheVector); 
                }
                else{ //whatever is in the stack has a higher precedence
                    while(!operStack.empty() && fromTheStack->get() != "(" && static_cast<Operator*>(fromTheStack)->getPrec() >= static_cast<Operator*>(fromTheVector)->getPrec()){
                        if(debug){
                            cout << fromTheStack->get() << endl;
                            cout << fromTheVector->get() << endl;
                        }
                        outputQueue.push(operStack.pop());
                        if(operStack.empty())
                            fromTheStack = nullptr;
                        else 
                            fromTheStack = operStack.top();
                    }
                    operStack.push(fromTheVector); 
                }
            }    
        }
        else if(currentStr == "and" || currentStr == "or"){ //ITS A LOGICAL OPERATOR
            if(operStack.empty())
                operStack.push(new Logical(currentStr));
            else{
                Token* fromTheVector = new Logical(currentStr);
                Token* fromTheStack = operStack.top();
                if(fromTheStack->get() == "(" || static_cast<Operator*>(fromTheStack)->getPrec() < static_cast<Operator*>(fromTheVector)->getPrec()){ //whatever is in the stack has a lower precedence
                    operStack.push(fromTheVector); 
                }
                else{ //whatever is in the stack has a higher precedence
                    while(!operStack.empty() && fromTheStack->get() != "(" && static_cast<Operator*>(fromTheStack)->getPrec() >= static_cast<Operator*>(fromTheVector)->getPrec()){
                        if(debug){
                            cout << fromTheStack->get() << endl;
                            cout << fromTheVector->get() << endl;
                        }
                        outputQueue.push(operStack.pop());
                        if(operStack.empty())
                            fromTheStack = nullptr;
                        else 
                            fromTheStack = operStack.top();
                    }
                    operStack.push(fromTheVector); 
                }
            }    
        }

        else if(currentStr == "("){ //ITS A LEFT PARENTHESIS
            operStack.push(new LParen(currentStr));
        }

        else if(currentStr == ")"){ //ITS A RIGHT PARENTHESIS
            Token* fromTheStack = operStack.pop();
            try{
                while(fromTheStack->get() != "("){
                    outputQueue.push(fromTheStack);
                    fromTheStack = operStack.pop();
                }
            }
            catch(...){
                throw runtime_error("MISSING LEFT PARENTHESIS");
            }
        }
        else{ //ITS A TOKENSTR
            outputQueue.push(new TokenStr(currentStr));
        }
    }
    while(!operStack.empty()){
        if(operStack.top()->get() == "(")
            throw runtime_error("MISSING RIGHT PARENTHESIS");
        try{
            outputQueue.push(operStack.pop());
        }
        catch(...){
            throw runtime_error("INVALID CONDITION");
        }
    }
    // while(!outputQueue.empty()){
    //     cout << *outputQueue.pop() << endl;
    // }
    // assert(false && "TESTING BREAKING POINT");
    return select(fields, outputQueue);
}

Table Table::select(vectorstr fields, Queue<Token *> conditions){
    //create object instances and open the files
    serialNumber++;
    //makes a deep copy of fieldVector and fieldMap
    Table otherTable(this->fileName + "-" + to_string(serialNumber), fields);
    FileRecord thisFileRec;
    //open the files
    fstream thisFile, otherFile;
    open_fileRW(thisFile, this->fileName.c_str());
    open_fileRW(otherFile, otherTable.fileName.c_str());
   
    //REVERSE POLISH NOTATION ALGORITHM 
    //By the end of this, previouslyWrittenRecords will hold the recordNumbers of all elements to be written
    if(!previouslyWrittenRecords.empty()) //clear any entries from previous search queries
        previouslyWrittenRecords.clear();
    Stack<Token*> rpnStack;

    while(!conditions.empty()){
        Token* qPtr = conditions.pop();
        TokenType thisType = qPtr->type();

        //if it is a tokenString, just push it to the stack
        if(thisType == TOKEN_STR)
            rpnStack.push(qPtr);

        //if it is a relational (eg. <=), pop the stack twice, call select_recnos_conditional, and push the resultset onto the stack
        else if(thisType == RELATIONAL){
            TokenStr* descriptionPtr = static_cast<TokenStr*> (rpnStack.pop());
            TokenStr* fieldNamePtr = static_cast<TokenStr*> (rpnStack.pop());
            previouslyWrittenRecords = select_recnos_relational(fieldNamePtr->get(), qPtr->get(), descriptionPtr->get());
            delete descriptionPtr; delete fieldNamePtr; //free the memory associated with these pointers
            rpnStack.push(new ResultSet("tempSet", previouslyWrittenRecords));
        }

        //if it is a logical operator, pop the stack twice, call select_recnos_relational, and push the resultset onto the stack
        else if(thisType == LOGICAL){
            ResultSet* rsetPtr1 = static_cast<ResultSet*> (rpnStack.pop());
            ResultSet* rsetPtr2 = static_cast<ResultSet*> (rpnStack.pop());
            previouslyWrittenRecords = select_recnos_logical(rsetPtr1->get_recnos(), qPtr->get(), rsetPtr2->get_recnos());
            delete rsetPtr1; delete rsetPtr2; //free the memory associated with these pointers
            rpnStack.push(new ResultSet("tempSet", previouslyWrittenRecords));
        }

        else{
            cout << qPtr->type();
            assert("REVERSE POLISH NOTATION ALGORITHM WITH TOKENTYPE FAILED");
        }
    }

    //by the end of the loop, the stack must just have 1 element (the final resultset token), 
    //so get this list of records and put them in previouslyWrittenRecords
    if(!rpnStack.empty()){
        previouslyWrittenRecords = (static_cast<ResultSet*>(rpnStack.pop()))->get_recnos();
        if(!rpnStack.empty()) //should be empty (otherwise there are too many spare left parenthesis)
            throw runtime_error("INVALID CONDITION");
    }
    else{ //the stack was empty becuase the queue was empty (meaning the user never passed in conditions), so the user wants all the records
        previouslyWrittenRecords = {};
        for(int i = 0; i < this->numberOfRecords; i++){
            previouslyWrittenRecords.push_back(i);
        }
    }
    // 1)loop through previouslyWrittenRecords
    //      2) for each recordNumber, read it from thisFile
    //      3) write it to otherFile
    //      4) insert it into all the multimaps appropriately
    for(int i = 0; i < previouslyWrittenRecords.size(); i++){
        //read it from the file
        if(thisFileRec.read(thisFile, previouslyWrittenRecords.at(i)) == 0)
            throw runtime_error("DID NOT READ FILE INFORMATION, MEANING RECORD DOES NOT EXIST ---- select, table");
        
        //Rearrange the vector string (since it is grabbed from the filerecord in the previous arrangement)
        vectorstr tempVec = thisFileRec.get();
        vectorstr newVec;
        for(int j = 0; j < fields.size(); j++){
            long index = this->fieldMap[fields.at(j)];
            newVec.push_back(tempVec.at(index));
        }

        //write the most recently read in entry to otherFile, and insert it into the multimaps
        //(all this is taken care of in insert_into if we convert the 2D array from FileRecord into a vectorstr)
        otherTable.insert_into(newVec);
    }

    //close the files
    thisFile.close();
    otherFile.close();
    otherTable.previouslyWrittenRecords = previouslyWrittenRecords;
    return otherTable;
}

vectorlong Table::select_recnos_relational(string fieldName, string oper, string description){
    vectorlong list;

    //select all records that are currently in the database
    if(oper == ""){
        for(long i = 0; i < numberOfRecords; i++){
            list.push_back(i);
        }
    }
    else if(oper == "=" || oper == "=="){
        list += indices.at(fieldMap[fieldName])[description];
    }
    else if(oper == ">="){
        mmap_sl::Iterator thisIt = indices.at(fieldMap[fieldName]).lower_bound(description);
        mmap_sl::Iterator endIt = indices.at(fieldMap[fieldName]).end();
        for( ; thisIt != endIt; thisIt++){
            MPair<string, long> tempPair = *thisIt;
            list += tempPair.value_list;
        }
    }
    else if(oper == "<="){
        mmap_sl::Iterator thisIt = indices.at(fieldMap[fieldName]).begin();
        mmap_sl::Iterator endIt = indices.at(fieldMap[fieldName]).upper_bound(description);
        for( ; thisIt != endIt; thisIt++){
            MPair<string, long> tempPair = *thisIt;
            list += tempPair.value_list;
        }
    }
    else if(oper == ">"){
        mmap_sl::Iterator thisIt = indices.at(fieldMap[fieldName]).upper_bound(description);
        mmap_sl::Iterator endIt = indices.at(fieldMap[fieldName]).end();
        for( ; thisIt != endIt; thisIt++){
            MPair<string, long> tempPair = *thisIt;
            list += tempPair.value_list;
        }
    }
    else if(oper == "<"){
        mmap_sl::Iterator thisIt = indices.at(fieldMap[fieldName]).begin();
        mmap_sl::Iterator endIt = indices.at(fieldMap[fieldName]).lower_bound(description);
        for( ; thisIt != endIt; thisIt++){
            MPair<string, long> tempPair = *thisIt;
            list += tempPair.value_list;
        }
    }
    else{
        cout << "OPER IS " << oper << endl;
        assert("NOT A VALID OPERATOR ----- select(vectorstr fields, string fieldName, string oper, string description)");
    }
    return list;
}

vectorlong Table::select_recnos_logical(vectorlong list1, string oper, vectorlong list2){
    vectorlong newList = {};
    //intersection of two sets
    if(oper == "and"){
        for(int i = 0; i < list1.size(); i++){
            bool found = false;
            for(int j = 0; j < list2.size(); j++){
                if(list1.at(i) == list2.at(j)){
                    found = true;
                    break;
                }
            }
            if(found)
                newList.push_back(list1.at(i));
        }
    }
    //union of two sets
    else if(oper == "or"){
        for(int i = 0; i < list1.size(); i++){
            bool found = false;
            for(int j = 0; j < list2.size(); j++){
                if(list1.at(i) == list2.at(j)){
                    found = true;
                    break;
                }
            }
            if(!found)
                newList.push_back(list1.at(i));
        }
        for(int k = 0; k < list2.size(); k++){
            newList.push_back(list2.at(k));
        }
    }
    else
        assert("OPER MUST BE EITHER \"and\" or \"or\" ---- TABLE, select_recnos_relational");
    
    return newList;
}

vectorlong Table::select_recnos(){
    return previouslyWrittenRecords;
}

void Table::resetNumberOfRecords(){
    this->numberOfRecords = 0;
}