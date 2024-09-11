#ifndef Co_VECTOR_UTILITIES_H
#define Co_VECTOR_UTILITIES_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <vector>

using namespace std;

template <typename T>
ostream &operator<<(ostream &outs, const vector<T> &list);

template <typename T>
vector<T> &operator+=(vector<T> &list, const T &addme);

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list)
{
    for(auto it = list.begin(); it != list.end(); it++)
    {
        outs << *it << " ";
    }
    return outs;
} 

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme)
{
    list.push_back(addme);
    return list;
} 

#endif