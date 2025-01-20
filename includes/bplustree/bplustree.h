#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include "btree_array_funcs.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <vector>

using namespace std;

template <class T>
class BPlusTree
{
public:
    class Iterator{
    public:
        friend class BPlusTree;
        Iterator(BPlusTree<T>* _it = nullptr, int _key_ptr = 0): it(_it), key_ptr(_key_ptr){ }

        T operator *(){
            return this->it->data[this->key_ptr];
        }

        Iterator operator++(int un_used){
            assert(this->it != nullptr && "THIS->IT == nullptr --- BPLUSTREE ITERATOR ++");
            Iterator copyIt = Iterator(this->it, this->key_ptr);

            //too big for array, move onto next BTREE
            if(this->key_ptr + 1 >= this->it->data_count){
                // if(this->it->next == nullptr)
                //     assert("ATTEMPTING TO MOVE TO B+TREE THAT DOES NOT EXIST --- BPLUSTREE ITERATOR ++");
                this->it = this->it->next;
                this->key_ptr = 0;
            }

            //move to next element;
            else
                this->key_ptr++;

            //return the copy
            return copyIt;
        }

        Iterator operator++(){
            assert(this->it != nullptr && "THIS->IT == nullptr --- BPLUSTREE ITERATOR ++");
            //too big for array, move onto next BTREE
            if(this->key_ptr + 1 >= this->it->data_count){
                // if(this->it->next == nullptr)
                //     assert("ATTEMPTING TO MOVE TO B+TREE THAT DOES NOT EXIST --- BPLUSTREE ITERATOR ++");
                this->it = this->it->next;
                this->key_ptr = 0;
            }

            //move to next element;
            else
                this->key_ptr++;

            //return refernce to the iterator itself
            return *this;
        }

        friend bool operator ==(const Iterator& lhs, const Iterator& rhs){
            if(lhs.it != nullptr && rhs.it != nullptr)
                return lhs.it == rhs.it && lhs.key_ptr == rhs.key_ptr;
            return lhs.it == rhs.it;
        }

        friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
            return !(lhs == rhs);
        }

        void print_Iterator(){
            if(it){
                cout<<"iterator: ";
                print_array(it->data, it->data_count, key_ptr);
            }
            else{
                cout<<"iterator: nullptr, key_ptr: "<<key_ptr<<endl;
            }
        }

        bool is_nullptr(){
            return !it;
        }

        void info(){
            cout<<endl<<"Iterator info:"<<endl;
            cout<<"key_ptr: "<<key_ptr<<endl;
            cout<<"it: "<<*it<<endl;
        }

    private:
        BPlusTree<T>* it;
        int key_ptr;
    };

    BPlusTree(bool dups = false);
    BPlusTree(T *a, int size, bool dups = false);

    //big three:
    BPlusTree(const BPlusTree<T>& other);
    ~BPlusTree();
    BPlusTree<T>& operator =(const BPlusTree<T>& RHS);

    void copy_tree(const BPlusTree<T>& other);  //copy other into this object
    void copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_node);

    void insert(const T& entry);   //insert entry into the tree
    void remove(const T& entry);   //remove entry from the tree
    void clear_tree();             //clear this object (delete all nodes etc.)

    bool contains(const T& entry) const; //true if entry can be found
    T& get(const T& entry);              //return a reference to entry
    const T& get(const T& entry) const;   //return a reference to entry
    T& get_existing(const T& entry);     //return a reference to entry
    Iterator find(const T& key);         //return an iterator to this key.
                                         //     nullptr if not there.
    Iterator lower_bound(const T& key);  //return first that goes NOT BEFORE
                                         // key entry or next if does not
                                         // exist: >= entry
    Iterator upper_bound(const T& key);  //return first that goes AFTER key
                                         //exist or not, the next entry  >entry

    int size() const;                    //count the number of elements

    bool empty() const;                  //true if the tree is empty

    void print_tree(int level = 0,
                    ostream &outs=cout) const;

    friend ostream& operator<<(ostream& outs,
                               const BPlusTree<T>& print_me){
        print_me.print_tree(0, outs);
        return outs;
    }

    bool is_valid();
    string in_order();
    string post_order();
    string pre_order();

    Iterator begin();
    Iterator end();
    BPlusTree<T>* get_smallest_node(); //change back to private

    ostream& list_keys(Iterator from = nullptr, Iterator to = nullptr){
        if (from == nullptr) from = begin();
        if (to == nullptr) to = end();
        for (Iterator it = from; it != to; it++)
            cout<<*it<<" ";
        return cout;
    }

