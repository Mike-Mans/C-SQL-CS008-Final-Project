#ifndef BTREE_ARRAY_FUNCS_H
#define BTREE_ARRAY_FUNCS_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <vector>

using namespace std;

//PROTOTYPES
template <class T>
T maximal(const T& a, const T& b);                      //return the larger of the two items

template <class T>
void swap(T& a, T& b);  //swap the two items

template <class T>
int index_of_maximal(T data[ ], int n);                 //return index of the largest item in data

template <class T>
void ordered_insert(T data[ ], int& n, T entry);        //insert entry into the sorted array
                                                        //data with length n

template <class T>
int first_ge(const T data[ ], int n, const T& entry);   //return the first element in data that is
                                                        //not less than entry

template <class T>
void insert_item(T data[ ], int i, int& n, T entry);    //insert entry at index i in data

template <class T>
void attach_item(T data[ ], int& n, const T& entry);    //append entry to the right of data

template <class T>
void detach_item(T data[ ], int& n, T& entry);          //remove the last element in data and place
                                                        //it in entry

template <class T>
void delete_item(T data[ ], int i, int& n, T& entry);   //delete item at index i and place it in entry

template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2);   //append data2 to the right of data1

template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2);   //move n/2 elements from the right of data1
                                                        //and move to data2

template <class T>
void copy_array(T dest[], const T src[],
                int& dest_size, int src_size);              //copy src[] into dest[]

template <class T>
void print_array(const T data[], int n, int pos = -1);  //print array data

template <class T>
bool is_gt(const T data[], int n, const T& item);       //item > all data[i]

template <class T>
bool is_le(const T data[], int n, const T& item);       //item <= all data[i]

//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list); //print vector list

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme); //list.push_back addme

//IMPLEMENTATIONS
template <class T>
T maximal(const T& a, const T& b){ //return the larger of the two items
    if(a > b)
        return a;
    return b;
}

template <class T>
void swap(T& a, T& b){ //swap the two items
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
int index_of_maximal(T data[ ], int n){ //return index of the largest item in data
    assert(n > 0 && "N MUST BE LARGER THAN 0 ------ INDEX_OF_MAXIMAL , BTREE ARRAY FUNCTIONS");
    int maxIndex = 0;
    int i = 0;
    for(i = 0; i < n; i++){
        if(data[i] > data[maxIndex]){
            maxIndex = i;
        }
    }
    return i;
}

template <class T>
void ordered_insert(T data[ ], int& n, T entry){ //insert entry into the sorted array
    assert(n >= 0 && "N MUST BE LARGER THAN 0 ------ ORDERED_INSERT , BTREE ARRAY FUNCTIONS");
    int i = 0;
    if(n > 0)
        i = first_ge(data, n, entry);
    
    insert_item(data, i , n, entry);
}

template <class T>
int first_ge(const T data[ ], int n, const T& entry){ //return the first element in data that is not less than entry
    assert(n >= 0 && "N MUST BE LARGER THAN 0 ------ FIRST_GE , BTREE ARRAY FUNCTIONS");
    for(int i = 0; i < n; i++){
        if(data[i] >= entry)
            return i;
    }
    return n;
}

template <class T>
void insert_item(T data[ ], int i, int& n, T entry){ //insert entry at index i in data
    assert(n >= 0 && "N MUST BE LARGER THAN 0 ------ INSERT_ITEM , BTREE ARRAY FUNCTIONS");

    //i is too large -- does not exist in the current tree, add to very end
    if(i == n)
        data[n++] = entry;
    
    //the entry already exists in the tree -- override it and don't increment size
    else if(data[i] == entry){
        data[i] = entry;
        return;
    }

    //it exists in middle of the array or at end of array -- shift elements over and insert
    else{
        //shift it! shift it! in reverse!
        for(int j = n; j > i; j--){
            data[j] = data[j - 1];
        }

        //insert at i
        data[i] = entry;
        
        //increment the size
        n++;
    }
}

template <class T>
void attach_item(T data[ ], int& n, const T& entry){ //append entry to the right of data
    assert(n >= 0 && "N MUST BE LARGER THAN 0 ------ ATTACH_ITEM , BTREE ARRAY FUNCTIONS");
    data[n++] = entry;
}

template <class T>
void detach_item(T data[ ], int& n, T& entry){ //remove the last element in data and place it in entry
    assert(n > 0 && "N MUST BE LARGER THAN 0 ------ DETACH_ITEM , BTREE ARRAY FUNCTIONS");
    entry = data[--n];
}

template <class T>
void delete_item(T data[ ], int i, int& n, T& entry){ //delete item at index i and place it in entry
    assert(n > 0 && "N MUST BE LARGER THAN 0 ------ DELETE_ITEM , BTREE ARRAY FUNCTIONS");
    entry = data[i];  //put item into entry since it will soon be overriden by shifting

    //shift it! shift it! in forward!
    for( ; i < n - 1; i++){
        data[i] = data[i + 1];
    }
    //decrement the size
    n--;
}

template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2){ //append data2 to the right of data1
    //all elements in data2 are larger than data1, and there is enough capacity in data1 to merge with data2
    assert(n1 >= 0 && "N MUST BE LARGER THAN 0 ------ MERGE , BTREE ARRAY FUNCTIONS");
    assert(n2 >= 0 && "N MUST BE LARGER THAN 0 ------ MERGE , BTREE ARRAY FUNCTIONS");
    //assert(data1[n1 - 1] < data2[0] && "DATA1 ELEMENTS MUST BE LESS THAN DATA2 ELEMENTS ------ MERGE , BTREE ARRAY FUNCTIONS");
    for(int i = 0; i < n2; i++){
        data1[n1 + i] = data2[i];
    }

    //adjust the sizes
    n1 += n2;
    n2 = 0;
}

