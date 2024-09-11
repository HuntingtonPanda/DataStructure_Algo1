#ifndef BST_FUNCTION_H
#define BST_FUNCTION_H


#include "assert.h"

#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>

using namespace std;

template <typename T>
struct tree_node{
    T _item;
    tree_node<T>* _left;
    tree_node<T>* _right;
    int _height;
    // In tree_node struct

    int height() {
        int left_h = (_left != nullptr) ? _left->height() : -1;
        int right_h = (_right != nullptr) ? _right->height() : -1;

        return 1 + max(left_h, right_h);
    }

    int balance_factor() {
        int left_h = (_left != nullptr) ? _left->height() : -1;
        int right_h = (_right != nullptr) ? _right->height() : -1;

        return left_h - right_h;
    }


    // int height() {
    //     int left_h = -1;
    //     int right_h = -1;

    //     if (_left != nullptr) {
    //         left_h = _left->height();
    //     }
    //     if (_right != nullptr) {
    //         right_h = _right->height();
    //     }

    //     return 1 + max(left_h, right_h);
    // }


    // int balance_factor() {
    //     int left_h = -1;
    //     int right_h = -1;

    //     if (_left != nullptr) {
    //         left_h = _left->height();
    //     }
    //     if (_right != nullptr) {
    //         right_h = _right->height();
    //     }

    //     return left_h - right_h;
    // }


    int update_height() {
        _height = height();
        return _height;
    }


    tree_node(T item=T(), tree_node* left=NULL, 
                          tree_node* right=NULL):
                    _item(item), _left(left), _right(right)
    {
        _height = -1;
        //don't forget to set the _height.
    }

    friend ostream& operator <<(ostream& outs, 
                                const tree_node<T>& t_node){
        outs<<"|"<<t_node._item<<"|";
        return outs;
    }
};

template <typename T>
void tree_insert(tree_node<T>* &root, const T& insert_me);

template <typename T>
tree_node<T>* tree_search(tree_node<T>* root, const T& target);

template <typename T>
bool tree_search(tree_node<T>* root, const T& target,
                 tree_node<T>* &found_ptr);

template<typename T>
void tree_print(tree_node<T>* root, int depth=0,
                                    ostream& outs=cout);

template<typename T> //prints detailes info about each node
void tree_print_debug(tree_node<T>* root, int depth=0,
                                          ostream& outs=cout);

template <typename T> //clear the tree
void tree_clear(tree_node<T>* &root);

template <typename T> //erase target from the tree
bool tree_erase(tree_node<T>*& root, const T& target);
template <typename T> //erase rightmost node from the tree -> max_value
void tree_remove_max(tree_node<T>* &root, T& max_value);


template <typename T> //print in_order
void in_order(tree_node<T>* root,ostream& outs=cout);

template <typename T> //print pre_order
void  pre_order(tree_node<T>* root,ostream& outs=cout);

template <typename T> //print post_order
void  post_order(tree_node<T>* root,ostream& outs=cout);

template <typename T> //string in_order
string in_order_string(tree_node<T>* root);

template <typename T> //string pre_order
string pre_order_string(tree_node<T>* root);

template <typename T> //string post_order
string post_order_string(tree_node<T>* root);


template <typename T> //return copy of tree pointed to by root
tree_node<T>* tree_copy(tree_node<T>* root);

template <typename T> //Add tree src to dest
void tree_add(tree_node<T>* & dest, const tree_node<T>* src);

template <typename T> //sorted array of ints -> tree
tree_node<T>* tree_from_sorted_list(const T* a);

template <typename T> // sorted array -> tree
tree_node<T>* tree_from_sorted_list(const T* a, int size);



/*
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
DEFINITION DEFINITION DEFINITION DEFINITION DEFINITION DEFINITION DEFINITION DEF
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
*/ 


//Verified
template <typename T>
void tree_insert(tree_node<T>* &root, const T& insert_me) {
    if (root == nullptr) {
        root = new tree_node<T>(insert_me);
    } else if (insert_me < root->_item){
        tree_insert(root->_left, insert_me);
    } else {
        tree_insert(root->_right, insert_me);
    }

    root -> update_height();
    // int left_height = -1;
    // int right_height = -1;
    // if (root->_left != nullptr) {
    //     left_height = root->_left->_height;
    // }
    // if (root->_right != nullptr) {
    //     right_height = root->_right->_height;
    // }
    // root->_height = 1 + max(left_height, right_height);
}


//VERIFIED
template <typename T>
tree_node<T>* tree_search(tree_node<T>* root, const T& target) {
    if (root == nullptr) {
        return root;
    }
    if (root->_item == target) {
        return root;
    }

    if (target < root->_item) {
        return tree_search(root->_left, target);
    } else {
        return tree_search(root->_right, target);
    }
}

//Verified
template <typename T>
bool tree_search(tree_node<T>* root, const T& target, tree_node<T>* &found_ptr){
    found_ptr = tree_search(root, target);
    return found_ptr;
}

//Verified
template<typename T>
void tree_print(tree_node<T>* root, int depth, ostream& outs) {
    if (root == nullptr) {
        return;
    }
    tree_print(root->_right, depth + 1);
    outs << setw(depth * 4) << "[" << root->_item << "]" << endl;
    tree_print(root->_left, depth + 1);
}


