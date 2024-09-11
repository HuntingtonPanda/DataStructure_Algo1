#ifndef AVL_H
#define AVL_H

#include "assert.h"
#include "avl_functions.h"
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

template <typename T>
class AVL{
public:
    AVL();
    AVL(const T *list, int size = -1);
    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    AVL(const AVL<T> &copy_me);
    AVL<T> &operator=(const AVL<T> &rhs);
    ~AVL();
    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    bool insert(const T &insert_me);
    bool erase(const T &target);

    bool contains(const T &target) const;

    void clear();
    void clear_all();
    bool empty()const
    ;
    string pre_order() const;
    string in_order() const;
    string post_order() const;

    bool search(const T &target, tree_node<T> *&found_ptr) const;

    void output_inorder(ostream &outs);

    friend ostream& operator <<(ostream& outs, const AVL<T>& tree){
        tree_print(tree._root, 0, outs);
        return outs;
    }
    AVL<T> &operator+=(const AVL<T> &rhs);

private:

    tree_node<T>* _root;
};


template <typename T>
AVL<T>::AVL():_root(nullptr){

}

template <typename T>
AVL<T>::AVL(const T *sorted_list, int size):_root(nullptr){
    if (size != -1) {
        _root = tree_from_sorted_list(sorted_list, size);
    } else {
        _root = tree_from_sorted_list(sorted_list);
    }
}

template <typename T>
AVL<T>::AVL(const AVL<T> &copy_me):_root(tree_copy(copy_me._root)){
    // Copy constructor
}

template <typename T>
AVL<T>& AVL<T>::operator=(const AVL<T> &rhs){
    if (this != &rhs) {
        tree_clear(_root);
        _root = tree_copy(rhs._root);
    }
    return *this;
}

template <typename T>
AVL<T>::~AVL(){
    tree_clear(_root);
}

template <typename T>
bool AVL<T>::insert(const T &insert_me){
    return tree_insert(_root, insert_me);
}

template <typename T>
bool AVL<T>::erase(const T &target){
    return tree_erase(_root, target);
}

template <typename T>
bool AVL<T>::contains(const T &target) const {
    return tree_search(_root, target) != nullptr;
}

template <typename T>
void AVL<T>::clear_all(){
    tree_clear(_root);
}

template <typename T>
bool AVL<T>::empty() const {
    return _root == nullptr;
}

template <typename T>
string AVL<T>::pre_order() const {
    return pre_order_string(_root);
}

template <typename T>
string AVL<T>::in_order() const {
    return in_order_string(_root);
}

template <typename T>
string AVL<T>::post_order() const {
    return post_order_string(_root);
}

template <typename T>
AVL<T>& AVL<T>::operator+=(const AVL<T> &rhs){
    tree_add(_root, rhs._root);
    return *this; // Dereference 'this' pointer
}


#endif