#ifndef Co_PQUEUE_H
#define Co_PQUEUE_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include "assert.h"
#include "heap.h"

using namespace std;

template <typename T>
struct info{
    static unsigned long time;
    T item;
    int priority;
    long timeStamp;

    info():item(T()), priority(0), timeStamp(time++){}
    info(T i, int p):item(i), priority(p), timeStamp(time++){}

    friend ostream& operator <<(ostream& outs, const info<T>& print_me){
        const bool tldr = true; //what is this

        outs << "Item: " << print_me.item << "\nPriority: " << print_me.priority << "\nTimestamp: " << print_me.timeStamp;
        return outs;
    }

    friend bool operator <(const info<T>& lhs, const info<T>& rhs){
        if (lhs.priority == rhs.priority)
            return lhs.timeStamp > rhs.timeStamp;

        return lhs.priority < rhs.priority;
    }
    friend bool operator >(const info<T>& lhs, const info<T>& rhs){
        if (lhs.priority == rhs.priority) 
            return lhs.timeStamp < rhs.timeStamp; 
        
        return lhs.priority > rhs.priority;
    }

};

template<typename T>
unsigned long info<T>::time = 0;

template <typename T>
class PQueue
{
public:
    PQueue(){}

    bool push(const T& value, int p);
    T pop();
    info<T> Pop_debug();
    bool is_empty() const {return _heap.is_empty();}
    int size() const {return _heap.size();}
    void print_tree() const;
    friend ostream& operator <<(ostream& outs, const PQueue<T>& print_me){
        outs << print_me._heap;
        return outs;
    }
    bool verify() const;
private:
    Heap<info<T>> _heap;

};

template <typename T>
bool PQueue<T>::push(const T& value, int p){
    if(_heap.size() + 1 >= _heap.capacity())
        return false;
    
    info<T> temp(value, p);

    _heap.insert(temp);

    return true;
}

template <typename T>
T PQueue<T>::pop(){
    return _heap.remove().item;
}

template <typename T>
info<T> PQueue<T>::Pop_debug(){
    return _heap.remove();
}

template <typename T>
void PQueue<T>::print_tree() const{
    _heap.print_tree();
}

template <typename T>
bool PQueue<T>::verify() const{
    return _heap.verify();
}

#endif