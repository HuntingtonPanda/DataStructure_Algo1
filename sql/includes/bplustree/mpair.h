#ifndef Co_MPAIR_H
#define Co_MPAIR_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include "bplustree.h"
#include "../table/typedefs.h"

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
    MPair(const K& k=K()): key(k)
    {

    }

    MPair(const K& k, const V& v): key(k)
    {
        value_list.push_back(v);
    }

    MPair(const K& k, const vector<V>& vlist): key(k), value_list(vlist)
    {

    }
    //--------------------------------------------------------------------------------

    vector<V> getVals() const{
        return value_list;
    }

    //You'll need to overlood << for your vector:
    friend ostream& operator <<(ostream& outs, const MPair<K, V>& print_me)
    {
        outs << setw(10) << print_me.key << " :    " << print_me.value_list;
        return outs;
    }
    
    friend bool operator ==(const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return (lhs.key == rhs.key); 
    }

        friend bool operator !=(const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return !(lhs.key == rhs.key); 
    }

    friend bool operator < (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return (lhs.key < rhs.key);
    }

    friend bool operator <= (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return (lhs.key <= rhs.key);
    }

    friend bool operator > (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return (lhs.key > rhs.key);
    }

    friend bool operator >= (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return (lhs.key >= rhs.key);
    }

    friend MPair< K, V > operator + (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {   
        //cout << "\n--------------THIS FIRED-------------\n";
        MPair<K, V> mpair_result(lhs.key, lhs.value_list);
        
        // if(lhs.value_list.size() != rhs.value_list.size())
        // {
        //     cout << "POOPY";
        //     assert(false);
        // }

        for(int i = 0; i < rhs.value_list.size(); i++)
        {
            //mpair_result.value_list.push_back(lhs.value_list.at(i) + rhs.value_list.at(i));
            mpair_result.value_list.push_back(rhs.value_list.at(i));
        }

        return mpair_result;
    }
};

#endif
