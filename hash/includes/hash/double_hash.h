#ifndef Co_DOUBLE_HASH_H
#define Co_DOUBLE_HASH_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include "assert.h"
#include "constants.h"

using namespace std;

template <typename T>
class DoubleHash
{
public:
    static const int CAPACITY = TABLE_SIZE;        //size of the table
    DoubleHash( );                      //CTOR

    bool insert(const T& entry);         //insert entry; false if overwriting.
    bool remove(int key);                //remove this key

    bool is_present(int key) const;      //is this key present?
    bool find(int key, T& result) const; //result <- record with this key
    int size( ) const { return used; }   //number of keys in this table
                                         //number of collisions in this table
    long collisions() const {return _collisions;}
    long capacity() const {return CAPACITY;}

    //print the entire talbe with keys, records, and hash values
    template<class TT>
    friend ostream& operator << (ostream& outs, const DoubleHash<TT>& h){
        for (int i = 0; i < CAPACITY; i++){
            outs << "[" << setfill('0') << setw(3) << i << "]";
            //for index with information
            if (h._data[i]._key >= 0){
                outs << "[" << h._data[i]._key << ":" << h._data[i]._item << "]";
                //for key that uses hash2
                if (i != h.hash(h._data[i]._key)){
                    outs << "(" << setfill('0') << setw(3) << h.hash(h._data[i]._key) << ")* "
                         << "hash2: " << h.hash2(h._data[i]._key);
                }
            }
            else if (h._data[i]._key == -2){
                outs << "- - - - - - ";
            }
            outs << endl;
        }
        return outs;
    }
private:

    static const int NEVER_USED = -1;        //this cell has never had a value
    static const int PREVIOUSLY_USED = -2;   //this cell has previously
                                             //   held a value that has since
                                             //been deleted.

    vector<T> _data;                          //table of records
    int used;                                //number of keys in the table
    long _collisions;

    int hash(int key) const;                //hash function
    int hash2(int key) const;               //hash2 function
    int next_index(int index, int key) const;       //wrap around index
    bool find_index(int key, int& index) const;     //find index of this key
    bool never_used(int index) const;      //is this cell NEVER_USED
    bool is_vacant(int index) const;       //is this cell available for insert
};




template <typename T>
DoubleHash<T>::DoubleHash( ){
    T blank;
    blank._key = NEVER_USED;
    for (int i = 0; i < CAPACITY; i++){
        _data.push_back(blank);
    }
    used = 0;
    _collisions = 0;
}                      //CTOR

template <typename T>
bool DoubleHash<T>::insert(const T& entry){
            assert(entry._key >= 0);
        int index; 
        bool flag;
        bool already_present = find_index(entry._key, index);

        if(!already_present){
            assert(size() < CAPACITY);
            index = hash(entry._key);
            while(!is_vacant(index)){
                index = next_index(index, entry._key);
            }
            ++used;
            flag = true;
        }
        else{
            ++_collisions;
            flag = false;
        }

        _data[index] = entry; 
        return flag;
}         //insert entry; false if overwriting.
template <typename T>
bool DoubleHash<T>::remove(int key){
        assert(key >= 0);
        int index;
        bool found = find_index(key, index);
        if(found){
            _data[index]._key = PREVIOUSLY_USED; 
            --used;
        }
        return found;
}                //remove this key

template <typename T>
bool DoubleHash<T>::is_present(int key) const{
        int temp;
    return find_index(key, temp);
}      //is this key present?
template <typename T>
bool DoubleHash<T>::find(int key, T& result) const{
    assert(key >=0);
    int index;
    bool temp = find_index(key, index);
    if (temp){
        result = _data[index];
    }
    return temp;
} //result <- record with this key


template <typename T>
int DoubleHash<T>::hash(int key) const{
    return (key % CAPACITY);
}                //hash function

template <typename T>
int DoubleHash<T>::hash2(int key) const{
    return 1 + (key % (CAPACITY - 2));
}               //hash2 function

template <typename T>
int DoubleHash<T>::next_index(int index, int key) const{
    return ((index + hash2(key)) % CAPACITY);
}       //wrap around index

template <typename T>
bool DoubleHash<T>::find_index(int key, int& index) const{
    int count = 0;
    index = hash(key);
    while((count < CAPACITY) && (!never_used(index)) && (_data[index]._key != key)){
        ++count;
        index = next_index(index, key);
    }
    return (_data[index]._key == key);
}     //find index of this key

template <typename T>
bool DoubleHash<T>::never_used(int index) const{
    return _data[index]._key == NEVER_USED;
}      //is this cell NEVER_USED
template <typename T>
bool DoubleHash<T>::is_vacant(int index) const{
    return _data[index]._key < 0;
}       //is this cell available for insert

#endif