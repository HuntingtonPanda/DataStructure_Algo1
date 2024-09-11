#ifndef Co_MULTIMAP_H
#define Co_MULTIMAP_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <vector>

#include "bplustree.h"
#include "mpair.h"
#include "../stl_utils/vector_utilities.h"

using namespace std;

template <typename K, typename V>
class MMap
{
public:
    typedef BPlusTree<MPair<K, V> > map_base;
    class Iterator{
    public:
        friend class MMap;
        Iterator(typename map_base::Iterator it = nullptr) : _it(it)
        {

        }

        Iterator operator ++(int unused)
        {
            Iterator temp = _it;
            _it++;
            return temp;
        }

        Iterator operator ++()
        {
            _it++;
            return _it;
        }

        MPair<K, V> operator *()
        {
            return *_it;
        }

        friend bool operator ==(const Iterator& lhs, const Iterator& rhs)
        {
            return (lhs._it == rhs._it);
        }

        friend bool operator !=(const Iterator& lhs, const Iterator& rhs)
        {
            return !(lhs._it == rhs._it);
        }

    private:
        typename map_base::Iterator _it;
    };

    MMap();

//  Iterators
    Iterator begin();
    Iterator end();

//  Capacity
    int size() const;
    bool empty() const;

//  Element Access
    const vector<V>& operator[](const K& key) const;
    vector<V>& operator[](const K& key);

//  Modifiers
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();

//  Operations:
    bool contains(const K& key) const;
    vector<V> &get(const K& key);

    Iterator find(const K& key);

    // I have not written these yet, but we will need them:
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound
    //    equal_range:

    int count(const K& key);
    Iterator lower_bound(const K& key);
    Iterator upper_bound(const K& key);
    Iterator equal_range(const K& key);

    bool is_valid();

    vector<V>& at(const K num); //I MADE THIS CONSTANT

    friend ostream& operator<<(ostream& outs, const MMap<K, V>& print_me)
    {
        outs<<print_me.mmap<<endl;
        return outs;
    }

private:
    BPlusTree<MPair<K, V> > mmap;
};

template <typename K, typename V>
MMap<K, V>::MMap()
{
    mmap.set_dups_ok();
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::begin()
{
    //typename MMap<K,V>::Iterator it;
    return Iterator(mmap.begin());
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::end()
{
    //typename MMap<K,V>::Iterator it;
    return Iterator(mmap.end());;
}

template <typename K, typename V>
int MMap<K, V>::size() const
{
    return mmap.size();
}

template <typename K, typename V>
bool MMap<K, V>::empty() const
{
    return mmap.empty();
} // HERE

template <typename K, typename V>
const vector<V> &MMap<K, V>::operator[](const K &key) const
{
    return mmap.get(MPair<K, V>(key)).value_list;
}

template <typename K, typename V>
vector<V> &MMap<K, V>::operator[](const K &key)
{
    return mmap.get(MPair<K,V>(key)).value_list;
}

template <typename K, typename V>
void MMap<K, V>::insert(const K &k, const V &v)
{
    mmap.insert(MPair<K, V>(k, v));
}

template <typename K, typename V>
void MMap<K, V>::erase(const K &key)
{
    mmap.remove(MPair<K,V>(key));
}

template <typename K, typename V>
void MMap<K, V>::clear()
{
    mmap.clear_tree();
}

template<typename K, typename V>
bool MMap<K, V>::contains(const K & key) const
{
    return (mmap.contains(key));
}

template <typename K, typename V>
vector<V> &MMap<K, V>::get(const K &key)
{
    //vector<V>* vec;
    return mmap.get(MPair<K, V>(key)).value_list;
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::find(const K &key)
{
    //typename MMap<K,V>::Iterator it;
    return Iterator(mmap.find(key));
}

template <typename K, typename V>
int MMap<K, V>::count(const K &key)
{
    return mmap.size();
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::lower_bound(const K& key)
{
    for(Iterator it = begin(); it != end(); it++)
    {
        if(key <= (*it).key) 
        {
            return it;
        }
    }
    return end();   
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::upper_bound(const K& key)
{
        for(Iterator it = begin(); it != end(); it++)
        {
            if(key < (*it).key) 
            {
                return it;
            }
        }
        return end();  
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::equal_range(const K& key)
{
    typename MMap<K,V>::Iterator it;
    return it;
}

template <typename K, typename V>
bool MMap<K, V>::is_valid()
{
    //return false;
    return mmap.is_valid();
}

template <typename K, typename V>
vector<V>& MMap<K, V>::at(const K num)
{
    return mmap.get(MPair<K,V>(num)).value_list;
}
//I MADE THIS CONSTANT
#endif
