#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "../node/node.h"
#include "assert.h"
#include <iostream>

using namespace std;

//Linked List General Functions:
template <typename T>
void _print_list(node<T>* head);

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head);

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head,
                            T key);


template <typename T>
node<T>* _insert_head(node<T> *&head,
                            T insert_this);

//insert after ptr: insert head if marker null
template <typename T>
node<T>* _insert_after(node<T>*& head,
                                node<T> *after_this,
                                T insert_this);

//insert before ptr: insert head if marker null
template <typename T>
node<T>* _insert_before(node<T>*& head,
                                node<T>* before_this,
                                T insert_this);

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* prev_to_this);

//delete, return item
template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this);

//duplicate the list...
template <typename T>
node<T>* _copy_list(node<T>* head);

//duplicate the list, return pointer to last node in dest... 
//     use this function in your queue big three 
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src);



//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head);

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos);










//Linked List General Functions:
template <typename T>
void _print_list(node<T>* head){
    node<T>* current = head;
    cout << "Head->";
    while(current != nullptr){
        cout << *current;
        current = current->_next;
    }
    cout << "|||\n";
}

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head){
    node<T>* current = head;
    cout << "Head->";
    if (current != nullptr){
        _print_list_backwards(current->_next);
        cout << *current;
    } else {
        cout << "|||\n";
    }
}

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head, T key){
    node<T>* current = head;
    while(current != nullptr){
        if(current->_item == key)
            return current;
        current = current->_next;
    }
    return nullptr;
}


template <typename T>
node<T>* _insert_head(node<T> *&head, T insert_this){
    if (head == nullptr) {
        head = new node<T>(insert_this);
        return head;
    }

    node<T>* current = new node<T>(insert_this, head);
    head->_prev = current;
    head = current;
    return head;
}

//insert after ptr: insert head if marker null
template <typename T>
node<T>* _insert_after(node<T>*& head, node<T> *after_this, T insert_this){
    if (head == nullptr)
        return _insert_head(head, insert_this);
    else {
        //cout << "\n<YES>\n"
        node<T>* current = new node<T>(insert_this, after_this->_next, after_this);
        if (after_this->_next != nullptr) {
            after_this->_next->_prev = current;
        }
        after_this->_next = current;
        return current;
    }
}

//insert before ptr: insert head if marker null
template <typename T>
node<T>* _insert_before(node<T>*& head, node<T>* before_this, T insert_this){
    if (before_this == head || head == nullptr)
        return _insert_head(head, insert_this);
    node<T>* current = new node<T>(insert_this, before_this, before_this->_prev);
    before_this->_prev->_next = current;
    before_this->_prev = current;

    return before_this;
}

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* prev_to_this){
    return prev_to_this->_prev;
}

//delete, return item
template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this){
    assert(head);

    if (head == delete_this){
        head = head -> _next;
        if (head != nullptr)
            head->_prev = nullptr;
    }
    else {
        node<T>* Previous = _previous_node(delete_this);
        delete_this->_prev->_next = delete_this->_next;
        if (delete_this->_next != nullptr)
            delete_this->_next->_prev = Previous;
    }

    T hold = delete_this->_item;

    delete delete_this;

    return hold;
}

//duplicate the list...
template <typename T>
node<T>* _copy_list(node<T>* head){
    node<T>* dest = nullptr;
    node<T>* last = _copy_list(dest, head);

    return dest;
}

//duplicate the list, return pointer to last node in dest... 
//     use this function in your queue big three 
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src){
    _clear_list(dest);

    node<T>* current = dest;
    node<T>* srcWalker = src;

    while(srcWalker){
        current = _insert_after(dest, current, srcWalker->_item);
        srcWalker = srcWalker->_next;
    }

    return current;
}



//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head){
    while (head) 
        _delete_node(head, head);
}

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos){
    assert(head);

    node<T>* Walker = head;
    
    for(int i = 0; i < pos; i++){
        assert(Walker->_next);
        Walker = Walker->_next;
    }

    return Walker->_item;

}

#endif