private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok;                        //true if duplicate keys are allowed
    int data_count;                      //number of data elements
    int child_count;                     //number of children
    T data[MAXIMUM + 1];                 //holds the keys
    BPlusTree* subset[MAXIMUM + 2] =  {nullptr};      //subtrees
    bool is_leaf() const;             //true if this is a leaf node
    BPlusTree* next = nullptr;

    T* find_ptr(const T& entry);         //return a pointer to this key.
                                         // nullptr if not there.

    //insert element functions
    void loose_insert(const T& entry);   //allows MAXIMUM+1 data elements in
                                         //   the root
    void fix_excess(int i);              //fix excess in child i

    //remove element functions:
    void loose_remove(const T& entry);  //allows MINIMUM-1 data elements
                                        //  in the root

    BPlusTree<T>* fix_shortage(int i);  //fix shortage in child i
    // and return the smallest key in this subtree
    void get_smallest(T& entry);      //entry := leftmost leaf
    void get_biggest(T& entry);       //entry := rightmost leaf
    void remove_biggest(T& entry);    //remove the biggest child of tree->entry
    void transfer_left(int i);        //transfer one element LEFT from child i
    void transfer_right(int i);       //transfer one element RIGHT from child i
    BPlusTree<T> *merge_with_next_subset(int i); //merge subset i with  i+1
};

//IMPLEMENTATIONS -----------------------------------------------------------------------

template <class T>
BPlusTree<T>::BPlusTree(bool dups){
    dups_ok = dups;
    data_count = 0;
    child_count = 0;
}

template <class T>
BPlusTree<T>::BPlusTree(T *a, int size, bool dups){
    dups_ok = dups;
    data_count = 0;
    child_count = 0;
    for(int i = 0; i < size; i++){
        this->insert(a[i]);
    }
}

//big three:
template <class T>
BPlusTree<T>::BPlusTree(const BPlusTree<T>& other){
    this->copy_tree(other);
}

template <class T>
BPlusTree<T>::~BPlusTree(){
    this->clear_tree();
}

template <class T>
BPlusTree<T>& BPlusTree<T>::operator =(const BPlusTree<T>& RHS){
    this->copy_tree(RHS);
    return *this;
}

//insert functions
template <class T>
void BPlusTree<T>::insert(const T& entry){
    loose_insert(entry);

    //GROW TREE
    if(this->data_count == MAXIMUM + 1){

        //Make a copy of the arrays from this into newTree
        BPlusTree* newTree = new BPlusTree();
        copy_array(newTree->data, this->data, newTree->data_count, this->data_count);
        copy_array(newTree->subset, this->subset, newTree->child_count, this->child_count);

        //Set this to empty, reset child count and data count
        for(int i = 0; i < this->child_count; i++){
            this->subset[i] = nullptr;
        }

        this->child_count = 1;
        this->data_count = 0;
        this->subset[0] = newTree;
        this->fix_excess(0);
    }
}

template <class T>
void BPlusTree<T>::loose_insert(const T& entry){
    //Call First_Greater_Equals
    int i = first_ge(this->data, this->data_count, entry);

    //it is a leaf, insert at this level (overrides duplicate values)
    if(this->is_leaf()){
        insert_item(this->data, i, this->data_count, entry);
    }

    //handle duplicates -- override
    else if(i < this->data_count && this->data[i] == entry){ 
        this->data[i] = entry;
        this->subset[i + 1]->get_smallest_node()->data[0] = entry;
    }

    else{
        // enter recursive call to next level
        this->subset[i]->loose_insert(entry);

        // call fix excess
        if(this->subset[i]->data_count == MAXIMUM + 1){
            this->fix_excess(i);
        }
    }
}

