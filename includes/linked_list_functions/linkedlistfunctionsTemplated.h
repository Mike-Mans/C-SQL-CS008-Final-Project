#ifndef LINKEDLISTFUNCTIONSTEMPLATED_H
#define LINKEDLISTFUNCTIONSTEMPLATED_H
#include <iostream>
#include "../node/node.h"

using namespace std;

//Linked List General Functions:
template <typename T>
void _print_list(node<T>* head);

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head);

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head,
                            T key);

template <typename T>
node<T>* _insert_head(node<T> *&head,
                            T insert_this);

//insert after ptr: insert head if marker null
template <typename T>
node<T>* _insert_after(node<T>*& head,
                                node<T> *after_this,
                                T insert_this);

//insert before ptr: insert head if marker null
template <typename T>
node<T>* _insert_before(node<T>*& head,
                                node<T>* before_this,
                                T insert_this);

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* prev_to_this);

//delete, return item
template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this);

//duplicate the list...
template <typename T>
node<T>* _copy_list(node<T>* head);

//duplicate the list, return pointer to last node in dest... 
//     use this function in your queue big three 
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src);

//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head);

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos);

//Linked List General Functions:
template <typename T>
void _print_list(node<T>* head){
    for(node<T>* curr = head; curr != nullptr; curr = curr->_next){
        cout << curr->_item << " ";
    }
}

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head){
    if(head->_next != nullptr)
        _print_list_backwards(head->_next);
    cout << head->_item << " ";
}

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head, T key){
    for(node<T>* curr = head; curr != nullptr; curr = curr->_next){
        if(curr->_item == key)
            return curr;
    }
    return nullptr;
}

template <typename T>
node<T>* _insert_head(node<T> *&head, T insert_this){
    if(head == nullptr){
        head = new node<T>(insert_this);
    }
    else{
        node<T>* temp = new node<T>(insert_this);
        temp->_next = head;
        head->_prev = temp;
        head = temp;
    }
    return head;
}

//insert after ptr: insert head if marker null
template <typename T>
node<T>* _insert_after(node<T>*& head, node<T> *after_this, T insert_this){
    //case1: if the list is empty
    if(head == nullptr){
        return _insert_head(head, insert_this);
    }
    //case2: if after_this is last element (also if list has only 1 element)
    else if(after_this->_next == nullptr){
        node<T>* temp = new node<T>(insert_this);
        after_this->_next = temp;
        temp->_prev = after_this;
        return temp;
    }
    //case3: if after_this is in the middle of the list or first with multiple elements
    else{
        node<T>* temp = new node<T>(insert_this);
        temp->_next = after_this->_next;
        temp->_prev = after_this;
        temp->_next->_prev = temp;
        after_this->_next = temp;
        return temp;
    }
}

//insert before ptr: insert head if marker null
template <typename T>
node<T>* _insert_before(node<T>*& head, node<T>* before_this, T insert_this){
    //case1: list is empty or only 1 element
    if(head == nullptr || head == before_this){
        return _insert_head(head, insert_this);
    }
    //case2: before_this is anywhere in the list but not head
    else{
        node<T>* temp = new node<T>(insert_this);
        temp->_prev = before_this->_prev;
        temp->_next = before_this;
        temp->_prev->_next = temp;
        before_this->_prev = temp;
        return temp;
    }
}

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* prev_to_this){
    assert(prev_to_this->_prev != nullptr && "No previous node to grab");
    return prev_to_this->_prev;
}

//delete, return item
template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this){
    //if list is empty
    assert(head != nullptr);
    assert(delete_this != nullptr && "List is empty, deleting node is impossible");
    T deleted_item = delete_this->_item;
    if(head == delete_this){
        //if list had 1 element
        if(delete_this->_next == nullptr){
            delete delete_this;
            head = nullptr;
        }
        //if list is more than 1 element and user wants to delete the head
        else{
            head = delete_this->_next;
            head->_prev = nullptr;
            delete delete_this;
        }
    }
    else{
        //if list is more than 1 element and user wants to delete in the middle of the list
        if(delete_this->_next != nullptr){
            delete_this->_next->_prev = delete_this->_prev;
            delete_this->_prev->_next = delete_this->_next;
            delete delete_this;
        }
        //if list is more than 1 element and user wants to delete last node.
        else{
            delete_this->_prev->_next = nullptr;
            delete delete_this;
        }
    }
    return deleted_item;
}

//duplicate the list...
template <typename T>
node<T>* _copy_list(node<T>* head){
    //list is empty
    if(head == nullptr)
        return nullptr;
    
    //list is non-empty. return newHead 
    node<T>* newHead = new node<T>(head->_item);
    node<T>* newTemp = newHead;

    //start from second node and add new nodes until the list reaches its end
    for(node<T>* temp = head->_next; temp != nullptr; temp = temp->_next){
        newTemp->_next = new node<T>(temp->_item);
        newTemp->_next->_prev = newTemp;
        newTemp = newTemp->_next;
    }

    //return head of new list
    return newHead;
}

//duplicate the list, return pointer to last node in dest... 
//     use this function in your queue big three 
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src){
    //list is empty
    if(src == nullptr){
        dest = nullptr;
        return nullptr;
    }
    
    //list is non-empty. return 
    dest = new node<T>(src->_item);
    node<T>* newTemp = dest;

    //start from second node and add new nodes until the list reaches its end
    for(node<T>* temp = src->_next; temp != nullptr; temp = temp->_next){
        newTemp->_next = new node<T>(temp->_item);
        newTemp->_next->_prev = newTemp;
        newTemp = newTemp->_next;
    }

    //return head of new list
    return newTemp;
}

//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head){
    //if the list is empty
    if(head == nullptr)
        return;
    if(head->_next == nullptr){
        delete head;
        return;
    }
    node<T>* temp = head->_next;
    while(temp->_next != nullptr){
        delete temp->_prev;
        temp = temp->_next;
    }
    delete temp->_prev;
    delete temp;
    head = nullptr;
}

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos){
    assert(head != nullptr && "Head is nullptr, cannot retrieve item in empty list");
    int count = 0;
    for(node<T>* temp = head; temp != nullptr; temp = temp->_next){
        if(count == pos)
            return temp->_item;
        count++;
    }
    assert(false && "pos was too large for the list, cannot retrieve item");
}
#endif