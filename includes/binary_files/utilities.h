#ifndef UTILITIES_H
#define UTILITIES_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <fstream>
#include "file_record.h"

using namespace std;

//utility functions
bool file_exists(const char filename[]);
void open_fileRW(fstream& f, const char filename[]);
void open_fileW(fstream& f, const char filename[]);
void confuse_me();
void simple_test();

#endif