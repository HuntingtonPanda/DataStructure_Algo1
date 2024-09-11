#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H

#include <iostream>
#include <iomanip>
#include "assert.h"

#include "../node/node.h"


//Linked List General Functions:
template <typename ITEM_TYPE>
void _print_list(node<ITEM_TYPE>* head);

// //recursive fun! :)
// template <typename ITEM_TYPE>
// void _print_list_backwards(node<ITEM_TYPE> *head);

//return ptr to key or NULL
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _search_list(node<ITEM_TYPE>* head,
                            ITEM_TYPE key);


template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_head(node<ITEM_TYPE> *&head,
                            ITEM_TYPE insert_this);

//insert after ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_after(node<ITEM_TYPE>*& head,
                                node<ITEM_TYPE> *after_this,
                                ITEM_TYPE insert_this);

//insert before ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_before(node<ITEM_TYPE>*& head,
                                node<ITEM_TYPE>* before_this,
                                ITEM_TYPE insert_this);

//ptr to previous node
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _previous_node(node<ITEM_TYPE>* head,
                                node<ITEM_TYPE>* prev_to_this);

//delete, return item
template <typename ITEM_TYPE>
ITEM_TYPE _delete_node(node<ITEM_TYPE>*&head,
                        node<ITEM_TYPE>* delete_this);

//duplicate the list...
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _copy_list(node<ITEM_TYPE>* head);

//duplicate list and return the last node of the copy
template <typename T>
node<T> *_copy_list(node<T>* &dest, node<T> *src);


//delete all the nodes
template <typename ITEM_TYPE>
void _clear_list(node<ITEM_TYPE>*& head);

//_item at this position
template <typename ITEM_TYPE>
ITEM_TYPE& _at(node<ITEM_TYPE>* head, int pos);

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//      Sorted List Routines. order: 0: ascending, order: other: descending
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted(node<ITEM_TYPE>* &head,       //insert
                                ITEM_TYPE item,
                                bool ascending=true);

//insert or add if a dup
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted_and_add(node<ITEM_TYPE>* &head,
                                        ITEM_TYPE item,
                                        bool ascending=true);
//node after which this item goes order: 0 ascending
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _where_this_goes(node<ITEM_TYPE>* head,
                                ITEM_TYPE item,
                                bool ascending=true);
//Last Node in the list
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _last_node(node<ITEM_TYPE>* head);            //never use this function






/* /////////////////////////////////////////////////
DEFINITIONS DEFINITIONS DEFINITIONS DEFINITIONS
DEFINITIONS DEFINITIONS DEFINITIONS DEFINITIONS
DEFINITIONS DEFINITIONS DEFINITIONS DEFINITIONS
DEFINITIONS DEFINITIONS DEFINITIONS DEFINITIONS 
////////////////////////////////////////////////////////
*/






//Linked List General Functions:
template <typename ITEM_TYPE>
void _print_list(node<ITEM_TYPE>* head){
    node<ITEM_TYPE>* walker = head;  
    while(walker != nullptr){
        cout << *walker << "-> ";
        walker = walker -> _next;
    }
    cout << "| | |\n";
}

// //recursive fun! :)
// template <typename ITEM_TYPE>
// void _print_list_backwards(node<ITEM_TYPE> *head){

// }

//return ptr to key or NULL
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _search_list(node<ITEM_TYPE>* head,
                            ITEM_TYPE key){
    node<ITEM_TYPE>* walker = head;  
    while(walker != nullptr){
        if(walker->_item == key)
            return walker;
        walker = walker -> _next;    
    }
    return nullptr;
}


template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_head(node<ITEM_TYPE>* &head,
                            ITEM_TYPE insert_this){
node<ITEM_TYPE>* TEMP = new node<ITEM_TYPE>(insert_this, head);
head = TEMP;

return head;
}

//insert after ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_after(node<ITEM_TYPE>*& head,
                                node<ITEM_TYPE> *after_this,
                                ITEM_TYPE insert_this){
if(!head){
    return _insert_head(head, insert_this);
}

assert(after_this);

node<ITEM_TYPE>* TEMP = new node<ITEM_TYPE>(insert_this, after_this->_next);

after_this->_next = TEMP; 

return TEMP; 
}

