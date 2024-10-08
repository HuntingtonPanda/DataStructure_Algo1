#ifndef Co_PAIR_H
#define Co_PAIR_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include "bplustree.h"

using namespace std;

template <typename K, typename V>
struct Pair{
    K key;
    V value;

    Pair(const K& k=K(), const V& v=V()): key(k), value(v)
    {

    }
    
    friend ostream& operator <<(ostream& outs, const Pair<K, V>& print_me)
    {
        outs << "(" << print_me.key << ": " << print_me.value << ")" <<endl;
        return outs;
    }

    friend bool operator ==(const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return lhs.key == rhs.key;
    }

    friend bool operator !=(const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return !(lhs.key == rhs.key);
    }

    friend bool operator < (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return lhs.key < rhs.key;
    }

    friend bool operator > (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return lhs.key > rhs.key;
    }

    friend bool operator <= (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return lhs.key <= rhs.key;
    }

    friend bool operator >= (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    { 
        return (lhs.key >= rhs.key); 
    }

    friend Pair<K, V> operator + (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return Pair<K, V>();
    }
};

#endif
