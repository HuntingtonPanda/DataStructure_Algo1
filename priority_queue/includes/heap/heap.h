#ifndef Co_HEAP_H
#define Co_HEAP_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include "assert.h"

using namespace std;

template <typename T>
class Heap
{
public:
    Heap():_how_many(0){}
    void insert(const T& insert_me);    //insert into the heap
    T remove();                         //remove and return top value 
    T top();                            //return the value at the top of heap
    bool is_empty() const;
    int size() const;
    int capacity() const;
    friend ostream& operator << (ostream& outs, const Heap<T>& print_me){
        print_me.print_tree(outs);
        return outs;
    }
    bool verify() const;                //true if tree is verified to be a heap
    T* heap_array();                    //returns a copy of underlying array: 
                                        //  don't forget to delete when done

private:
    static const int CAPACITY = 1000;
    T _heap[CAPACITY]; //static array
    int _how_many; //num used

    void print_tree(ostream& outs = cout) const;
    void print_tree(int root, int level = 0, ostream& outs = cout) const;

    bool verify(int root) const;

    bool is_root(int i) const {return i==0;}
    bool is_leaf(int i) const;
    int parent_index(int i) const;
    int left_child_index(int i)const {return 2*i + 1;}
    int right_child_index(int i) const {return 2*i + 2;}
    int big_child_index(int i) const;
    void swap_with_parent(int i);
};


template<typename T>
void Heap<T>::insert(const T& insert_me){
    assert(_how_many < CAPACITY);

    int current = _how_many;
    _heap[_how_many++] = insert_me;

    while (!is_root(current) && _heap[current] > _heap[parent_index(current)]) {
        swap_with_parent(current);
        current = parent_index(current);
    } 
}    //insert into the heap

template<typename T>
T Heap<T>::remove(){
    assert(!is_empty());

    T removed = _heap[0];
    _heap[0] = _heap[--_how_many];
    
    int current = 0;
    while (!is_leaf(current)) {
        int big_child = big_child_index(current);
        if (big_child < _how_many && _heap[current] < _heap[big_child]) {
            swap_with_parent(big_child);
            current = big_child;
        } else {
            break;
        }
    }
    return removed;
}                         //remove and return top value 

template<typename T>
T Heap<T>::top(){
    assert(!is_empty());
    return _heap[0];
}                            //return the value at the top of heap

template<typename T>
bool Heap<T>::is_empty() const{
    return _how_many == 0;
}

template<typename T>
int Heap<T>::size() const{
    return _how_many;
}

template<typename T>
int Heap<T>::capacity() const{
    return CAPACITY;
}

template<typename T>
bool Heap<T>::verify() const{
    return verify(0);
}                //true if tree is verified to be a heap

template<typename T>
T* Heap<T>::heap_array(){
    T* copy = new T[_how_many];
    for (int i = 0; i < _how_many; ++i) {
        copy[i] = _heap[i];
    }
    return copy; 
}
                    //returns a copy of underlying array: 
                                    //  don't forget to delete when done

// static const int CAPACITY = 1000;
// T _heap[CAPACITY]; //static array
// int _how_many; //num used

template<typename T>
void Heap<T>::print_tree(ostream& outs) const {
    print_tree(0, 0, outs);
}

template<typename T>
void Heap<T>::print_tree(int root, int level, ostream& outs) const {
    if (root >= _how_many)
        return;

    print_tree(right_child_index(root), level + 1, outs); 
    outs << setw(4 * level) << "[" << _heap[root] << "]\n";
    print_tree(left_child_index(root), level + 1, outs);  
}

template<typename T>
bool Heap<T>::verify(int root) const{
    if(is_leaf(root))
        return true;

    if(_heap[root] > _heap[big_child_index(root)])
        return (verify(left_child_index(root)) && verify(right_child_index(root)));
    else
        return false;
}

// template<typename T>
// bool Heap<T>::is_root(int i) const {
//     return i==0;
// }

template<typename T>
bool Heap<T>::is_leaf(int i) const{
    return left_child_index(i) >= _how_many;
}

template<typename T>
int Heap<T>::parent_index(int i) const{
    return (i - 1)/2;
}

// template<typename T>
// int Heap<T>::left_child_index(int i)const {return 2*i + 1;}

// template<typename T>
// int Heap<T>::right_child_index(int i) const {return 2*i + 2;}

template<typename T>
int Heap<T>::big_child_index(int i) const{
    int left = left_child_index(i);
    int right = right_child_index(i);
    if (right >= _how_many || _heap[left] > _heap[right]) {
        return left;
    }
    return right;
}

template<typename T>
void Heap<T>::swap_with_parent(int i){
    T temp = _heap[i];
    _heap[i] = _heap[parent_index(i)];
    _heap[parent_index(i)] = temp;
}


#endif