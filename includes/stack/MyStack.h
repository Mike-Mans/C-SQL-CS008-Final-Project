#ifndef MYSTACK_H
#define MYSTACK_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include "../linked_list_functions/linkedlistfunctionsTemplated.h"

using namespace std;

template <typename ITEM_TYPE>
class Stack{
public:
    class Iterator{
    public:
        friend class Stack;                 //give access to list to access _ptr
        Iterator(){_ptr = nullptr;}            //default ctor
        Iterator(node<ITEM_TYPE>* p){       //Point Iterator to where p is pointing to
            _ptr = p;
        }
        ITEM_TYPE operator *(){
            assert(_ptr != nullptr && "PTR IS NULLPTR");
            return _ptr->_item;
        }    //dereference operator

        bool is_null(){return _ptr == nullptr;}            //true if _ptr is NULL
        
        friend bool operator !=(const Iterator& left, const Iterator& right)  //true if left != right
        {
            return left._ptr != right._ptr;
        }

        friend bool operator ==(const Iterator& left, const Iterator& right)  //true if left == right
        {
            return left._ptr == right._ptr;
        }

        Iterator& operator++(){                        //member operator:++it
                                                       // or ++it = new_value
            assert(_ptr != nullptr);
            _ptr = _ptr->_next;
            return *this;
        }

        friend Iterator operator++(Iterator& it, int unused){        //friend operator: it++
            assert(it._ptr != nullptr);
            Iterator temp = it;
            it._ptr = it._ptr->_next;
            return temp;
        }

    private:
        node<ITEM_TYPE>* _ptr;    //pointer being encapsulated
    };

    //BIG THREE
    Stack(){
        _top = nullptr;
        _size = 0;
    }
    Stack(const Stack<ITEM_TYPE>& copyMe){
        _top = _copy_list(copyMe._top);
        _size = copyMe._size;
    }
    ~Stack(){
        _clear_list(_top);
        _top = nullptr;
        _size = 0;
    }

    Stack<ITEM_TYPE>& operator=(const Stack<ITEM_TYPE>& RHS){
        if(this != &RHS){
            _top = _copy_list(RHS._top);
            _size = RHS._size;
        }
        return *this;
    }
    ITEM_TYPE top(){
        // assert(_top != nullptr && "TOP IS NULLPOINTER");
        if(_top == nullptr)
            throw runtime_error("INVALID EXPRESSION");
        return _top->_item;
    }
    bool empty(){
        return _top == nullptr;
    }
    void push(ITEM_TYPE item){
        _insert_head(_top, item);
        _size++;
    }
    ITEM_TYPE pop(){
        // assert(_top != nullptr && "TOP IS NULLPOINTER");
        if(_top == nullptr)
            throw runtime_error("INVALID EXPRESSION");
        _size--;
        return _delete_node(_top, _top);
    }

    template<typename T>
    friend ostream& operator<<(ostream& outs, const Stack<T>& printMe){
        for(node<ITEM_TYPE>* temp = printMe._top; temp != nullptr; temp = temp->_next){
            outs << temp->_item << " ";
        }
        return outs;
    }
    Iterator begin() const{
        return Iterator(_top);
    }                   //Iterator to the head node
    Iterator end() const{
        return Iterator(nullptr);
    }                     //Iterator to NULL
    int size() const { return _size; }

private:
    node<ITEM_TYPE>* _top;
    int _size;
};

#endif