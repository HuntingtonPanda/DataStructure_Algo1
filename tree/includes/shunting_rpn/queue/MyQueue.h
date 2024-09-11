#ifndef Co_MYQUEUE_H
#define Co_MYQUEUE_H
#include <iostream>
#include <iomanip>
#include "assert.h"

#include "../node/node.h"
#include "../linked_list_functions/linked_list_functions.h"

using namespace std;

template <typename T>
class Queue
{
public:
    class Iterator{
    public:
        friend class Queue;          //give access to list to access _ptr
        Iterator(){_ptr = nullptr;}                    //default ctor
        Iterator(node<T>* p) : _ptr(p) {}
                                                    //Point Iterator to where p
                                                    //  is pointing to
        T &operator*(){
            return _ptr->_item;
        }                             //dereference operator

        T *operator->(){ 
            return &(_ptr->_item);
        }                             //member access operator
        bool is_null(){ return _ptr == nullptr; }     //true if _ptr is NULL
        friend bool operator!=(const Iterator &left,
                               const Iterator &right)
        { return left._ptr != right._ptr; } //true if left != right

        friend bool operator==(const Iterator &left,
                               const Iterator &right)
        { return left._ptr != right._ptr; } //true if left == right

        Iterator &operator++(){ 
            if(_ptr)
                _ptr = _ptr->_next;
            return *this;
        }                            //member operator:
                                                        //  ++it; or
                                                        //  ++it = new_value

        friend Iterator operator++(Iterator &it,
                                   int unused){  
            Iterator temp = it;
            it._ptr = (it._ptr)->_next;
            return temp;
                                   
        }         //friend operator: it++          //friend operator: it++                    //  p is pointing to
 
    private:
        node<T>* _ptr;               //pointer being encapsulated
    };

    Queue();

    Queue(const Queue<T>& copyMe);
    ~Queue();
    Queue& operator=(const Queue<T>& RHS);

    bool empty();
    T front();
    T back();

    void push(T item);
    T pop();

    Iterator begin() const;            //Iterator to the head node
    Iterator end() const;              //Iterator to NULL
    void print_pointers();
    int size() const { return _size; }
    template<typename TT>
    friend ostream& operator << (ostream& outs, const Queue<TT>& printMe);
private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};

template<typename TT>
ostream& operator << (ostream& outs, const Queue<TT>& printMe){
    // for(node<TT>* walker = printMe._front; walker != nullptr; walker = walker->_next)
    // {
    //     outs << walker->_item << "-> ";
    // }
    // outs << "|||";
    _print_list(printMe._front);
    return outs;
}

template <typename T>
Queue<T>::Queue():_front(nullptr), _rear(nullptr), _size(0){}

template <typename T>
Queue<T>::Queue(const Queue<T>& copyMe):_front(nullptr), _rear(nullptr), _size(0)
{
    _rear = _copy_list(_front, copyMe._front);
    _size = copyMe._size;
}


template <typename T>
Queue<T>::~Queue(){
    _clear_list(_front);
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& RHS){
    // _clear_list(_front);
    // _front = nullptr;
    // _rear = nullptr;
    _rear = _copy_list(_front, RHS._front);
    _size = RHS._size;
    return *this;
}

template <typename T>
bool Queue<T>::empty(){
    return (!_front);

}

template <typename T>
T Queue<T>::front(){
    return _front->_item;

}

template <typename T>
T Queue<T>::back(){
    return _rear->_item;

}

template <typename T>
void Queue<T>::push(T item){
    _rear = _insert_after(_front, _rear, item);
    _size++;

}

template <typename T>
T Queue<T>::pop(){
    T temp  = _delete_node(_front, _front);
    _size--;
    return temp;
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::begin() const{
    return _front;
}            //Iterator to the head node

template <typename T>
typename Queue<T>::Iterator Queue<T>::end() const{
    return nullptr;
}              //Iterator to NULL

template <typename T>
void Queue<T>::print_pointers(){
    _print_list(_front);
}

#endif