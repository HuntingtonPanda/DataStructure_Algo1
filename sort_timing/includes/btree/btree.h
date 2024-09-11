#ifndef Co_BTREE_H
#define Co_BTREE_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include "assert.h"

using namespace std;

template <class T>
class BTree
{
public:
    BTree(bool dups = false);
    BTree(T *a, int size, bool dups = false);
    //big three:
    BTree(const BTree<T>& other);
    ~BTree();
    BTree<T>& operator =(const BTree<T>& RHS);

    void insert(const T& entry);                //insert entry into the tree
    void remove(const T& entry);                //remove entry from the tree

    void clear_tree();                          //clear this object
                                                //  (delete all nodes etc.)
    void copy_tree(const BTree<T>& other);      //copy other into this object

    bool contains(const T& entry);              //true if entry can be found in
                                                //                  the array
    T& get(const T& entry);                     //return a reference to entry
                                                //                  in the tree
    T* find(const T& entry);                    //return a pointer to this key.
                                                //          NULL if not there.

    int size() const;                           //count the number of elements
                                                //              in the tree
    bool empty() const;                         //true if the tree is empty

    bool is_valid();
                                                //print a readable version of
                                                //                  the tree
    void print_tree(int level = 0, ostream &outs=cout) const;
    friend ostream& operator<<(ostream& outs, const BTree<T>& print_me){
        print_me.print_tree(0, outs);
        return outs;
    }

    string in_order();                          // traverse the tree in an
                                                // inorder fashion, return a 
                                                // string of all the data items
                                                // with vertical delimiters

private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok;                               //true if duplicate keys may be
                                                //      inserted
    int data_count;                             //number of data elements
    T data[MAXIMUM + 1];                        //holds the keys
    int child_count;                            //number of children
    BTree* subset[MAXIMUM + 2];                 //subtrees

    bool is_leaf() const {return child_count==0;} //true if this is a leaf node

    //insert element functions
    void loose_insert(const T& entry);          //allows MAXIMUM+1 data
                                                //      elements in the root
    void fix_excess(int i);                     //fix excess of data elements
                                                //                  in child i

    //remove element functions:
    void loose_remove(const T& entry);          //allows MINIMUM-1 data
                                                //      elements in the root
    void fix_shortage(int i);                   //fix shortage of data elements
                                                //                  in child i

    void remove_biggest(T& entry);              //remove the biggest child of
                                                //          this tree->entry
    void rotate_left(int i);                    //transfer one element LEFT
                                                //              from child i
    void rotate_right(int i);                   //transfer one element RIGHT
                                                //              from child i
    void merge_with_next_subset(int i);         //merge subset i with subset
                                                //                      i+1

};

template <typename T>
BTree<T>::BTree(bool dups){

}

template <typename T>
BTree<T>::BTree(T *a, int size, bool dups){

}

//big three:
template <typename T>
BTree<T>::BTree(const BTree<T>& other){

}

template <typename T>
BTree<T>::~BTree(){

}

template <typename T>
BTree<T>& BTree<T>::operator =(const BTree<T>& RHS){
    return this;
}

template <typename T>
void BTree<T>::insert(const T& entry){
    
}                //insert entry into the tree
template <typename T>
void BTree<T>::remove(const T& entry){

}                //remove entry from the tree

template <typename T>
void BTree<T>::clear_tree(){

}                          //clear this object
                                            //  (delete all nodes etc.)
template <typename T>
void BTree<T>::copy_tree(const BTree<T>& other){

}      //copy other into this object

template <typename T>
bool BTree<T>::contains(const T& entry){
    return true;
}              //true if entry can be found in
                                            //                  the array
template <typename T>
T& BTree<T>::get(const T& entry){
    return entry;
}                     //return a reference to entry
                                            //                  in the tree
template <typename T>
T* BTree<T>::find(const T& entry){
    T* temp = nullptr;
    return temp;
}                    //return a pointer to this key.
                                            //          NULL if not there.

template <typename T>
int BTree<T>::size() const{
    return 1;
}                           //count the number of elements
                                            //              in the tree
template <typename T>                                            
bool BTree<T>::empty() const{
    return true;
}                         //true if the tree is empty

template <typename T>
bool BTree<T>::is_valid(){
    return true;
}
                                            //print a readable version of
                                            //                  the tree
template <typename T>
void BTree<T>::print_tree(int level, ostream &outs) const{

}

template <typename T>
string BTree<T>::in_order(){
    return "HI";
}                          // traverse the tree in an
                                            // inorder fashion, return a 
                                            // string of all the data items
                                            // with vertical delimiters

//insert element functions
template <typename T>
void BTree<T>::loose_insert(const T& entry){

}          //allows MAXIMUM+1 data
                                            //      elements in the root
template <typename T>                                            
void BTree<T>::fix_excess(int i){

}                     //fix excess of data elements
                                            //                  in child i

//remove element functions:
template <typename T>
void BTree<T>::loose_remove(const T& entry){

}          //allows MINIMUM-1 data
                                            //      elements in the root
template <typename T>
void BTree<T>::fix_shortage(int i){

}                   //fix shortage of data elements
                                            //                  in child i
template <typename T>
void BTree<T>::remove_biggest(T& entry){

}              //remove the biggest child of
                                            //          this tree->entry
template <typename T>
void BTree<T>::rotate_left(int i){

}                    //transfer one element LEFT
                                            //              from child i
template <typename T>
void BTree<T>::rotate_right(int i){

}                   //transfer one element RIGHT
                                            //              from child i
template <typename T>
void BTree<T>::merge_with_next_subset(int i){

}         //merge subset i with subset
                                            //                      i+1

#endif