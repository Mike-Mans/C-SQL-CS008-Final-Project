#ifndef TABLE_H
#define TABLE_H

#include "typedefs.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <vector>
#include "../bplustree/map.h"
#include "../bplustree/multimap.h"
#include "../token/token.h"
#include "../binary_files/file_record.h"
#include "../binary_files/utilities.h"
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"

using namespace std;

static long serialNumber;

class Table{
    public:
        Table();

        Table(string tableName);

        Table(string tableName, vectorstr fields, bool pushBackMMaps = true);

        void insert_into(vectorstr row);

        //makes a copy of the table
        Table select_all();

        Table select(vectorstr fields, string fieldName, string oper, string description);

        Table select(vectorstr fields, vectorstr conditions);

        Table select(vectorstr fields, Queue<Token *> conditions);

        vectorlong select_recnos_relational(string fieldName, string oper, string description);

        vectorlong select_recnos_logical(vectorlong list1, string oper, vectorlong list2);

        vectorlong select_recnos();

        void resetNumberOfRecords();

        friend ostream& operator<<(ostream& outs, const Table& t){
            if(t.numberOfRecords == 0)
                return outs;
            //Print the general table info
            outs << "TABLE NAME: " << t.fileName << endl;
            outs << "NUMBER OF RECORDS: " << t.numberOfRecords << endl;

            //Print the table headers
            outs << "#: ";
            for(int i = 0; i < t.fieldVector.size(); i++){
                outs << setw(25) << t.fieldVector.at(i);
            }
            outs << endl;
            
            //Print the elements in the binary file
            FileRecord r;
            fstream f;
            //open the file for reading and writing.
            open_fileRW(f, t.fileName.c_str());
            int i = 0;
            long bytes = r.read(f, i); //empty envelop to be filled by the FileRecord object
            while (bytes > 0){
                outs<< i << ": " << r << endl;
                i++;
                bytes = r.read(f, i);
            }
            f.close();
            return outs;
        }

    private:
        string fileName;
        long numberOfRecords;

        vector<mmap_sl> indices;
        vectorstr fieldVector;
        vectorlong previouslyWrittenRecords;
        map_sl fieldMap;
};  

#endif