template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2){ //move n/2 elements from the right of data1 and move to data2
    assert(n1 >= 0 && "N MUST BE LARGER THAN 0 ------ SPLIT , BTREE ARRAY FUNCTIONS");
    assert(n2 == 0 && "N MUST BE EMPTY ------ SPLIT , BTREE ARRAY FUNCTIONS");

    // odd/even discrepancy when determining size of first array 
    int half_n = n1/2;
    if(n1 % 2 != 0)
        half_n++;

    //copy elements from data1 into data2
    for(int i = 0; i < (n1 - half_n); i++){
        data2[i] = data1[half_n + i];
    }

    //readjust the sizes
    n2 = n1 - half_n;
    n1 = half_n;
}

template <class T>
void copy_array(T dest[], const T src[], int& dest_size, int src_size){ //copy src[] into dest[]
    assert(src_size >= 0 && "N MUST BE LARGER THAN 0 ------ COPY_ARRAY , BTREE ARRAY FUNCTIONS");
    assert(dest_size == 0 && "N MUST BE EMPTY ------ COPY_ARRAY , BTREE ARRAY FUNCTIONS");

    while(dest_size < src_size){
        dest[dest_size] = src[dest_size];
        dest_size++;
    }
}

template <class T>
void print_array(const T data[], int n, int pos){ //print array data
    assert(n > 0 && "N MUST BE LARGER THAN 0 ------ PRINT_ARRAY , BTREE ARRAY FUNCTIONS");
    assert(pos < n && "N MUST BE LARGER THAN POS ------ PRINT_ARRAY , BTREE ARRAY FUNCTIONS");
    cout << data[pos];
}

template <class T>
bool is_gt(const T data[], int n, const T& item){ //item > all data[i]
    assert(n > 0 && "N MUST BE LARGER THAN 0 ------ IS_GT , BTREE ARRAY FUNCTIONS");
    for(int i = 0; i < n; i++){
        if(data[i] >= item)
            return false;
    }
    return true;
}

template <class T>
bool is_le(const T data[], int n, const T& item){ //item <= all data[i]
    assert(n > 0 && "N MUST BE LARGER THAN 0 ------ IS_GT , BTREE ARRAY FUNCTIONS");
    for(int i = 0; i < n; i++){
        if(data[i] < item)
            return false;
    }
    return true;
}

//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list){ //print vector list
    for(int i = 0; i < list.size(); i++){
        outs << list.at(i) << " ";
    }
    return outs;
}

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme){ //list.push_back addme
    list.push_back(addme);
    return list;
}

//adds every element from list2 to list1 (DOES NOT ACCOUNT FOR DUPLICATES/IS NOT UNION OPERATOR YET)
template <typename T>
vector<T>& operator +=(vector<T>& list, const vector<T>& list2){ //list.push_back addme
    for(int i = 0; i < list2.size(); i++){
        list.push_back(list2.at(i));
    }
    return list;
}
#endif