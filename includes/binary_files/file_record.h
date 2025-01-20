#ifndef FILE_FileRecord_H
#define FILE_FileRecord_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <cstring>
#include <vector>
#include <fstream>
#include "utilities.h"

using namespace std;

struct FileRecord{
    //when you construct a FileRecord, it's either empty or it
    //  contains a word
    
    FileRecord(){ }

    FileRecord(vector<char*> v){
        for(int i = 0; i < v.size(); i++){
            strcpy(_record[i], v.at(i));
        }
        for(int i = v.size(); i < MAX + 1; i++){
            _record[i][0] = '\0';
        }
    }

    FileRecord(vector<string> v){
        for(int i = 0; i < v.size(); i++){
            strcpy(_record[i], v.at(i).c_str());
        }
        for(int i = v.size(); i < MAX + 1; i++){
            _record[i][0] = '\0';
        }
    }

    vector<string> get(){
        vector<string> v;
        for(int i = 0; i < MAX + 1; i++){
            if(_record[i][0] == '\0')
                break;
            v.push_back(_record[i]);
        }
        return v;
    }

    long write(fstream& outs);              //returns the FileRecord number
    long read(fstream& ins, long recno);    //returns the number of bytes ---- read = MAX, or zero if --- read passed the end of file

    friend ostream& operator<<(ostream& outs, const FileRecord& r){
        for(int i = 0; i < r.MAX + 1; i++){
            if(r._record[i][0] == '\0')
                break;
            outs << setw(25) << r._record[i];
        }
        return outs;
    }
    static const int MAX = 100;
    char _record[MAX+1][MAX+1];
};

#endif