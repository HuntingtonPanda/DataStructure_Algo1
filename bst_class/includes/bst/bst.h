#ifndef BST_H
#define BST_H

#include "assert.h"
#include "../bst_functions/bst_functions.h"
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;


template <typename T>
class BST{
public:
    BST();
    BST(const T *sorted_list, int size = -1);
    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    BST(const BST<T> &copy_me);
    BST<T>& operator=(const BST<T> &rhs);
    ~BST();
    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    void insert(const T &insert_me);

    void erase(const T &target);

    
    bool contains(const T &target)const;
    void clear_all();
    bool empty()const;
    friend ostream &operator<<(ostream &outs, const BST<T> &tree)
    {
        const bool debug = false;
        if (debug){
            cout<<"-------------------------------"<<endl;
            tree_print_debug(tree._root, 0, outs);
            cout<<". . . . . . . . . . . . . . . ."<<endl;
        }
        tree_print(tree._root, 0, outs);
        return outs;
    }
    BST<T> operator+=(const BST<T> &rhs);
    string pre_order();
    string in_order();
    string post_order();

private:
    tree_node<T>* _root;
};



template <typename T>
BST<T>::BST():_root(nullptr){

}

template <typename T>
BST<T>::BST(const T *sorted_list, int size):_root(nullptr){
    if (size != -1) {
        _root = tree_from_sorted_list(sorted_list, size);
    } else {
        _root = tree_from_sorted_list(sorted_list);
    }
}

template <typename T>
BST<T>::BST(const BST<T> &copy_me):_root(tree_copy(copy_me._root)){
    // Copy constructor
}

template <typename T>
BST<T>& BST<T>::operator=(const BST<T> &rhs){
    if (this != &rhs) {
        tree_clear(_root);
        _root = tree_copy(rhs._root);
    }
    return *this;
}

template <typename T>
BST<T>::~BST(){
    tree_clear(_root);
}

template <typename T>
void BST<T>::insert(const T &insert_me){
    tree_insert(_root, insert_me);
}

template <typename T>
void BST<T>::erase(const T &target){
    tree_erase(_root, target);
}

template <typename T>
bool BST<T>::contains(const T &target) const {
    return tree_search(_root, target) != nullptr;
}

template <typename T>
void BST<T>::clear_all(){
    tree_clear(_root);
}

template <typename T>
bool BST<T>::empty() const {
    return _root == nullptr;
}

template <typename T>
BST<T> BST<T>::operator+=(const BST<T> &rhs){
    tree_add(_root, rhs._root);
    return *this;
}

template <typename T>
string BST<T>::pre_order(){
    return pre_order_string(_root);
}

template <typename T>
string BST<T>::in_order(){
    return in_order_string(_root);
}

template <typename T>
string BST<T>::post_order(){
    return post_order_string(_root);
}


#endif