template <class T>
void BPlusTree<T>::fix_excess(int i){
    BPlusTree* temp = new BPlusTree();

    //split the data
    split(this->subset[i]->data, this->subset[i]->data_count, temp->data, temp->data_count);

    //split the subset
    split(this->subset[i]->subset, this->subset[i]->child_count, temp->subset, temp->child_count);

    //make everything [child_count, MAXIMUM + 2] nullptr, for both this->subset[i]->subset & temp->subset
    for(int j = this->subset[i]->child_count; j < MAXIMUM + 2; j++){
        this->subset[i]->subset[j] = nullptr;
    }
    for(int j = temp->child_count; j < MAXIMUM + 2; j++){
        temp->subset[j] = nullptr;
    }

    //grab the last element from child's data array, and decrement the array size (detach)
    T tempData = this->subset[i]->data[--this->subset[i]->data_count];

    //shift everything over in this, and insert (everything is done using array function insert_item)
    insert_item(this->data, i, this->data_count, tempData); 
    insert_item(this->subset, i + 1, this->child_count, temp); 

    //make the left subtree's next point to the right subtree
    temp->next = subset[i]->next;
    subset[i]->next = temp;

    //for b+tree, if it is a leaf then prepend the item that was brought up to the right leaf's data
    if(this->subset[i+1]->is_leaf()){ 
        assert(this->subset[i]->is_leaf() && "THIS SHOULD ALSO BE A LEAF LOGICALLY ---- B+TREE, FIX_EXCESS");

        //prepend the data element
        insert_item(this->subset[i+1]->data, 0, this->subset[i+1]->data_count, this->data[i]);
    }
}

//remove functions
template <class T>
void BPlusTree<T>::remove(const T& entry){
    //call loose remove
    this->loose_remove(entry);
    //SHRINK TREE
    if(this->data_count == 0 && this->child_count == 1){
        //cout << "ENTERING SHRINK TREE" << endl;
        //make a temporary pointer to the child, and set this->child_count to 0
        BPlusTree* temp = this->subset[0];
        this->child_count = 0;

        //copy the data array from temp to this
        copy_array(this->data, temp->data, this->data_count, temp->data_count);
        
        //copy the subset array from temp to this
        copy_array(this->subset, temp->subset, this->child_count, temp->child_count);

        //everything is copied over, so we can simply free the temp BTree (I make sure to set temp->data_count and temp->child_count to 0 first so destructor calls properly)
        temp->child_count = 0;
        temp->data_count = 0;
        delete temp;
    }
}

