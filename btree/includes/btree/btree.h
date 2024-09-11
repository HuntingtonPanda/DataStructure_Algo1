#ifndef Co_BTREE_H
#define Co_BTREE_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include "../btree_array_functions/btree_array_functions.h"
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

    void makeTree(){
        data[0] = 100;
        data[1] = 500;
        data_count = 2;
        child_count = 3;

        //SECOND LAYER
        subset[0] = new BTree<T>;
        subset[0]->data[0] = 50;
        subset[0]->data[1] = 75;
        subset[0]->data_count = 2;
        subset[0]->child_count = 3;

        subset[1] = new BTree<T>;
        subset[1]->data[0] = 200;
        subset[1]->data_count = 1;
        subset[1]->child_count = 0;

        subset[2] = new BTree<T>;
        subset[2]->data[0] = 700;
        subset[2]->data[1] = 900;
        subset[2]->data_count = 2;
        subset[2]->child_count = 0;

        //THIRD LAYER
        subset[0]->subset[0] = new BTree<T>;
        subset[0]->subset[0]->data[0] = 25;
        subset[0]->subset[0]->data_count = 1;
        subset[0]->subset[0]->child_count = 0;

        subset[0]->subset[1] = new BTree<T>;
        subset[0]->subset[1]->data[0] = 55;
        subset[0]->subset[1]->data_count = 1;
        subset[0]->subset[1]->child_count = 0;
        
        subset[0]->subset[2] = new BTree<T>;
        subset[0]->subset[2]->data[0] = 85;
        subset[0]->subset[2]->data_count = 1;
        subset[0]->subset[2]->child_count = 0;
        //cout << "AHHHHHHHH\n";
        print_tree();
        //cout << "\nHELLO";
        //HELLO
    }

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

//private:
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
    private:
};

/*
    bool dups_ok;                               //true if duplicate keys may be
                                                //      inserted
    int data_count;                             //number of data elements
    T data[MAXIMUM + 1];                        //holds the keys
    int child_count;                            //number of children
    BTree* subset[MAXIMUM + 2];                 //subtrees
*/
template <typename T>
BTree<T>::BTree(bool dups): dups_ok(dups), data_count(0), child_count(0){
    // for (int i = 0; i < MAXIMUM + 1; i++) {
    //     data[i] = NULL;
    //     subset[i] = NULL;
    // }
    // subset[MAXIMUM + 1] = NULL;
}

template <typename T>
BTree<T>::BTree(T *a, int size, bool dups): dups_ok(dups), data_count(0), child_count(0){
    for (int i = 0; i < size; i++){
        insert(a[i]);
    }
}

//big three:
template <typename T>
BTree<T>::BTree(const BTree<T>& other){
    copy_tree(other);
}

template <typename T>
BTree<T>::~BTree(){
    clear_tree();
}

template <typename T>
BTree<T>& BTree<T>::operator =(const BTree<T>& RHS){
    if(this != RHS){
        copy_tree(RHS);
    }
    return *this;
}

template <typename T>
void BTree<T>::insert(const T& entry){
    loose_insert(entry);
    if (data_count > 0 && data_count > MAXIMUM) {
        BTree* temp_root = new BTree<T>(*this);
        BTree* temp_split = new BTree<T>;
        data_count = 0;
        child_count = 0;

        split(temp_root->data, temp_root->data_count, temp_split->data, temp_split->data_count);
        split(temp_root->subset, temp_root->child_count, temp_split->subset, temp_split->child_count);

        T temp;
        detach_item(temp_root->data, temp_root->data_count, temp);
        attach_item(data, data_count, temp);
        attach_item(subset, child_count, temp_root);
        attach_item(subset, child_count, temp_split);
    }
}                //insert entry into the tree
template <typename T>
void BTree<T>::remove(const T& entry){
    loose_remove(entry);
    if(data_count == 0 && child_count == 1){
        BTree<T>* Temp = subset[0];
        copy_array(subset, Temp->subset, this->child_count, Temp->child_count);
        copy_array(data, Temp->data, this->data_count, Temp->data_count);

        Temp->child_count = 0;
        Temp->data_count = 0;

        delete Temp;
    }
}                //remove entry from the tree

template <typename T>
void BTree<T>::clear_tree(){
    for(int i = 0; i < child_count; i++){
        delete subset[i];
    }
    child_count = 0;
    data_count = 0;
}                          //clear this object
                                            //  (delete all nodes etc.)
template <typename T>
void BTree<T>::copy_tree(const BTree<T>& other){
    data_count = other.data_count;
    child_count = other.child_count;
    for(int i = 0; i < other.data_count; i++){
        data[i] = other.data[i];
    }
    for(int i = 0; i < other.child_count; i++){
        subset[i] = new BTree<T>;
        subset[i]->copy_tree(*other.subset[i]);
    }
}      //copy other into this object

