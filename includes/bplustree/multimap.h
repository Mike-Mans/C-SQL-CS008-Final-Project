#ifndef MULTIMAP_H
#define MULTIMAP_H

#include "bplustree.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <vector>

using namespace std;

template <typename K, typename V>
struct MPair{
    K key;
    vector<V> value_list;

    //--------------------------------------------------------------------------------
    /*      MPair CTORs:
     *  must have these CTORs:
     *  - default CTOR / CTOR with a key and no value: this will create an empty vector
     *  - CTOR with a key AND a value: pushes the value into the value_list
     *  _ CTOR with a key and a vector of values (to replace value_list)
     */
    //--------------------------------------------------------------------------------
    MPair(const K& k=K()){
        key = k;
    }

    MPair(const K& k, const V& v){
        key = k;
        value_list.push_back(v);
    }

    MPair(const K& k, const vector<V>& vlist){
        key = k;
        value_list = vlist;
    }

    //--------------------------------------------------------------------------------
    vector<V> get(){
        return value_list;
    }

    //You'll need to overlod << for your vector:
    friend ostream& operator <<(ostream& outs, const MPair<K, V>& print_me){
        outs << print_me.key << " : " << print_me.value_list;
        return outs;
    }
    
    friend bool operator ==(const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return lhs.key == rhs.key;
    }

    friend bool operator !=(const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return lhs.key != rhs.key;
    }

    friend bool operator < (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return lhs.key < rhs.key;
    }

    friend bool operator <= (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return lhs.key <= rhs.key;
    }

    friend bool operator > (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return lhs.key > rhs.key;
    }

    friend bool operator >= (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return lhs.key >= rhs.key;
    }

    friend MPair<K, V> operator + (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return MPair<K, V>();
    }
};

template <typename K, typename V>
class MMap
{
public:
    typedef BPlusTree<MPair<K, V> > map_base;
    class Iterator{
    public:
        friend class MMap;
        Iterator() { }

        Iterator(typename map_base::Iterator it){ 
            _it = it;
        }

        Iterator operator ++(int unused){
            return _it++;
        }

        Iterator operator ++(){
            return ++_it;
        }

        MPair<K, V> operator *(){
            return *_it;
        }

        friend bool operator ==(const Iterator& lhs, const Iterator& rhs){
            return lhs._it == rhs._it;
        }

        friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
            return lhs._it != rhs._it;
        }

    private:
        typename map_base::Iterator _it;
    };

    MMap();

// for Parser
    void print_lookup();

//  Iterators
    Iterator begin();
    MMap<K,V> copy();
    Iterator end();

//  Capacity
    int size() const;
    bool empty() const;

//  Element Access
    const vector<V>& operator[](const K& key) const;
    vector<V>& operator[](const K& key);
    V& at(const K& key);
    const V& at(const K& key) const;

//  Modifiers
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();

//  Operations:
    bool contains(const K& key) const;
    vector<V> &get(const K& key);

    Iterator find(const K& key);
    int count(const K& key);
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound
    //    equal_range:

    Iterator lower_bound(const K& key);
    Iterator upper_bound(const K& key);
    Iterator equal_range(const K& key);

    bool is_valid();

    friend ostream& operator<<(ostream& outs, const MMap<K, V>& print_me){
        outs<<print_me.mmap<<endl;
        return outs;
    }

private:
    BPlusTree<MPair<K, V> > mmap;
};

//IMPLEMENTATIONS -----------------------------------------------------------------------

template <typename K, typename V>
MMap<K,V>::MMap(){ }

template <typename K, typename V>
void MMap<K,V>::print_lookup(){
    for(Iterator it = this->begin(); it != this->end(); it++){
        cout << *it << endl;
    }
}

template <typename K, typename V>
typename MMap<K,V>::Iterator MMap<K,V>::begin(){
    return MMap<K, V>::Iterator(mmap.begin());
}

template <typename K, typename V>
MMap<K,V> MMap<K,V>::copy(){
    MMap<K,V> newMMap;
    newMMap.mmap.copy_tree(this->mmap);
    return newMMap;
}

template <typename K, typename V>
typename MMap<K,V>::Iterator MMap<K,V>::end(){
    return MMap<K, V>::Iterator(mmap.end());
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::lower_bound(const K& key){
    return MMap<K, V>::Iterator(mmap.lower_bound(MPair<K, V>(key)));
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::upper_bound(const K& key){
    return MMap<K, V>::Iterator(mmap.upper_bound(MPair<K, V>(key)));
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::equal_range(const K& key){
    return Iterator();
}

template <typename K, typename V>
int MMap<K,V>::size() const{
    return 0;
}

template <typename K, typename V>
bool MMap<K,V>::empty() const{
    return mmap.empty();
}

template <typename K, typename V>
const vector<V>& MMap<K,V>::operator[](const K& key) const{
    return mmap.get(MPair<K, V>(key)).value_list;
}

template <typename K, typename V>
vector<V>& MMap<K,V>::operator[](const K& key){
    return mmap.get(MPair<K, V>(key)).value_list;
}

template <typename K, typename V>
V& MMap<K, V>::at(const K& key){
    V* temp;
    return *temp;
}

template <typename K, typename V>
const V& MMap<K, V>::at(const K& key) const{
    const V* temp;
    return *temp;
}

template <typename K, typename V>
void MMap<K,V>::insert(const K& k, const V& v){
    mmap.get(MPair<K, V>(k)).value_list.push_back(v);
    // cout << "SUCCESSFULLY INSERTED ----- MULTIMAP INSERT" << endl;
}

template <typename K, typename V>
void MMap<K,V>::erase(const K& key){
    mmap.remove(MPair<K, V>(key));
}

template <typename K, typename V>
void MMap<K,V>::clear(){
    mmap.clear_tree();
}

template <typename K, typename V>
bool MMap<K,V>::contains(const K& key) const{
    return mmap.contains(MPair<K, V>(key));
}

template <typename K, typename V>
vector<V>& MMap<K,V>::get(const K& key){
    vector<V>* myVector;
    return *myVector;
}

template <typename K, typename V>
typename MMap<K,V>::Iterator MMap<K,V>::find(const K& key){
    return Iterator(mmap.find(MPair<K, V>(key)));
}

template <typename K, typename V>
int MMap<K,V>::count(const K& key){
    return 0;
}

template <typename K, typename V>
bool MMap<K,V>::is_valid(){
    return mmap.is_valid();
}

#endif