template <class T>
void BPlusTree<T>::loose_remove(const T& entry){
    //          |   !found    |   found       |
    //    ------|-------------|---------------|-------
    //    leaf  | 2A: nothing | 2B: delete    |
    //          |     to do   |    target     |
    //    ------|-------------|---------------|-------
    //    !leaf | 2C: loose   | 2D: replace   |
    //          |    remove   |    w/ biggest |
    //    ------|-------------|---------------|-------
    
    //Call First_Greater_Equals
    bool case2D = false;
    int i = first_ge(this->data, this->data_count, entry);

    if(this->is_leaf()){
        //CASE 2A -- root has no children and target was not found
        if(i >= this->data_count || this->data[i] != entry){ } //we did not find the target (either i is out of bounds or the element did not exist in the list)
        
        //CASE 2B -- root has no children and target WAS found
        else{  //we found the element in the list
            T itemRemoved;
            delete_item(this->data, i, this->data_count, itemRemoved);
            assert(itemRemoved == entry && "ITEM REMOVED DOES NOT MATCH ENTRY --- LOOSE REMOVE");
        }
    }
    else{
        //CASE 2C -- root has children and target was not found
        if(i >= this->data_count || this->data[i] != entry){ //we did not find the target (either i is out of bounds or the element did not exist in the list)
            //Enter the recursive case to the next level
            assert(this->subset[i] != nullptr && "TRYING TO DEREFERENCE A NULLPTR --- LOOSE REMOVE");
            assert(i < this->child_count && "Trying to access subset[i] when i >= child_count--- LOOSE REMOVE");
            this->subset[i]->loose_remove(entry);
        }
        //CASE 2D -- root has children and target WAS found
        else{ //We found the element
            T itemGrabbed;
            this->subset[i + 1]->loose_remove(entry); //remove from right subbranch according to B+Tree Algorithm
            this->subset[i + 1]->get_smallest(itemGrabbed);

            // //TESTING PURPOSES
            // this->print_tree();
            // BPlusTree* temp = this->subset[i + 1]->get_smallest_node();
            // cout << "PRINTING ARR ";
            // temp->print_tree();
            // cout << temp->data_count << endl;
            // cout << "AFTER LOOP " << temp->data[0] << " ";
            // cout << endl << "ITEM GRABBED DURING REMOVE" << itemGrabbed << endl;
            // //END TESTING PURPOSES
            this->data[i] = itemGrabbed;
            case2D = true;
        }
    }
    
    //fix shortage all the way up
    for(int j = 0; j < this->child_count; j++){
        if(this->subset[j]->data_count < MINIMUM){
            //cout << "ENTERING FIX SHORTAGE IN LOOP" << endl;
            this->fix_shortage(j);
        }
    }
    if(case2D && i + 1 < this->child_count){
        T itemGrabbed;
        this->subset[i + 1]->get_smallest(itemGrabbed);
        this->data[i] = itemGrabbed;
    }
}

template <class T>
BPlusTree<T>* BPlusTree<T>::fix_shortage(int i){
    //Case 1 --- Transfer an extra entry from subset[i-1] (Rotate Right)
    if(i + 1 < this->child_count && this->subset[i + 1]->data_count > MINIMUM){
        //cout << "ENTERING CASE 2 --- FIX_SHORTAGE" << endl;
        this->transfer_left(i);
    }

    //Case 2 --- Transfer an extra entry from subset[i+1] (Rotate Left)
    else if(i - 1 >= 0 && this->subset[i - 1]->data_count > MINIMUM){
        //cout << "ENTERING CASE 1 --- FIX_SHORTAGE" << endl;
        this->transfer_right(i);
    }

    //Case 4 --- Combine subset[i] with subset[i+1]
    else if(i - 1 >= 0 && this->subset[i - 1]->data_count == MINIMUM){
        //cout << "ENTERING CASE 3 --- FIX_SHORTAGE" << endl;   
        this->merge_with_next_subset(i);
    }

    //Case 3 --- Combine subset[i] with subset[i-1]
    else if(i + 1 < this->child_count && this->subset[i + 1]->data_count == MINIMUM){
        //cout << "ENTERING CASE 4 --- FIX_SHORTAGE" << endl;          
        this->merge_with_next_subset(i + 1);
    }

    else{
        assert(false && "IMPOSSIBLE CASE IN FIX_SHORTAGE REACHED");
    }
    return this;
}

template <class T>
void BPlusTree<T>::get_biggest(T& entry){
    if(this->is_leaf())
        entry = this->data[this->data_count - 1];
    else    
        this->subset[this->child_count - 1]->get_biggest(entry);
}

template <class T>
void BPlusTree<T>::remove_biggest(T& entry){
    if(!this->is_leaf()) //Recursive call to next level
        this->subset[this->child_count - 1]->remove_biggest(entry);
    else //we are at the base level (leaves), now remove the largest in data and place in entry
        delete_item(this->data, this->data_count - 1, this->data_count, entry);

    //call fix shortage all the way up
    for(int i = 0; i < this->child_count; i++){
        if(this->subset[i]->data_count < MINIMUM){
            //cout << "ENTERING FIX SHORTAGE IN LOOP" << endl;
            this->fix_shortage(i);
        }
    }  
}