template <typename T>
bool BTree<T>::contains(const T& entry){
    //assert(find(entry));
    return find(entry);
}              //true if entry can be found in
                                            //                  the array
template <typename T>
T& BTree<T>::get(const T& entry){
    assert(find(entry));
    return *find(entry);
}                     //return a reference to entry
                                            //                  in the tree
template <typename T>
T* BTree<T>::find(const T& entry){
    int i = first_ge(data, data_count, entry);
    if (i < data_count && entry == data[i]) {
        return &data[i];
    } else if (i < child_count) {
        return subset[i]->find(entry);
    } else {
        return nullptr;
    }
    return nullptr;
}                    //return a pointer to this key.
                                            //          NULL if not there.

template <typename T>
int BTree<T>::size() const{
    if(is_leaf())
        return 1;

    int count = 1;
    for(int i = 0; i < child_count; i++){
        count += size();
    }
    return count;
}                           //TEST THIS

template <typename T>                                            
bool BTree<T>::empty() const{
    if(data_count == 0 && child_count == 0)
        return true;
    return false;
}                         //true if the tree is empty

template <typename T>
bool BTree<T>::is_valid(){
    return true;
}
                                            //print a readable version of
                                            //                  the tree
// template <typename T>
// void BTree<T>::print_tree(int level, ostream &outs) const{
//     if (root == nullptr) {
//         return;
//     }
//     for(int i = data_count - 1; i >= 0; i--){

//     }
//     tree_print(root->_right, level + 1);
//     outs << setw(depth * 4) << "[" << root->_item << "]" << endl;
//     tree_print(root->_left, level + 1);

//     cout << outs;
// }

template <typename T>
void BTree<T>::print_tree(int level, ostream &outs) const
{
    if (child_count > data_count)
    {
        subset[data_count]->print_tree(level + 1);
    }


    for (int i = data_count - 1; i >= 0; i--)
    {
        outs << setw(10 * level) << "[" << data[i] << ": " << data_count << ", " << child_count << "]" << endl;

        // if (i == 0)
        //     outs << setw(10 * level) << " " << "\n";
        if (child_count > i)
        {
            outs << setw(10 * level) << " " << "\n";
            subset[i]->print_tree(level + 1);
        }
    }
    outs << setw(10 * level) << " " << "\n";
}

template <typename T>
string BTree<T>::in_order(){
    string in_order = "";
    if(is_leaf()){
        for(int i = 0; i < data_count; i++){
            in_order += to_string(data[i]) + "|";
        }
        return in_order;
    }

    for(int i = 0; i < data_count; i++){
        in_order += subset[i]->in_order();
        in_order += to_string(data[i]) + "|";
    }

    in_order += subset[data_count] -> in_order();
    return in_order;
}                          // traverse the tree in an
                                            // inorder fashion, return a 
                                            // string of all the data items
                                            // with vertical delimiters

//insert element functions
template <typename T>
void BTree<T>::loose_insert(const T& entry){
    int i = first_ge(data, data_count, entry);
    if (i < data_count && entry == data[i]) 
        return;

    if(is_leaf())
        //insert_item(root->data, i, root->data_count, entry);
        ordered_insert(data, data_count, entry);
    else {
        subset[i]->loose_insert(entry);
        if (subset[i]->data_count > MAXIMUM) {
            //cout << "\nFIXING_EXCESS<><><<><><><><><><><><><>\n";
            fix_excess(i);
        }
    }
}          //allows MAXIMUM+1 data
                                            //      elements in the root
template <typename T>                                            
void BTree<T>::fix_excess(int i){

    BTree* extra = new BTree<T>;
    split(subset[i]->data, subset[i]->data_count, extra->data, extra->data_count);
    split(subset[i]->subset, subset[i]->child_count, extra->subset, extra->child_count);
    T temp;
    detach_item(subset[i]->data, subset[i]->data_count, temp);
    insert_item(data, i, data_count, temp);
    insert_item(subset, i+1, child_count, extra);

}                     //fix excess of data elements
                                            //                  in child i

