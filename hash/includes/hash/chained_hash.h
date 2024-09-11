#ifndef Co_CHAINED_HASH_H
#define Co_CHAINED_HASH_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include "assert.h"
#include "../avl/avl.h"
#include "double_hash.h"
#include "constants.h"

using namespace std;

template <typename T>
class ChainedHash
{
public:
    ChainedHash( ): total_records(0){}                              //CTOR

    bool insert(const T& entry);            //insert entry; false if overwriting.
    bool remove(int key);                   //remove this key

    bool find(int key, T& result) const;    //result <- record with key
    bool is_present(int key) const;         //is this key present in table?
    int size( ) const { return total_records; }  //number of keys in the table
    long capacity(){return TABLE_SIZE;}


    //print entire table with keys, etc.
    template<class TT>
    friend ostream& operator << (ostream& outs, const ChainedHash<TT>& h){
        for (int i = 0; i < TABLE_SIZE; i++){
            //print index
            outs << "[" << setfill('0') << setw(3) << i << "]";
            //print tree
            outs << "tree: " << h._data[i] << endl;
            outs << endl;
        }
        return outs;
    }

private:
    AVL<T> _data[TABLE_SIZE];               //table chains
    int total_records;                      //number of keys in the table

    int hash(int key) const;                //hash function
};

template <typename T>
bool ChainedHash<T>::insert(const T& entry){
    assert(entry._key >= 0);
    int index = hash(entry._key);

    bool already_present = is_present(entry._key);

    if(!already_present){
        total_records++;
        _data[index].insert(entry);
        return true;
    }
    else
        return false;
}            //insert entry; false if overwriting.

template <typename T>
bool ChainedHash<T>::remove(int key){
    assert(key >= 0);
    int index = hash(key);
    if (_data[index].erase(key))
    {
        total_records--;
        return true;
    }
    else
        return false;
}                   //remove this key

template <typename T>
bool ChainedHash<T>::find(int key, T& result) const{
    tree_node<T>* temp; 
    int index = hash(key);
    bool findResult = _data[index].search(key, temp);
    if(temp)
        result = temp -> _item;
    return findResult;
}    //result <- record with key

template <typename T>
bool ChainedHash<T>::is_present(int key) const{
    T result;
    int index = hash(key);
    return _data[index].contains(key, result);
}         //is this key present in table?

template <typename T>
int ChainedHash<T>::hash(int key) const{
    return (key % TABLE_SIZE);
}                //hash function
#endif