template <class T>
void BPlusTree<T>::transfer_left(int i){
    //i is the subbranch that is in shortage
    //cout << "ENTERING ROTATE LEFT" << endl;
    assert(i < this->data_count && "DATA_COUNT - 1 IS THE LARGEST POSSIBLE VALUE OF I --- ROTATE_LEFT");
    if(!this->subset[i]->is_leaf()){
        T rootItem;
        T rightItem;
        BPlusTree* rightTree;

        //detach
        delete_item(this->subset[i + 1]->data, 0, this->subset[i + 1]->data_count, rightItem);
        if(!this->subset[i + 1]->is_leaf())
            delete_item(this->subset[i + 1]->subset, 0, this->subset[i + 1]->child_count, rightTree);

        //delete the appropriate item
        delete_item(this->data, i, this->data_count, rootItem);

        //insert appropriately 
        insert_item(this->data, i, this->data_count, rightItem);

        //attach at end
        attach_item(this->subset[i]->data, this->subset[i]->data_count, rootItem);
        if(!this->subset[i + 1]->is_leaf())
            attach_item(this->subset[i]->subset, this->subset[i]->child_count, rightTree);
    }
    else{
        T item;
        delete_item(this->subset[i + 1]->data, 0, this->subset[i + 1]->data_count, item);
        attach_item(this->subset[i]->data, this->subset[i]->data_count, item);
        this->data[i] = this->subset[i + 1]->data[0];
    }
}

template <class T>
void BPlusTree<T>::transfer_right(int i){
    //i is the subbranch that is in shortage
    //cout << "ENTERING ROTATE RIGHT" << endl;
    assert(i >= 1 && "1 IS THE LOWEST POSSIBLE VALUE OF I --- ROTATE_RIGHT");
    if(!this->subset[i]->is_leaf()){
        T rootItem;
        T leftItem;
        BPlusTree* leftTree;

        //detach
        detach_item(this->subset[i - 1]->data, this->subset[i - 1]->data_count, leftItem);
        if(!this->subset[i - 1]->is_leaf())
            detach_item(this->subset[i - 1]->subset, this->subset[i - 1]->child_count, leftTree);

        //delete the appropriate item
        delete_item(this->data, i - 1, this->data_count, rootItem);

        //insert appropriately 
        insert_item(this->data, i - 1, this->data_count, leftItem);

        //prepend
        insert_item(this->subset[i]->data, 0, this->subset[i]->data_count, rootItem);
        if(!this->subset[i - 1]->is_leaf())
            insert_item(this->subset[i]->subset, 0, this->subset[i]->child_count, leftTree);
    }
    else{ //leaves only
        T item;
        detach_item(this->subset[i - 1]->data, this->subset[i - 1]->data_count, item);
        insert_item(this->subset[i]->data, 0, this->subset[i]->data_count, item);
        this->data[i - 1] = item;
    }
}

template <class T>
BPlusTree<T>* BPlusTree<T>::merge_with_next_subset(int i){
    //in this call, either i or i - 1 are in shortage and require a merge
    //it will move all elements from i into i - 1 (i gets removed)
    //cout << "ENTERING MERGE WITH NEXT SUBSET" << endl;
    assert(this->subset[i] != nullptr && "this->subset[i] is nullptr");
    assert(this->subset[i - 1] != nullptr && "this->subset[i - 1] is nullptr"); 

    //Put the desired item from the root and attach him to i - 1's ->data
    T rootItem;
    BPlusTree* deletedTree;
    delete_item(this->data, i - 1, this->data_count, rootItem);
    if(!this->subset[i - 1]->is_leaf()) //if its not a leaf
        attach_item(this->subset[i - 1]->data, this->subset[i - 1]->data_count, rootItem);

    //will merge appropriate arrays and adjust their sizes
    merge(this->subset[i - 1]->data, this->subset[i - 1]->data_count, this->subset[i]->data, this->subset[i]->data_count);
    merge(this->subset[i - 1]->subset, this->subset[i - 1]->child_count, this->subset[i]->subset, this->subset[i]->child_count);
    
    //set the next pointers appropriately
    if(this->subset[i - 1]->is_leaf()) //if it is a leaf
        this->subset[i - 1]->next = this->subset[i]->next;

    //remove this->subset[i] from the subset. Then call destructor on that BTree, which wont clear the rest of the tree given that the child count is 0
    assert(this->subset[i]->child_count == 0 && "CHILD COUNT MUST BE 0 TO CALL DESTRUCTOR --- MERGE WITH NEXT SUBSET");
    delete_item(this->subset, i, this->child_count, deletedTree);

    assert(deletedTree->child_count == 0 && "DELETEDTREE CHILD COUNT MUST BE 0 --- MERGE WITH NEXT SUBSET");
    delete deletedTree;   //frees memory and calls destructor (which doesn't delete the trees, since clear_tree on does nothing when child_count is 0);
    return this;
}

