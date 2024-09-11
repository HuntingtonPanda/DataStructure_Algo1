#ifndef Co_OPEN_HASH_H
#define Co_OPEN_HASH_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include "assert.h"

using namespace std;


template <class RecordType> 
class table
{
public:
// MEMBER CONSTANT -- See Appendix E if this fails to compile. static const size_t CAPACITY = 811;
// CTOR
    table(): used(0)
    {
        for(size_t i = 0; i < CAPACITY; i++){
            data[i].key = NEVER_USED;
        }
    } 

    void insert(const RecordType& entry)
    {
        bool already_present;
        size_t index; 
         
        assert(entry.key >= 0);
        find_index(entry.key, already_present, index);

        if(!already_present)
        {
            assert(size() < CAPACITY);
            index = hash(entry.key);
            while(!is_vacant(index)){
                index = next_index(index);
            }
            ++used;
        }

        data[index] = entry; //overwrite
    }

    void remove(int key)
    {
        bool found;
        size_t index;

        assert(key >= 0);
        find_index(key, found, index);
        
        if(found)
        {
            //if key found, remove this record, --used
            data[index].key = PREVIOUSLY_USED; //flag no longer sue
            --used;
        }
    }

    //return true if the table contains a record with the specified key
    bool is_present(int key) const{ 
        size_t index = hash(key);

        vector<HashRecord>::const_iterator it;
        for(it = data[index].begin(); it != data[index].end(); it++){
            if(hashkey(*it) == key)
                return true;
        }
        return false; 
    }

    void find(int key, bool& found, HashRecord& result) const
    {
        size_t = index;
        assert(key >=0);
        find_index(key, found, index);
        return found;
    } 

    //return total number of records
    size_t size( ) const 
    { 
        return used; 
    }

    int hashkey(const string& s){
        int result = 0;
        for(int i = 0; i < s.length(); i++)
            result = result + static_cast<int>(s[i]);
        return (result % table_size);
    }
    
private:

    static const int NEVER_USED = -1;
    static const int PREVIOUSLY_USED = -2;

    RecordType data[CAPACITY];
    size_t used;

    size_t hash(int key) const{ return (key % CAPACITY); }

    size_t next_index(size_t index) const{ return ((index + 1) % CAPACITY); }

    void find_index(int key, bool& found, size_t& index) const
    {
        size_t count = 0;
        index = hash(key);
        while((count < CAPACITY) && (!never_used(index)) && (data[index].key != key)){
            ++count;
            index = next_index(index);
        }
        found = (data[index].key == key);
    }

    bool never_used(size_t index) const{ return (data[index].key == NEVER_USED); }

    bool is_vacant(size_t index) const{ return (data[index].key < 0); }
}; 

#endif