template<typename T> 
void tree_print_debug(tree_node<T>* root, int depth, ostream& outs) {
    if (root == nullptr) {
        return;
    }

    tree_print_debug(root->_right, depth + 1, outs);
    outs << setw(depth * 4) << "" << "[Item: " << root->_item << ", Height: " << root->_height;
    outs << ", Balance Factor: " << root->balance_factor() << "]" << endl;
    tree_print_debug(root->_left, depth + 1, outs);
}


//Verified
template <typename T>
void tree_clear(tree_node<T>* &root) {
    if (root != nullptr) {
        tree_clear(root->_left);
        tree_clear(root->_right);
        delete root;
        root = nullptr;
    }
}


// template <typename T>
// bool tree_erase(tree_node<T>*& root, const T& target) {
//     if (root == nullptr) {
//         return false;
//     }

//     if (target < root->_item) {
//         return tree_erase(root->_left, target);
//     } else if (target > root->_item) {
//         return tree_erase(root->_right, target);
//     } else {

//     }
//     return true;
// }
template <typename T>
bool tree_erase(tree_node<T>*& root, const T& target) {
    if (root == nullptr) {
        // Case 1: root is null
        return false;
    } else if (target > root->_item) {
        // Case 2: target > root->item, go right
        bool result = tree_erase(root->_right, target);
        root->update_height();
        return result;
    } else if (target < root->_item) {
        // Case 3: target < root->item, go left
        bool result = tree_erase(root->_left, target);
        root->update_height();
        return result;
    } else {
        // Case 4: target == root->item
        if (root->_left == nullptr) {
            // Case 4.a: root has no left subtree
            tree_node<T>* temp = root;
            root = root->_right; // Bypass target
            delete temp;
        } else {
            // Case 4.b: root has a left child
            tree_remove_max(root->_left, root->_item);
        }
        if (root != nullptr) {
            root->update_height();
        }
        return true;
    }
}



template <typename T>
void tree_remove_max(tree_node<T>* &root, T& max_value) {
    if (root == nullptr) {
        return; // The tree is empty
    }

    if (root->_right == nullptr) {
        // Rightmost node found
        max_value = root->_item;
        tree_node<T>* temp = root;
        root = root->_left; // Replace with its left child
        delete temp;
    } else {
        tree_remove_max(root->_right, max_value); // Go right
    }
}



template <typename T>
void in_order(tree_node<T>* root, ostream& outs) {
    if (root == nullptr) {
        return; // Base case
    }

    in_order(root->_left, outs); // Visit left subtree
    outs << root->_item << " "; // Visit root
    in_order(root->_right, outs); // Visit right subtree
}


template <typename T>
void pre_order(tree_node<T>* root, ostream& outs) {
    if (root == nullptr) {
        return; // Base case
    }

    outs << root->_item << " "; // Visit root
    pre_order(root->_left, outs); // Visit left subtree
    pre_order(root->_right, outs); // Visit right subtree
}


template <typename T>
void post_order(tree_node<T>* root, ostream& outs) {
    if (root != nullptr) {
        post_order(root->_left, outs);  // Visit left subtree
        post_order(root->_right, outs); // Visit right subtree
        outs << root->_item << " ";     // Visit root
    }
}


template <typename T>
string in_order_string(tree_node<T>* root) {
    if (root == nullptr) {
        return "";
    }
    return in_order_string(root->_left) + "[" +to_string(root->_item) + "]" + in_order_string(root->_right);
}

template <typename T>
string pre_order_string(tree_node<T>* root) {
    if (root == nullptr) {
        return "";
    }
    return "[" + to_string(root->_item) + "]" + pre_order_string(root->_left) + pre_order_string(root->_right);
}

template <typename T>
string post_order_string(tree_node<T>* root) {
    if (root == nullptr) {
        return "";
    }
    return post_order_string(root->_left) + post_order_string(root->_right) + "[" + to_string(root->_item) + "]";
}


//VERIFIED
template <typename T>
tree_node<T>* tree_copy(tree_node<T>* root) {
    if (root == nullptr) {
        return nullptr;
    }

    // tree_node<T>* new_node = new tree_node<T>(root->_item);
    // new_node->_left = tree_copy(root->_left);  // Copy left subtree
    // new_node->_right = tree_copy(root->_right); // Copy right subtree
    // return new_node;

    return new tree_node<T>(root->_item, tree_copy(root->_left), tree_copy(root->_right));

}

template <typename T>
void tree_add(tree_node<T>* &dest, const tree_node<T>* src) {

}



template <typename T>
tree_node<T>* tree_from_sorted_list(const T* a, int size) {
    if (size <= 0) {
        return nullptr;
    }
    // Constructing the tree recursively
    int mid = size / 2;
    tree_node<T>* root = new tree_node<T>(a[mid]);
    root->_left = tree_from_sorted_list(a, mid);
    root->_right = tree_from_sorted_list(a + mid + 1, size - mid - 1);
    return root;
}


template <typename T>
tree_node<T>* tree_from_sorted_list(const T* a) {
    int size = 0;
    while (a[size] != -1) { // I DONT KNOW
        size++;
    }
    return tree_from_sorted_list(a, size);
}


#endif