//remove element functions:
template <typename T>
void BTree<T>::loose_remove(const T& entry){
    // int i = first_ge(data, data_count, entry);
    // T temp = entry;

    // if(!find(entry)){
    //     return;
    // }else if(is_leaf() && data[i] == entry){
    //     delete_item(data, i, data_count, temp);
    // }else if(data[i] == entry && i < data_count){
    //     subset[i]->remove_biggest(data[i]);
    //     fix_shortage(i);
    // }else{
    //     subset[i]->loose_remove(entry);
    //     fix_shortage(i);
    // }

    int i = first_ge(data, data_count, entry);
    T tmp_entry = entry;

    if(!find(entry)){
        return;
    }
    else{
        if(is_leaf()){
            if(data[i] == entry){
                delete_item(data, i, data_count, tmp_entry);
            }
        }
        else{
            if(data[i] == entry && i < data_count){
                subset[i]->remove_biggest(data[i]);
                if(subset[i]->data_count <  MINIMUM){
                    fix_shortage(i);
                }
            } else{
                subset[i]->loose_remove(entry);
                if(subset[i]->data_count <  MINIMUM){
                    fix_shortage(i);
                }

            }

        }  
    }
}          //allows MINIMUM-1 data
                                            //      elements in the root
template <typename T>
void BTree<T>::fix_shortage(int i){
    if (i < child_count - 1 && subset[i + 1]->data_count > MINIMUM) 
        rotate_left(i);
    else if (i > 0 && subset[i - 1]->data_count > MINIMUM)
        rotate_right(i);
    else if(i < child_count - 1)
        merge_with_next_subset(i);
    else
        merge_with_next_subset(i-1);
}                   //fix shortage of data elements
                                            //                  in child i
template <typename T>
void BTree<T>::remove_biggest(T& entry){
    if(is_leaf()){
        data_count -= 1;
        entry = data[data_count];
        return;
    }
    subset[child_count-1]->remove_biggest(entry);
    //FUCKER, YOU NEED TO REMOVE CHECK FOR SHORTAGES EVERY TIME YOU REMOVE
    if(subset[child_count-1]->data_count <  MINIMUM){
        fix_shortage(child_count-1);
    }

}              //remove the biggest child of
                                            //          this tree->entry
template <typename T>
void BTree<T>::rotate_left(int i){
    attach_item(subset[i]->data, subset[i]->data_count, data[i]);
    //data[i-1] = subset[i]->data[0];
    delete_item(subset[i+1]->data, 0, subset[i+1]->data_count, data[i]);
    if(!(subset[i+1]->is_leaf())){
        //attach_item(subset[i]->subset, subset[i]->child_count, subset[i]->subset[0]);
        subset[i]->child_count += 1;
        delete_item(subset[i+1]->subset, 0, subset[i+1]->child_count, subset[i]->subset[subset[i]->child_count - 1]);
    }
}                    //transfer one element LEFT
                                            //              from child i
template <typename T>
void BTree<T>::rotate_right(int i){
    insert_item(subset[i]->data, 0, subset[i]->data_count, data[i-1]);
    detach_item(subset[i-1]->data, subset[i-1]->data_count, data[i-1]);
    if(!(subset[i-1]->is_leaf())){
        push_right(subset[i]->subset, subset[i]->child_count);
        detach_item(subset[i-1]->subset, subset[i-1]->child_count, subset[i]->subset[0]);
    }

    //FIX CHILDREN HERE AND FOR ROTATE_LEFT
}                   //transfer one element RIGHT
                                            //              from child i
template <typename T>
void BTree<T>::merge_with_next_subset(int i){
    // T detach_entry;
    // delete_item(data, i, data_count, detach_entry);
    // attach_item(subset[i]->data, subset[i]->data_count, detach_entry);
    // merge(subset[i]->data, subset[i]->data_count, subset[i+1]->data, subset[i+1]->data_count);
    // merge(subset[i]->subset, subset[i]->child_count, subset[i+1]->subset, subset[i+1]->child_count);

    // subset[i+1]->child_count = 0;
    // subset[i+1]->data_count = 0;
    // delete subset[i+1]; 

    // for (int j = i+1; j < child_count - 1; ++j) {
    //     subset[j] = subset[j+1];
    // }

    // child_count--;
    // subset[child_count] = nullptr;

    T detach_entry;
    delete_item(data, i, data_count, detach_entry);
    attach_item(subset[i]->data, subset[i]->data_count, detach_entry);


    merge(subset[i]->data, subset[i]->data_count, subset[i+1]->data, subset[i+1]->data_count);

    // if(!subset[i+1]->is_leaf()){
    merge(subset[i]->subset, subset[i]->child_count, subset[i+1]->subset, subset[i+1]->child_count);

        // Set subset[i+1] data_count and child_count to zero
    subset[i+1]->data_count = 0;
    subset[i+1]->child_count = 0;

    // Delete subset[i+1]
    BTree<T>* temp_ptr = subset[i+1];

    // Delete temp_ptr
    delete temp_ptr; 

    // Shift subset[i+2], subset[i+3], etc., leftward
    for (int j = i+1; j < child_count - 1; ++j) {
        subset[j] = subset[j+1];
    }
    subset[child_count - 1] = nullptr;
    // }
    child_count--;

}  
                                            //                      i+1

#endif