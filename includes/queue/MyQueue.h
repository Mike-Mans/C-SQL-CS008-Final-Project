#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include "../linked_list_functions/linkedlistfunctionsTemplated.h"

using namespace std;

template <typename T>
class Queue{
public:
    class Iterator{
    public:
        friend class Queue;                               //give access to list to access _ptr
        Iterator(){_ptr = nullptr;}                          //default ctor
        Iterator(node<T>* p){                             //Point Iterator to where p is pointing to
            _ptr = p;
        }                            
        T operator *(){
            assert(_ptr != nullptr && "PTR IS NULLPTR");
            return _ptr->_item;
        }//dereference operator

        bool is_null(){return _ptr == nullptr;}//true if _ptr is NULL

        friend bool operator !=(const Iterator& left, const Iterator& right)  //true if left != right
        {
            return left._ptr != right._ptr;
        }

        friend bool operator ==(const Iterator& left, const Iterator& right)  //true if left == right
        {
            return left._ptr == right._ptr;
        }

        Iterator& operator++(){                         //member operator:++it
                                                        // or ++it = new_value
            assert(_ptr != nullptr);
            _ptr = _ptr->_next;
            return *this;
        }

        friend Iterator operator++(Iterator& it, int unused){         //friend operator: it++
            assert(it._ptr != nullptr);
            Iterator temp = it;
            it._ptr = it._ptr->_next;
            return temp;
        }

    private:
        node<T>* _ptr;                          //pointer being encapsulated
    };

    //BIG THREE
    Queue(){
       _front = nullptr; 
       _rear = nullptr;
       _size = 0;
    }
    Queue(const Queue<T>& copyMe){
        _rear = _copy_list(_front, copyMe._front);
        _size = copyMe._size;
    }
    ~Queue(){
        _clear_list(_front);
        _front = nullptr; 
       _rear = nullptr;
        _size = 0;
    }

    Queue& operator=(const Queue<T>& RHS){
        if(this != &RHS){
            _rear = _copy_list(_front, RHS._front);
            _size = RHS._size;
        }
        return *this;
    }

    bool empty(){
        return _front == nullptr;
    }
    T front(){
        assert(_front != nullptr && "FRONT IS NULLPOINTER");
        return _front->_item;
    }
    T back(){
        assert(_rear !=  nullptr && "REAR IS NULLPOINTER");
        return _rear->_item;
    }

    void push(T item){
        _size++;
        _rear = _insert_after(_front, _rear, item);
    }
    T pop(){
        assert(_front != nullptr && "REAR IS NULLPOINTER");
        if(_rear == _front)
            _rear = nullptr;
        _size--;
        return _delete_node(_front, _front);
    }

    Iterator begin() const{
        return Iterator(_front);
    }                                     //Iterator to the head node
    Iterator end() const{
        return Iterator(nullptr);
    }                                       //Iterator to NULL
    void print_pointers(){
        _print_list(_front);
    }
    int size() const { return _size; }

    template<typename TT>
    friend ostream& operator << (ostream& outs, const Queue<TT>& printMe){
        for(node<T>* temp = printMe._front; temp != nullptr; temp = temp->_next){
            outs << temp->_item << " ";
        }
        return outs;
    }
private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};

#endif