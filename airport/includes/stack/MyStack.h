#ifndef MYSTACK_H
#define MYSTACK_H

#include "../linked_list_functions/linkedlistfunctionsTemplated.h"
#include <iostream>

template <typename ITEM_TYPE>
class Stack{
public:
    class Iterator{
    public:
        friend class Stack;                 //give access to list to access _ptr
        Iterator(){_ptr = NULL;}            //default ctor
        Iterator(node<ITEM_TYPE>* p): _ptr(p){}      //Point Iterator to where
                                            //  p is pointing to
        ITEM_TYPE operator *(){
            return _ptr->_item;
        }    //dereference operator
        bool is_null(){return _ptr == NULL;}            //true if _ptr is NULL
        friend bool operator !=(const Iterator& left,
                                const Iterator& right)  //true if left != right
        {return left._ptr != right._ptr;}

        friend bool operator ==(const Iterator& left,
                                const Iterator& right)  //true if left == right
        {return left._ptr == right._ptr;}


        Iterator& operator++(){                        //member operator:++it
                                                       // or ++it = new_value
            if(_ptr)
                _ptr = _ptr->_next;
            return *this;
        }

        friend Iterator operator++(Iterator& it,
                                   int unused){        //friend operator: it++
            assert(it._ptr!=NULL);
            Iterator temp = it;
            it._ptr = (it._ptr)->_next;
            return temp;
        }

    private:
        node<ITEM_TYPE>* _ptr;    //pointer being encapsulated
    };

    Stack();
    Stack(const Stack<ITEM_TYPE>& copyMe);
    ~Stack();
    Stack<ITEM_TYPE>& operator=(const Stack<ITEM_TYPE>& RHS);
    ITEM_TYPE top();
    bool empty();
    void push(ITEM_TYPE item);
    ITEM_TYPE pop();
    template<typename T>
    friend ostream& operator<<(ostream& outs, const Stack<T>& printMe){
        for(node<T>* walker = printMe._top; walker != nullptr; walker = walker->_next)
        {
            outs << walker->_item << "-> ";
        }
        outs << "|||";
        return outs;   
    }
    Iterator begin() const;                   //Iterator to the head node
    Iterator end() const;                     //Iterator to NULL
    int size() const { return _size; }

private:
    node<ITEM_TYPE>* _top;
    int _size;
};

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
    typename Stack<T>::Iterator it(_top);
    return it;

}              //Iterator to the head node

template <typename T>
typename Stack<T>::Iterator Stack<T>::end() const{
    typename Stack<T>::Iterator it(nullptr);
    return it;

}                //Iterator to NULL

#endif