#ifndef MYSTACK_H
#define MYSTACK_H
#include <iostream>
#include <iomanip>
#include "assert.h"

#include "../node/node.h"
#include "../linked_list_functions/linked_list_functions.h"

using namespace std;

template <typename T>
class Stack{
public:
    class Iterator{
    public:
        friend class Stack;                     //give access to list to access _ptr
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
                                   
        }         //friend operator: it++          //friend operator: it++

    private:
        node<T>* _ptr;                          //pointer being encapsulated
    };

    Stack();
    Stack(const Stack<T>& copyMe);
    ~Stack();
    Stack<T>& operator=(const Stack<T>& RHS);
    T top();
    bool empty();
    void push(T item);
    T pop();
    template<typename TT>
    friend ostream& operator<<(ostream& outs, 
                                        const Stack<TT>& printMe);

    Iterator begin() const;              //Iterator to the head node
    Iterator end() const;                //Iterator to NULL
    int size() const { return _size; }

private:
    node<T>* _top;
    int _size;
};

template<typename TT>
ostream& operator<<(ostream& outs, 
                                    const Stack<TT>& printMe){
    for(node<TT>* walker = printMe._top; walker != nullptr; walker = walker->_next)
    {
        outs << walker->_item << "-> ";
    }
    outs << "|||";
    return outs;                                    
}

template <typename T>
Stack<T>::Stack(): _top(nullptr), _size(0){
    
}

template <typename T>
Stack<T>::Stack(const Stack<T>& copyMe){
    _size = copyMe._size;
    _top = _copy_list(copyMe._top);

}

template <typename T>
Stack<T>::~Stack(){
    _clear_list(_top);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& RHS){
    _size = RHS._size;
    _copy_list(_top, RHS._top);
    return *this;
}

template <typename T>
T Stack<T>::top(){
    return _top->_item;

}

template <typename T>
bool Stack<T>::empty(){
    return(!_top);

}

template <typename T>
void Stack<T>::push(T item){
    _insert_head(_top, item);
    _size++;
}

template <typename T>
T Stack<T>::pop(){
    _size--;
    T temp = _delete_node(_top, _top);
    return temp;
    

}

template <typename T>
typename Stack<T>::Iterator Stack<T>::begin() const{
    return _top;

}              //Iterator to the head node

template <typename T>
typename Stack<T>::Iterator Stack<T>::end() const{
    return nullptr;

}                //Iterator to NULL


#endif