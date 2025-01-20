#ifndef SQL_H
#define SQL_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>

#include "../parser/parser.h"
#include "../table/table.h"
#include "../table/typedefs.h"
using namespace std;

class SQL{
public:
    SQL();
    Table command(string thisCommand);
    vectorlong select_recnos();
    bool getSuccessFlag();
    void printOpenFiles();
    void batch();
private:
    bool sqlSuccessFlag;
    vectorlong thisRecnos;
    Map<string, Table> sqlMap;
    vector<string> sqlStringVector;
};

SQL::SQL(){ 
    ifstream inFile("sql_tables.txt");
    string tempTableName;
    while(getline(inFile, tempTableName)){
        sqlStringVector.push_back(tempTableName);
        sqlMap.insert(tempTableName, Table(tempTableName));
    }
    inFile.close();
    printOpenFiles();
}

void SQL::batch(){
    // 1. valid command:
        cout << "1. select lname, fname, major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson" << endl;
        cout << command("select lname, fname, major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson") << endl;
    // 2. Expected comma:
        cout << "2. select lname fname, major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson" << endl; 
        cout << command("select lname fname, major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson") << endl;
    // 3. Expected: field name
        cout << "3. select lname, , major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson" << endl; 
        cout << command("select lname, , major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson") << endl;
    // 4. Expected from:
        cout << "4. select lname, fname, major  student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson" << endl; 
        cout << command("select lname, fname, major  student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson") << endl;
    // 5. Expected table name:
        cout << "5. select lname, fname, major from  where ((lname=Yang or major=CS) and age<23 )or lname=Jackson" << endl;
        cout << command("select lname, fname, major from  where ((lname=Yang or major=CS) and age<23 )or lname=Jackson") << endl;
    // 6. Expected condition:
        cout << "6. select lname, fname, major from student where " << endl;
        cout << command("select lname, fname, major from student where ") << endl;
    // 7. Missing left paren:
        cout << "7. select lname, fname, major from student where (lname=Yang or major=CS) and age<23 )or lname=Jackson" << endl;
        cout << command("select lname, fname, major from student where (lname=Yang or major=CS) and age<23 )or lname=Jackson") << endl;
    // 8. Missing right paren:
        cout << "8. select lname, fname, major from student where ((lname=Yang or major=CS and age<23 )or lname=Jackson" << endl; 
        cout << command("select lname, fname, major from student where ((lname=Yang or major=CS and age<23 )or lname=Jackson") << endl;
    // 9. :
        cout << "9. select lname, fname, major from student where ((lname= or major=CS) and age<23 )or lname=Jackson" << endl;
        cout << command("select lname, fname, major from student where ((lname= or major=CS) and age<23 )or lname=Jackson") << endl;
    // 10. :
        cout << "10. select lname, fname, major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson" << endl; 
        cout << command("select lname, fname, major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson") << endl;
    // 11. :
        cout << "11. select lname, fname, major from student where ((lname=Yang  major=CS) and age<23 )or lname=Jackson" << endl;
        cout << command("select lname, fname, major from student where ((lname=Yang  major=CS) and age<23 )or lname=Jackson") << endl;
    // 12. :
        cout << "12. select lname, fname, major from student where ((lname=Yang or ) and age<23 )or lname=Jackson" << endl;
        cout << command("select lname, fname, major from student where ((lname=Yang or ) and age<23 )or lname=Jackson") << endl;
    // 13. :
        cout << "13. select lname, fname, major from student where ((lname=Yang or major=CS) and age<23 )or " << endl;
        cout << command("select lname, fname, major from student where ((lname=Yang or major=CS) and age<23 )or ") << endl;
    // 14. :
        cout << "14. select lname, fname, major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson" << endl;
        cout << command("select lname, fname, major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson") << endl;
}

void SQL::printOpenFiles(){
    cout << "CURRENTLY OPEN TABLES" << endl << "-----------------" << endl;
    for(int i = 0; i < sqlStringVector.size(); i++){
        cout << sqlStringVector.at(i) << endl;
    }
    cout << endl;
}

bool SQL::getSuccessFlag(){
    return sqlSuccessFlag;
}

Table SQL::command(string thisCommand){
    Table t;
    try{
        char temp[200];
        strcpy(temp, thisCommand.c_str());
        Parser p(temp);
        mmap_ss parseTree = p.parse_tree();
        sqlSuccessFlag = p.getSuccessFlag();
        if(!sqlSuccessFlag){
            throw runtime_error("GENERAL INVALID COMMAND");
        }
        if(parseTree["command"].at(0) == "make"){
            if(sqlMap.contains(parseTree["table_name"].at(0)) || !parseTree.contains("fields")){
                // throw runtime_error("TABLE ALREADY EXISTS OR NO FIELDS GIVEN");
                cout << "TABLE ALREADY EXISTS OR NO FIELDS GIVEN" << endl;
                return sqlMap[parseTree["table_name"].at(0)];
            }
            // use constructor that creates a fresh table
            Table t_temp(parseTree["table_name"].at(0), parseTree["fields"]);
            t = t_temp;

            // push it back into the map and vector and write it to the file!
            sqlMap.insert(parseTree["table_name"].at(0), t_temp);
            sqlStringVector.push_back(parseTree["table_name"].at(0));
            ofstream textFile("sql_tables.txt");
            for(int i = 0; i < sqlStringVector.size(); i++){
                textFile << sqlStringVector.at(i) << endl;
            }
        }
        else if(parseTree["command"].at(0) == "insert"){
            if(!sqlMap.contains(parseTree["table_name"].at(0)))
                throw runtime_error("TABLE DOES NOT EXIST");
            //use constructor that opens a created file

            // t = Table(parseTree["table_name"].at(0));
            t = sqlMap[parseTree["table_name"].at(0)];
            t.insert_into(parseTree["values"]);
            sqlMap[parseTree["table_name"].at(0)] = t;
        }
        else if(parseTree["command"].at(0) == "select"){
            //use constructor that opens a created file
            if(!sqlMap.contains(parseTree["table_name"].at(0)))
                throw runtime_error("TABLE DOES NOT EXIST");

            // t = Table(parseTree["table_name"].at(0));
            t = sqlMap[parseTree["table_name"].at(0)];

            if(parseTree.contains("where")){
                // cout << "USER INPUTTED FIELD NAMES: " << parseTree["fields"] << endl;
                t = t.select(parseTree["fields"], parseTree["condition"]);
            }
            else{
                cout << "There is no condition" << endl;
                t = t.select(parseTree["fields"], vectorstr());
            }
            thisRecnos = t.select_recnos();
        }
        else{
            throw runtime_error("EXPECTED COMMAND OF (SELECT, INSERT, MAKE)");
        }
    }
    catch(exception& e){
        cout << "\033[31m" << e.what() << endl;
        cout << "INVALID COMMAND --- TRY AGAIN\033[0m" << endl;
        t.resetNumberOfRecords();
        thisRecnos = {};
    }
    return t;
}

vectorlong SQL::select_recnos(){
    return thisRecnos;
}

#endif