//copy functions
template <class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other){
    //other must be an empty tree with data_count = 0 and child_count = 0
    BPlusTree* tempPointer = nullptr;
    this->copy_tree(other, tempPointer);
}

template <class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_node){
    //copy the number of elements in data and subset from other to this
    this->data_count = other.data_count;
    this->child_count = other.child_count;

    //iteratively loop through and copy all data elements
    for(int i = 0; i < this->data_count; i++){
        this->data[i] = other.data[i];
    }

    //recursively deep copy of subset elements
    for(int i = 0; i < this->child_count; i++){
        if(other.subset[i] != nullptr){
            this->subset[i] = new BPlusTree<T>();
            this->subset[i]->copy_tree(*(other.subset[i]), last_node);
        }
    }

    if(this->is_leaf()){
        if(last_node == nullptr)
            last_node = this;
        else
            last_node->next = this;
            last_node = this;
    }
}

//find functions
template <class T>
bool BPlusTree<T>::contains(const T& entry) const{
    bool found = false;
    int i = first_ge(this->data, this->data_count, entry);
    //if it is out of bounds of the data array (AKA if i == data_count), it possibly exists in far right subtree
    if(i < this->data_count){
        //the index is not out of bounds, 
        found = (this->data[i] == entry);
    }

    //if found, return a refernence to the item
    if(found){
        return true;
    }

    //otherwise, search the corresponding subtree and 
    else{
        //the subtree does not exist, hence it does not exist, so return nullptr
        if(this->subset[i] == nullptr || this->is_leaf())
            return false;
        else
            return this->subset[i]->contains(entry);
    }
}

template <class T>
T& BPlusTree<T>::get(const T& entry){
    bool debug = false;
    if(debug)
        cout << "ENTERING BPlusTree<T>::get" << endl;
    T* ptr = this->find_ptr(entry);
    if(ptr != nullptr){
        if(debug)
            cout << "ENTERING BPlusTree<T>::get TRUE CONDITION" << endl;
        // *ptr = entry; //SHOULD NOT BE OVERRIDING IT*******
        if(debug)
            cout << *ptr << endl;
        return *ptr;
    }
    
    //does not exist, so insert it then return it
    // cout << "inserting it" << endl;
    if(debug)
        cout << "ENTERING BPlusTree<T>::get FALSE CONDITION" << endl;
    this->insert(entry);
    if(debug)
        cout << *(this->find_ptr(entry)) << endl;
    return *(this->find_ptr(entry));
}

template <class T>
const T& BPlusTree<T>::get(const T& entry) const{
    // cout << "ENTERING CONST BPlusTree<T>::get" << endl;
    int i = first_ge(this->data, this->data_count, entry);
    if(i >= this->data_count || this->data[i] != entry){ //not found -- recursive call on i subbranch or assert
        assert(this->is_leaf() && "ITEM DOES NOT EXIST IN B+TREE --- CONST GET, B+Tree");
        return this->subset[i]->get(entry);
    }
    else{ //it was found! -- determine if it was found on a leaf or not
        if(this->is_leaf())
            return this->data[i];
        else   
            return this->subset[i + 1]->get(entry);
    }
}