//insert before ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_before(node<ITEM_TYPE>*& head,
                                node<ITEM_TYPE>* before_this,
                                ITEM_TYPE insert_this){
if(!head||head == before_this){
    return _insert_head(head, insert_this);
}

node<ITEM_TYPE>* Previous = _previous_node(head, before_this);

node<ITEM_TYPE>* TEMP = new node<ITEM_TYPE>(insert_this, before_this);

Previous->_next = TEMP;

return TEMP;
}

//ptr to previous node
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _previous_node(node<ITEM_TYPE>* head,
                                node<ITEM_TYPE>* prev_to_this){
assert(head);
assert(prev_to_this);

if(head == prev_to_this) {
    return nullptr;
}

node<ITEM_TYPE>* Walker = head;

while(Walker->_next != prev_to_this){
    Walker = Walker->_next;
}

return Walker;
}

//delete, return item
template <typename ITEM_TYPE>
ITEM_TYPE _delete_node(node<ITEM_TYPE>*&head,
                        node<ITEM_TYPE>* delete_this){
assert(head);

/*
node<ITEM_TYPE>* Previous = _previous_node(head, delete_this);

if (Previous) 
    Previous->_next = delete_this->_next;
else 
    head = delete_this->_next;
*/

if (head == delete_this)
    head = head -> _next;
else {
    node<ITEM_TYPE>* Previous = _previous_node(head, delete_this);
    Previous->_next = delete_this->_next;
}


ITEM_TYPE hold = delete_this->_item;

delete delete_this;

return hold;
}

// //duplicate the list...
// template <typename ITEM_TYPE>
// node<ITEM_TYPE>* _copy_list(node<ITEM_TYPE>* head){


// node<ITEM_TYPE>* srcWalker = head;

// node<ITEM_TYPE>* nHead = nullptr;
// node<ITEM_TYPE>* nHeadWalker = nullptr;

// while(srcWalker){
//     nHeadWalker = _insert_after(nHead, nHeadWalker, srcWalker->_item);
//     srcWalker = srcWalker->_next;
// }

// return nHead;
// }


// //duplicate list and return the last node of the copy
// template <typename T>
// node<T> *_copy_list(node<T>* &dest, node<T> *src){

//     node<T>* current = dest;

//     node<T>* srcWalker = src;

//     while(srcWalker){
//         current = _insert_after(dest, current, srcWalker->_item);
//         srcWalker = srcWalker->_next;
//     }


//     return current;
// }

//duplicate the list...
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _copy_list(node<ITEM_TYPE>* head){

node<ITEM_TYPE>* nHead = nullptr;

node<ITEM_TYPE>* last;

last = _copy_list(nHead, head);

return nHead;
}


//duplicate list and return the last node of the copy
template <typename T>
node<T> *_copy_list(node<T>* &dest, node<T> *src){

    _clear_list(dest);

    dest = nullptr;

    node<T>* current = dest;

    node<T>* srcWalker = src;

    while(srcWalker){
        current = _insert_after(dest, current, srcWalker->_item);
        srcWalker = srcWalker->_next;
    }


    return current;
}


//delete all the nodes
template <typename ITEM_TYPE>
void _clear_list(node<ITEM_TYPE>*& head){
    while(head){
        //cout << "cry ";
        _delete_node(head, head);
    }
    //cout << "Not_Sad";

}

//_item at this position
template <typename ITEM_TYPE>
ITEM_TYPE& _at(node<ITEM_TYPE>* head, int pos){

    assert(head);
    node<ITEM_TYPE>* Walker = head;
    
    for(int i = 0; i < pos; i++){
        assert(Walker->_next);
        Walker = Walker->_next;
    }

    return Walker->_item;
}

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//      Sorted List Routines. order: 0: ascending, order: other: descending
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted(node<ITEM_TYPE>* &head,       //insert
                                ITEM_TYPE item,
                                bool ascending){

return nullptr;
}

//insert or add if a dup
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted_and_add(node<ITEM_TYPE>* &head,
                                        ITEM_TYPE item,
                                        bool ascending){

return nullptr;
}
//node after which this item goes order: 0 ascending
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _where_this_goes(node<ITEM_TYPE>* head,
                                ITEM_TYPE item,
                                bool ascending){

return nullptr;
}
//Last Node in the list
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _last_node(node<ITEM_TYPE>* head){


return nullptr;
}            //never use this function.

#endif