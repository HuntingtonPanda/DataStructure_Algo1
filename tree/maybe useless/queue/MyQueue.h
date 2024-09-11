#ifndef MYQUEUE_H
#define MYQUEUE_H

#include "../linked_list_functions/linkedlistfunctionsTemplated.h"
#include <iostream>

template <typename T>
class Queue
{
public:
    class Iterator{
    public:
        friend class Queue;                               //give access to list to access _ptr
        Iterator(){_ptr = NULL;}                          //default ctor
        Iterator(node<T>* p): _ptr(p){}                   //Point Iterator to where
                                                          //  p is pointing to
        T operator *(){
            return _ptr->_item;
        }    //dereference operator
        bool is_null(){
            return _ptr == nullptr;
        }            //true if _ptr is NULL
        friend bool operator !=(const Iterator& left,
                                const Iterator& right)  //true if left != right
        {
            return left._ptr != right._ptr;
        }

        friend bool operator ==(const Iterator& left,
                                const Iterator& right)  //true if left == right
        {
            return left._ptr == right._ptr;
        }


        Iterator& operator++(){                         //member operator:++it
                                                        // or ++it = new_value
            if(_ptr)
                _ptr = _ptr->_next;
            return *this;
        }

        friend Iterator operator++(Iterator& it,
                                   int unused){         //friend operator: it++
            Iterator temp = it;
            it._ptr = (it._ptr)->_next;
            return temp;
        }

    private:
        node<T>* _ptr;                          //pointer being encapsulated
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

    Iterator begin() const;                                     //Iterator to the head node
    Iterator end() const;                                       //Iterator to NULL
    void print_pointers();
    void print_list_backwards();
    int size() const { return _size; }
    template<typename TT>
    friend ostream& operator << (ostream& outs, const Queue<TT>& printMe){
        outs << "Queue:Head->";
        for (node<TT>* walker = printMe._front; walker != nullptr; walker = walker->_next) {
            outs << *walker << " ";
        }
        outs << "|||";
        return outs;
    }
private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};





template <typename T>
Queue<T>::Queue():_front(nullptr), _rear(nullptr), _size(0){}

template <typename T>
Queue<T>::Queue(const Queue<T>& copyMe) : _front(nullptr), _rear(nullptr), _size(0) {
    _rear = _copy_list(_front, copyMe._front);
    _size = copyMe._size;
    if (_rear) {
        while (_rear->_next) {
            _rear = _rear->_next;
        }
    }
}


template <typename T>
Queue<T>::~Queue(){
    _clear_list(_front);
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& RHS){
    if (this != &RHS) { // Check for self-assignment
        _clear_list(_front);
        _front = nullptr;
        _rear = nullptr;
        _rear = _copy_list(_front, RHS._front);
        _size = RHS._size;
        // Update _rear to point to the last node
        if (_rear) {
            while (_rear->_next) {
                _rear = _rear->_next;
            }
        }
    }
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
    if(_front == nullptr)
        _rear = nullptr;
    _size--;
    return temp;
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::begin() const{
    typename Queue<T>::Iterator it(_front);
    return it;
}            //Iterator to the head node

template <typename T>
typename Queue<T>::Iterator Queue<T>::end() const{
    typename Queue<T>::Iterator it(nullptr);
    return it;
}              //Iterator to NULL

template <typename T>
void Queue<T>::print_pointers(){
    _print_list(_front);
}

template <typename T>
void Queue<T>::print_list_backwards()
{
    _print_list_backwards(_front);
    cout << endl;
}

#endif