template <class T>
T* BPlusTree<T>::find_ptr(const T& entry){
    // cout << "ENTERING BPlusTree<T>::find_ptr" << endl;
    bool found = false;
    int i = first_ge(this->data, this->data_count, entry);
    //if it is out of bounds of the data array (AKA if i == data_count), it possibly exists in far right subtree
    if(i < this->data_count){
        //the index is not out of bounds, 
        found = (this->data[i] == entry);
    }

    //if found, return a refernence to the item
    if(found){
        if(this->is_leaf()){ //it exists only in the linked list, so just return a reference to this
            // cout << "CASE 1: BPlusTree<T>::find_ptr ------- found: " << data[i] << endl;
            return &data[i];
        }
        else{
            // cout << "CASE 2: BPlusTree<T>::find_ptr ------- found: " << this->subset[i + 1]->get_smallest_node()->data[0] << endl;
            return &this->subset[i + 1]->get_smallest_node()->data[0];
        }
    }

    //otherwise, search the corresponding subtree and 
    else{
        //the subtree does not exist, hence it does not exist, so return nullptr
        if(this->subset[i] == nullptr || this->is_leaf()){
            // cout << "BPlusTree<T>::find_ptr ------- returning nullptr" << endl;
            return nullptr;
        }
        else
            return this->subset[i]->find_ptr(entry);
    }
}

template <class T>
T& BPlusTree<T>::get_existing(const T& entry){
    T* temp;
    return *temp;
}

//get smallest functions
template <class T>
BPlusTree<T>* BPlusTree<T>::get_smallest_node(){
    if(this->is_leaf())
        return this;
    else   
        return this->subset[0]->get_smallest_node();
}

template <class T>
void BPlusTree<T>::get_smallest(T& entry){
    if(this->is_leaf())
        entry = this->data[0];
    else
        this->subset[0]->get_smallest(entry);
}

//clear tree function
template <class T>
void BPlusTree<T>::clear_tree(){
    for(int i = 0; i < this->child_count; i++){
        //clean up all of my children, and then call the destructor to free them from memory. Set to nullptr to be safe
        if(this->subset[i] != nullptr){
            this->subset[i]->clear_tree();
            delete this->subset[i];
            this->subset[i] = nullptr;
        }
    }
    this->child_count = 0;
    this->data_count = 0;
    this->next = nullptr;
}

//Iterator Functions
template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::find(const T& entry){
    bool found = false;
    int i = first_ge(this->data, this->data_count, entry);
    //if it is out of bounds of the data array (AKA if i == data_count), it possibly exists in far right subtree
    if(i < this->data_count){
        //the index is not out of bounds, 
        found = (this->data[i] == entry);
    }

    //if found, return a refernence to the item
    if(found){
        if(this->is_leaf()) //it exists only in the linked list, so just return a reference to this
            return Iterator(this, i);
        else{
            BPlusTree* smallestTree = this->subset[i + 1]->get_smallest_node();    
            return Iterator(smallestTree, first_ge(smallestTree->data, smallestTree->data_count, entry));
        }
    }

    //otherwise, search the corresponding subtree and 
    else{
        //the subtree does not exist, hence it does not exist, so return nullptr
        if(this->subset[i] == nullptr || this->is_leaf())
            return Iterator(nullptr);
        else
            return this->subset[i]->find(entry);
    }
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::lower_bound(const T& key){
    int i = first_ge(this->data, this->data_count, key);
    if(i >= this->data_count || this->data[i] != key){ //not found
        if(this->is_leaf()){
            if(i >= this->data_count){
                if(this->next == nullptr) //at the end, so Iterator(nullptr)
                    return Iterator(nullptr);
                else{ //in the middle of btree but last element in current array
                    BPlusTree<T>::Iterator temp = (Iterator(this, i - 1));
                    temp++;
                    return temp;
                }
            }
            else
                return Iterator(this, i);
        }
        else   
            return this->subset[i]->lower_bound(key); 
    }
    else{ //it was found
        if(this->is_leaf())
            return Iterator(this, i);
        else   //breakcrumb
            return this->subset[i + 1]->lower_bound(key); 
    }
    assert("SHOULD NOT END UP HERE LOGICALLY ----- ITERATOR LOWER BOUND, BPLUSTREE");
    return Iterator(nullptr);
}

template <class T> //basically lowerbound + 1 if it is equal
typename BPlusTree<T>::Iterator BPlusTree<T>::upper_bound(const T& key){
    Iterator tempIt = lower_bound(key);
    if(tempIt.it != nullptr && ((*tempIt) == key))
        tempIt++;
    return tempIt;
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::begin(){
    BPlusTree* temp = this->get_smallest_node();
    if(temp->data_count == 0)
        return Iterator(nullptr);
    else
        return Iterator(temp);
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::end(){
    return Iterator(nullptr);
}

//Misc Functions
template <class T>
int BPlusTree<T>::size() const{
    return this->data_count;
}

template <class T>
bool BPlusTree<T>::empty() const{
    return this->data_count == 0 && this->child_count == 0;
}

template <class T>
bool BPlusTree<T>::is_leaf() const{
    return this->child_count == 0;
}

template <class T>
bool BPlusTree<T>::is_valid(){
    //should check that every data[i] < data[i+1]
    for(int i = 0; i < this->data_count - 1; i++){
        if(this->data[i] > this->data[i + 1]){
            this->print_tree();
            return false;
        }
    }

    if (is_leaf())
        return true;
    
    //data[data_count-1] must be less than equal to 
    //  every subset[child_count-1]->data[ ]
    else{
        T item;
        int i;
        for(i = 0; i < this->data_count; i++){
            this->subset[i]->get_biggest(item);
            if(this->data[i] <= item){
                //this->print_tree();
                cout << "CASE 1: " <<this->data[i] << "-----" << item << endl;
                return false;
            }

            this->subset[i + 1]->get_smallest(item);
            if(this->data[i] != item){
                //this->print_tree();
                cout << "CASE 2: " <<this->data[i] << "-----" << item << endl;
                return false;
            }

            if(!this->subset[i]->is_valid()){
                //this->print_tree();
                cout << "CASE 3" << endl;
                return false;
            }
        }
        if(!this->subset[this->child_count - 1]->is_valid()){
            //this->print_tree();
            // cout << "CASE 4" << endl;
            return false;
        }
    }
    return true;
}

//print and string functions
template <class T>
void BPlusTree<T>::print_tree(int level, ostream &outs) const{
    bool debugPrint = false;
    for(int i = data_count - 1; i >= 0; i--){
        if(subset[i + 1] != nullptr && i + 1 < this->child_count){
            subset[i + 1]->print_tree(level + 1, outs); 
        }
        outs << setw(4*level) << " " << "[" << data[i] << "] ";
        if(debugPrint)
            outs << " " << this->data_count << ", " << this->child_count;
        outs << endl;
    }
    if(subset[0] != nullptr && child_count != 0){
        subset[0]->print_tree(level + 1, outs);
    }
}

template <class T>
string BPlusTree<T>::in_order(){
    string str = "";
    int i = 0;
    for( ; i < this->data_count; i++){
        if(i < this->child_count && this->subset[i] != nullptr)
            str += this->subset[i]->in_order();
        str += to_string(this->data[i]) + "|";
    }
    if(i < this->child_count && this->subset[i] != nullptr)
        str += this->subset[i]->in_order();
    return str;
}

template <class T>
string BPlusTree<T>::pre_order(){
    string str = "";
    int i;
    for(i = 0; i < this->data_count; i++){
        str += to_string(this->data[i]) + "|";
        if(i < this->child_count && this->subset[i] != nullptr)
            str += this->subset[i]->pre_order();
    }
    if(i < this->child_count && this->subset[i] != nullptr)
        str += this->subset[i]->pre_order();
    return str;
}

template <class T>
string BPlusTree<T>::post_order(){
    string str = "";
    if(this->child_count != 0 && this->subset[0] != nullptr)
        str += this->subset[0]->post_order();
    for(int i = 0; i < this->data_count; i++){
        if(i + 1 < this->child_count && this->subset[i + 1] != nullptr)
            str += this->subset[i + 1]->post_order();
        str += to_string(this->data[i]) + "|";
    }
    return str;
}

#endif