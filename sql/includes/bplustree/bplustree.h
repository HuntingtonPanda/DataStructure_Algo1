#ifndef Co_BPLUSTREE_H
#define Co_BPLUSTREE_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>

#include "btree_array_funcs.h"

using namespace std;

template <class T>
class BPlusTree
{
public:
    class Iterator{
    public:
        friend class BPlusTree;
        Iterator(BPlusTree<T>* _it=NULL, int _key_ptr = 0): it(_it), key_ptr(_key_ptr)
        {
            // while(it && key_ptr >= it->data_count)
            // {
            //     key_ptr -= it->data_count;
            //     it = it->next;
            // }
        }

        T operator *()
        {   
            return it->data[key_ptr];
        }

        Iterator operator++(int un_used){
            Iterator temp = *this;
            if(key_ptr == it->data_count -1)
            {
                key_ptr = 0;
                it = it->next;
            }
            else
                key_ptr++;
            return temp;
        }
        
        Iterator operator++(){
            if(key_ptr == it->data_count -1)
            {
                key_ptr = 0;
                it = it->next;
            }
            else
                key_ptr++;
            return *this;
        }

        friend bool operator ==(const Iterator& lhs, const Iterator& rhs)
        {
            return (lhs.it == rhs.it) && (lhs.key_ptr == rhs.key_ptr);
        } // FIX THIS AHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH

        friend bool operator !=(const Iterator& lhs, const Iterator& rhs)
        {
            return !(lhs == rhs);
        }

        void print_Iterator()
        {
            if (it)
            {
                cout<<"iterator: ";
                // print_array(it->data, it->data_count, key_ptr);
                Iterator temp = *this; 
                while(temp.it)
                {
                    cout << *temp << " ";
                    temp++;
                }
                cout << endl;
            }
            else
            {
                cout<<"iterator: NULL, key_ptr: "<<key_ptr<<endl;
            }
            //cout<<"COMPLETE PRINT ITERATOR\n";
        }

        bool is_null() {return !it;}

        void info()
        {
            cout<<endl<<"Iterator info:"<<endl;
            cout<<"key_ptr: "<<key_ptr<<endl;
            cout<<"it: "<<*it<<endl;
        }

    private:
        BPlusTree<T>* it;
        int key_ptr;
    };

    BPlusTree(bool dups = false);
    BPlusTree(T *a, int size, bool dups = false);

    //big three:
    BPlusTree(const BPlusTree<T>& other);
    ~BPlusTree();
    BPlusTree<T>& operator =(const BPlusTree<T>& RHS);

    void copy_tree(const BPlusTree<T>& other);  //copy other into this object
    void copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_node);

    void insert(const T& entry);   //insert entry into the tree
    void remove(const T& entry);   //remove entry from the tree
    void clear_tree();             //clear this object (delete all nodes etc.)

    bool contains(const T& entry) const; //true if entry can be found
    T& get(const T& entry);              //return a reference to entry
    const T& get(const T& entry)const;   //return a reference to entry
    T& get_existing(const T& entry);     //return a reference to entry
    Iterator find(const T& key);         //return an iterator to this key. NULL if not there.
    //const Iterator find(const T& key);         //return an iterator to this key. NULL if not there.
    Iterator lower_bound(const T& key);  //return first that goes NOT BEFORE key entry or next if does not exist: >= entry
    Iterator upper_bound(const T& key);  //return first that goes AFTER key exist or not, the next entry  >entry

    int size() const;                    //count the number of elements

    bool empty() const;                  //true if the tree is empty

    void print_tree(int level = 0, ostream &outs = cout) const;
    friend ostream& operator<<(ostream& outs, const BPlusTree<T>& print_me)
    {
        print_me.print_tree(0, outs);
        return outs;
    }

    bool is_valid();
    string in_order();
    string pre_order();
    string post_order();

    Iterator begin();
    Iterator end();

    ostream& list_keys(Iterator from = NULL, Iterator to = NULL)
    {
        if (from == NULL) from = begin();
        if (to == NULL) to = end();
        for (Iterator it = from; it != to; it++)
            cout<<*it<<" ";
        return cout;

    }

    void makeTree(){
        data[0] = 200;
        data[1] = 400;
        data_count = 2;
        child_count = 3;

        //Second Layer
        subset[0] = new BPlusTree<T>;
        subset[0]->data[0] = 100;
        subset[0]->data_count = 1;
        subset[0]->child_count = 2;
        
        subset[1] = new BPlusTree<T>;
        subset[1]->data[0] = 250;
        subset[1]->data[1] = 300;
        subset[1]->data_count = 2;
        subset[1]->child_count = 3;

        subset[2] = new BPlusTree<T>;
        subset[2]->data[0] = 500;
        subset[2]->data_count = 1;
        subset[2]->child_count = 2;

        //Third Layer
        subset[0]->subset[0] = new BPlusTree<T>;
        subset[0]->subset[0]->data[0] = 50;
        subset[0]->subset[0]->data_count = 1;
        subset[0]->subset[0]->child_count = 0;

        BPlusTree<int>::Iterator it = subset[0]->subset[0];

        subset[0]->subset[1] = new BPlusTree<T>;
        subset[0]->subset[1]->data[0] = 100;
        subset[0]->subset[1]->data_count = 1;
        subset[0]->subset[1]->child_count = 0;

        subset[0]->subset[0]->next = subset[0]->subset[1];

        
        subset[1]->subset[0] = new BPlusTree<T>;
        subset[1]->subset[0]->data[0] = 200;
        subset[1]->subset[0]->data_count = 1;
        subset[1]->subset[0]->child_count = 0;

        subset[0]->subset[1]->next = subset[1]->subset[0];


        subset[1]->subset[1] = new BPlusTree<T>;
        subset[1]->subset[1]->data[0] = 250;
        subset[1]->subset[1]->data[1] = 270;
        subset[1]->subset[1]->data_count = 2;
        subset[1]->subset[1]->child_count = 0;

        subset[1]->subset[0]->next = subset[1]->subset[1];


        subset[1]->subset[2] = new BPlusTree<T>;
        subset[1]->subset[2]->data[0] = 300;
        subset[1]->subset[2]->data_count = 1;
        subset[1]->subset[2]->child_count = 0;

        subset[1]->subset[1]->next = subset[1]->subset[2];


        subset[2]->subset[0] = new BPlusTree<T>;
        subset[2]->subset[0]->data[0] = 400;
        subset[2]->subset[0]->data_count = 1;
        subset[2]->subset[0]->child_count = 0;

        subset[1]->subset[2]->next = subset[2]->subset[0];

        subset[2]->subset[1] = new BPlusTree<T>;
        subset[2]->subset[1]->data[0] = 500;
        subset[2]->subset[1]->data[1] = 550;
        subset[2]->subset[1]->data_count = 2;
        subset[2]->subset[1]->child_count = 0;

        subset[2]->subset[0]->next = subset[2]->subset[1];

        print_tree();
        it.print_Iterator();
    }

    void set_dups_ok(){
        dups_ok = true;
    }
private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok;                        //true if duplicate keys are allowed
    int data_count;                      //number of data elements
    T data[MAXIMUM + 1];                 //holds the keys
    int child_count;                     //number of children
    BPlusTree* subset[MAXIMUM + 2];      //subtrees
    BPlusTree* next;

    bool is_leaf() const {return child_count == 0;}             //true if this is a leaf node

    T* find_ptr(const T& entry);         //return a pointer to this key.
                                         // NULL if not there.

    //insert element functions
    void loose_insert(const T& entry);   //allows MAXIMUM+1 data elements in
                                         //   the root
    void fix_excess(int i);              //fix excess in child i

    //remove element functions:
    void loose_remove(const T& entry);  //allows MINIMUM-1 data elements
                                        //  in the root

    BPlusTree<T>* fix_shortage(int i);  //fix shortage in child i
    // and return the smallest key in this subtree
    BPlusTree<T>* get_smallest_node();
    void get_smallest(T& entry);      //entry := leftmost leaf
    void get_biggest(T& entry);       //entry := rightmost leaf
    void remove_biggest(T& entry);    //remove the biggest child of tree->entry
    void transfer_left(int i);        //transfer one element LEFT from child i
    void transfer_right(int i);       //transfer one element RIGHT from child i
    BPlusTree<T> *merge_with_next_subset(int i); //merge subset i with  i+1

    //MY OWN FUNCTIONS
    int size(const BPlusTree<T>* node) const;

};

template <class T>
BPlusTree<T>::BPlusTree(bool dups): dups_ok(dups), child_count(0), data_count(0), next(nullptr) {}

template <class T>
BPlusTree<T>::BPlusTree(T *a, int size, bool dups): dups_ok(dups), child_count(0), data_count(0), next(nullptr)
{
    for(int i = 0; i < size; i++){
        insert(a[i]);
    }
}

template <class T>
BPlusTree<T>::BPlusTree(const BPlusTree<T> &other)
{
    copy_tree(other);
}

template <class T>
BPlusTree<T>::~BPlusTree(){
    clear_tree();
}

template <class T>
BPlusTree<T> &BPlusTree<T>::operator=(const BPlusTree<T> &RHS)
{
    if(this != &RHS){
        clear_tree();
        copy_tree(RHS);
    }
    return *this;
}

template <class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T> &other)
{
    BPlusTree<T>* temp = nullptr;
    copy_tree(other, temp);
}

/*
    bool dups_ok;                        //true if duplicate keys are allowed
    int data_count;                      //number of data elements
    T data[MAXIMUM + 1];                 //holds the keys
    int child_count;                     //number of children
    BPlusTree* subset[MAXIMUM + 2];      //subtrees
    BPlusTree* next;
*/

template <class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T> &other, BPlusTree<T> *&last_node)
{
    dups_ok = other.dups_ok;
    data_count = other.data_count;
    child_count = other.child_count;

    for(int i = 0; i < other.data_count; i++){
        data[i] = other.data[i];
    }

    for(int i = 0; i < other.child_count; i++){
        subset[i] = new BPlusTree<T>(dups_ok);
        subset[i]->copy_tree(*other.subset[i], last_node);
    }
    if(is_leaf()){
        if(last_node == nullptr){
            last_node = this;
        } else{
            last_node->next = this;
            last_node = this;
        }
    }
}

template <class T>
void BPlusTree<T>::insert(const T &entry)
{
    loose_insert(entry);

    if (data_count > MAXIMUM) {
        BPlusTree<T>* new_root = new BPlusTree<T>(dups_ok);
        
        copy_array(new_root->data, data, new_root->data_count, data_count);
        copy_array(new_root->subset, subset, new_root->child_count, child_count);\

        data_count = 0;
        child_count = 1;
        subset[0] = new_root;
        fix_excess(0);
    }
}

/*
template <class T>
void BPlusTree<T>::insert(const T &entry)
{
    loose_insert(entry);
    if (data_count > 0 && data_count > MAXIMUM) {
        BPlusTree* temp_root = new BPlusTree<T>(*this);
        BPlusTree* temp_split = new BPlusTree<T>;
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
}
*/

/*
template <class T>
void BPlusTree<T>::insert(const T &entry)
{
    loose_insert(entry); 

    if (data_count > MAXIMUM) {
        BPlusTree<T>* temp_root = new BPlusTree<T>;
        BPlusTree<T>* temp_split = new BPlusTree<T>;

        copy_array(temp_root->data, data, temp_root->data_count, data_count);
        copy_array(temp_root->subset, subset, temp_root->child_count, child_count);

        data_count = 0;
        child_count = 0;

        T temp;
        split(temp_root->data, temp_root->data_count, temp_split->data, temp_split->data_count);
        split(temp_root->subset, temp_root->child_count, temp_split->subset, temp_split->child_count);

        detach_item(temp_root->data, temp_root->data_count, temp);

        attach_item(data, data_count, temp);

        attach_item(subset, child_count, temp_root);
        attach_item(subset, child_count, temp_split);
    }
}
*/

template <class T>
void BPlusTree<T>::remove(const T &entry)
{

}

template <class T>
void BPlusTree<T>::clear_tree()
{
    for(int i = 0; i < child_count; i++){
        delete subset[i];
    }
    child_count = 0;
    data_count = 0;
}

template <class T>
bool BPlusTree<T>::contains(const T &entry) const
{
    int index = first_ge(data, data_count, entry);
        
    bool found  = false;

    if(data[index] == entry && index < data_count)
    {
        found = true;
    }

    if(found)
    {   
        if(is_leaf()){ //return true if only found at leaf
            return true;
        } else { return subset[index + 1]->contains(entry); }  //index + 1 because we added the item to the leftmost of the right subtree
    } else 
    {   
        if(is_leaf())
        {
            return false;
        }

        return subset[index]->contains(entry);
    }        
}

template <class T>
T &BPlusTree<T>::get(const T &entry)
{
        if(!contains(entry))
            insert(entry);

        return get_existing(entry);
}

template <class T>
const T &BPlusTree<T>::get(const T &entry) const
{
    int index = first_ge(data, data_count, entry);
    bool found = (index < data_count && data[index] == entry);

    if(found)
    {
        if(is_leaf()){
            return data[index];
        }else 
            return static_cast<const BPlusTree<T>*>(subset[index + 1])->get(entry); 
    } else {
        if(is_leaf())
            return data[index]; 
        else 
            static_cast<const BPlusTree<T>*>(subset[index])->get(entry);
    }
}

template <class T>
T &BPlusTree<T>::get_existing(const T &entry)
{
    int index = first_ge(data, data_count, entry);
    bool found = (index < data_count && data[index] == entry);

    if(is_leaf())
    {
        if(found)
            return data[index]; //returning item
        else 
            assert(false);
    } else {
        if(found)
            return subset[index + 1]->get(entry); //if found and is not leaf -> find in inner nodes
        return subset[index]->get(entry);
    
    }
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::find(const T &key)
{
    int index = first_ge(data, data_count, key);

    bool found = (index < data_count && data[index] == key);
    if(found)
    {
        if(is_leaf())
        {
            return Iterator(this, index);
        } else {
            return subset[index + 1]->find(key);
        }
    } else {
        if(is_leaf())
        {
            return Iterator(nullptr);
        } else {
            return subset[index]->find(key);
        }
    }
}

// template <class T>
// typename BPlusTree<T>::Iterator BPlusTree<T>::find(const T &key) const
// {
//     typename BPlusTree<T>::Iterator it;
//     return it;
// }

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::lower_bound(const T &key)
{
    // BPlusTree<T>* traverse = this;
    // while (!traverse->is_leaf()) 
    // {
    //     int i = first_ge(traverse->data, traverse->data_count, key);
    //     if (i < traverse->data_count && traverse->data[i] == key)
    //     {
    //         traverse = traverse->subset[i+1];
    //     }
    //     else
    //     {
    //         traverse = traverse->subset[i];
    //     }
    // }
    // int i = first_ge(traverse->data, traverse->data_count, key);
    // if (i < traverse->data_count && traverse->data[i] >= key)
    // {
    //     return Iterator(traverse, i);
    // }
    // else
    // {
    //     if (traverse->next != nullptr)
    //     {
    //         return Iterator(traverse->next, 0);
    //     }
    //     else
    //     {
    //         return end();
    //     }
    // }
    // for(BPlusTree<T>::Iterator it = begin(); it != end(); it++){
    //     if(key >= *it)
    //     { 
    //         return it; 
    //     }
    // }
    // return end();
    int index = first_ge(data, data_count, key);
    bool found = (index < data_count) && (data[index] == key);
    if(is_leaf())
    {
        if(index < data_count)
            return BPlusTree<T>::Iterator(this, index);
        else
            return BPlusTree<T>::Iterator(next);
    }
    return subset[index+found]->lower_bound(key);
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::upper_bound(const T &key)
{
    // BPlusTree<T>* traverse = this;
    
    // while (!traverse->is_leaf()) 
    // {
    //     int i = first_ge(traverse->data, traverse->data_count, key);
    //     traverse = traverse->subset[i];
    // }

    // int i = first_ge(traverse->data, traverse->data_count, key);
    // if (i < traverse->data_count && traverse->data[i] == key)
    // {
    //     i++;
    // }
    
    // if (i < traverse->data_count)
    // {
    //     return Iterator(traverse, i);
    // }
    // else
    // {
    //     if (traverse->next != nullptr)
    //     {
    //         return Iterator(traverse->next, 0);
    //     }
    //     else
    //     {
    //         return end();
    //     }
    // }
    // for(BPlusTree<T>::Iterator it = begin(); it != end(); it++){
    //     if(key > *it)
    //     { 
    //         return it; 
    //     }
    // }
    // return end();
    typename BPlusTree<T>::Iterator it = lower_bound(key);

    if(!it.is_null() && *it == key)
        ++it;
    
    return it;
    // int index = first_ge(data, data_count, key);
    // bool found = (index < data_count) && (data[index] == key);
    // if(is_leaf())
    // {
    //     if(index < data_count)
    //         return BPlusTree<T>::Iterator it(this, index+found);
    //     else
    //         return BPlusTree<T>::Iterator(next);
    // }
    // return subset[index+found]->lower_bound(key);
    
}

//SHOULD I COUNT THE BREADCRUMBS????
template <class T>
int BPlusTree<T>::size() const
{
    return size(this);
}

template <class T>
int BPlusTree<T>::size(const BPlusTree<T>* node) const
{
    if (node == nullptr)
        return 0;

    if (node->is_leaf())
        return node->data_count;

    int total_size = node->data_count;
    for (int i = 0; i < node->child_count; ++i)
    {
        total_size += size(node->subset[i]);
    }
    return total_size;
}

template <class T>
bool BPlusTree<T>::empty() const
{
    if(data_count == 0 && child_count == 0)
        return true;
    return false;
}

template <class T>
void BPlusTree<T>::print_tree(int level, ostream &outs) const
{
    if(is_leaf()){
        for(int i = data_count - 1; i >= 0; i--)
        {
            cout << setw(7*level) << "[ " << data[i] << " ]" << endl;
        }
    }else{
       subset[child_count - 1]->print_tree(level+1, outs); 
       for(int i = data_count - 1; i >= 0; i--) 
       {    
            cout << setw(7*level) << "[" << data[i] << "]" << endl;
            subset[i]->print_tree(level+1, outs);
       }
    }
}

template <class T>
bool BPlusTree<T>::is_valid()
{
    if(is_leaf()){ return true; }
    
    for(int i = 0; i < data_count; i++)
    {
        if(data[data_count - 1] > subset[data_count]->data[i])
        {
            return false;
        }
    }

    
    for(int i = 0; i < data_count; i++)
    {
        if(!contains(data[i])){ return false; }
    }
    

    return true; 
}

template <class T>
string BPlusTree<T>::in_order()
{
    string s;
    if(is_leaf()) {
        for(int i = 0; i < data_count; i++)
        {
            s += to_string(data[i]) + "|";
        }
    }else{
        for(int i = 0; i < data_count; i++)
        {
            s += subset[i]->in_order(); 
            s += to_string(data[i]) + "|";
        }
        s += subset[data_count]->in_order(); 
    }
    return s;
}

template <class T>
string BPlusTree<T>::pre_order()
{
    string str;
    
    for(int i = 0; i < data_count; i++)
    {
        str += to_string(data[i]) + "|"; 


        if(!is_leaf())
        {
            str += subset[i]->pre_order(); 
        }
    }
    
    if(!is_leaf())
    {
        str += subset[data_count]->pre_order();
    }

    return str;

}

template <class T>
string BPlusTree<T>::post_order()
{
    string str;

    if(!is_leaf())
    {
        str += subset[0]->post_order(); 
    }

    for(int i = 0; i < data_count; i++)
    {

        if(!is_leaf())
        {
            str += subset[i + 1]->post_order(); 
        }
        str += to_string(data[i]) + "|"; 

    }

    return str;
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::begin()
{
    // BPlusTree<T>* traverse = this;
    // while (traverse->is_leaf() == false) 
    // {
    //     traverse = traverse->subset[0];
    // }
    // return Iterator(traverse, 0);
    return Iterator(get_smallest_node());
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::end()
{
    // BPlusTree<T>* traverse = this;
    // while (traverse->is_leaf() == false) 
    // {
    //     traverse = traverse->subset[child_count - 1];
    // }
    // return Iterator(traverse, data_count);
    return Iterator(nullptr);
}

//------------------------------------------------------------------------------------------------------------------

template <class T>
T *BPlusTree<T>::find_ptr(const T &entry)
{
    BPlusTree<T>* traverse = this;
    while (traverse != nullptr)
    {
        int i = first_ge(traverse->data, traverse->data_count, entry);
        if (i < traverse->data_count && traverse->data[i] == entry)
        {
            return &traverse->data[i];
        }
        if (traverse->is_leaf())
        {
            return nullptr; 
        }
        traverse = traverse->subset[i]; 
    }
    return nullptr;
}

template <class T>
void BPlusTree<T>::loose_insert(const T &entry)
{
    // int i = first_ge(data, data_count, entry);
    // if (i < data_count && entry == data[i]){
    //     if(is_leaf()){
    //         if(!dups_ok){
    //             data[i] = entry;
    //         }
    //         else{
    //         data[i] = data[i] + entry;
    //         }
    //         return;
    //     } 
    //     else 
    //     {
    //         subset[i+1]->loose_insert(entry);
    //         if (subset[i]->data_count > MAXIMUM) {
    //             //cout << "\nFIXING_EXCESS<><><<><><><><><><><><><>\n";
    //             fix_excess(i+1);
    //         }
    //     }
    // } 
    // else 
    // {

    //     if(is_leaf()){
    //         insert_item(data, i, data_count, entry);
    //         //ordered_insert(data, data_count, entry);
    //     }
    //     else 
    //     {
    //         subset[i]->loose_insert(entry);
    //         if (subset[i]->data_count > MAXIMUM) {
    //             //cout << "\nFIXING_EXCESS<><><<><><><><><><><><><>\n";
    //             fix_excess(i);
    //         }
    //     }

    // }

    int index = first_ge(data, data_count, entry); 
    bool found = false;

    if(data[index] == entry && index < data_count)
    { found = true; }

    if(found)
    { 
        if(dups_ok){
            if(is_leaf()){   
                data[index] = data[index] + entry; 
            } else {
                subset[index + 1]->loose_insert(entry);
                if(subset[index + 1]->data_count > MAXIMUM)
                {
                    fix_excess(index);
                }
            }
        }else{
            if(is_leaf()){   
                data[index] = entry; 
            } else {
                subset[index + 1]->loose_insert(entry);
                if(subset[index + 1]->data_count > MAXIMUM)
                {
                    fix_excess(index);
                }
            }
        }
    } 
    else {
        if(is_leaf())
        {
            insert_item(data, index, data_count, entry); 
        } else {
            subset[index]->loose_insert(entry);
            if(subset[index]->data_count > MAXIMUM)
            {
                fix_excess(index);
            }
        }
    }

}

template <class T>
void BPlusTree<T>::fix_excess(int i)
{
    BPlusTree<T>* new_node = new BPlusTree<T>(dups_ok);

    split(subset[i]->data, subset[i]->data_count, new_node->data, new_node->data_count);
    split(subset[i]->subset, subset[i]->child_count, new_node->subset, new_node->child_count);

    T temp;
    detach_item(subset[i]->data, subset[i]->data_count,  temp);

    insert_item(data, i , data_count, temp); 

    insert_item(subset, i + 1, child_count, new_node);

    if(subset[i]->is_leaf())
    {
        insert_item(subset[i + 1]->data, 0, subset[i + 1]->data_count, temp); 

        subset[i + 1]->next = subset[i]->next; 

        subset[i]->next = subset[i + 1]; 

    }
}
// template <class T>
// void BPlusTree<T>::fix_excess(int i)
// {
//     BPlusTree* extra = new BPlusTree<T>;

//     split(subset[i]->data, subset[i]->data_count, extra->data, extra->data_count);
//     split(subset[i]->subset, subset[i]->child_count, extra->subset, extra->child_count);

//     T temp;
//     detach_item(subset[i]->data, subset[i]->data_count, temp);
//     insert_item(data, i, data_count, temp);

//     insert_item(subset, i+1, child_count, extra);

//     if (subset[i]->is_leaf())
//     {
//         extra->next = subset[i]->next;
//         subset[i]->next = extra;
//     }
// }

/*
template <class T>
void BPlusTree<T>::fix_excess(int i)
{
    BPlusTree* extra = new BPlusTree<T>;
    split(subset[i]->data, subset[i]->data_count, extra->data, extra->data_count);
    split(subset[i]->subset, subset[i]->child_count, extra->subset, extra->child_count);
    T temp;
    detach_item(subset[i]->data, subset[i]->data_count, temp);
    insert_item(data, i, data_count, temp);
    insert_item(subset, i+1, child_count, extra);
}
*/


template <class T>
void BPlusTree<T>::loose_remove(const T &entry)
{

}

template <class T>
BPlusTree<T> *BPlusTree<T>::fix_shortage(int i)
{
    return nullptr;
}

template <class T>
BPlusTree<T> *BPlusTree<T>::get_smallest_node()
{
    // BPlusTree<T>* traverse = this;
    // while (!traverse->is_leaf()) 
    // {
    //     traverse = traverse->subset[0];
    // }
    // return traverse;

    if(!is_leaf())
    { 
        return subset[0]->get_smallest_node(); 
    } //traverse leftmost
    return this;
}

template <class T>
void BPlusTree<T>::get_smallest(T &entry)
{
    //return *get_smallest_node;
    BPlusTree<T>* traverse = this;
    while (!traverse->is_leaf()) 
    {
        traverse = traverse->subset[0];
    }
    entry = traverse->data[0];
}

template <class T>
void BPlusTree<T>::get_biggest(T &entry)
{
    BPlusTree<T>* traverse = this;
    while (!traverse->is_leaf()) 
    {
        traverse = traverse->subset[traverse->child_count - 1];
    }
    entry = traverse->data[traverse->data_count - 1];
}

template <class T>
void BPlusTree<T>::remove_biggest(T &entry)
{

}

template <class T>
void BPlusTree<T>::transfer_left(int i)
{
    assert(i > 0 && subset[i]->data_count > MINIMUM);

    BPlusTree<T>* left_child = subset[i-1];
    BPlusTree<T>* right_child = subset[i];

    // Transfer the first item of subset[i] to the end of subset[i-1]
    T temp;
    delete_item(right_child->data, 0, right_child->data_count, temp);
    attach_item(left_child->data, left_child->data_count, temp);

    // Update data[i-1] with the new first item of subset[i]
    data[i-1] = right_child->data[0];

    if (!right_child->is_leaf())
    {
        // Transfer the first child of subset[i] to the end of subset[i-1]
        BPlusTree<T>* child;
        delete_item(right_child->subset, 0, right_child->child_count, child);
        attach_item(left_child->subset, left_child->child_count, child);
    }
}

template <class T>
void BPlusTree<T>::transfer_right(int i)
{
    assert(i < child_count - 1 && subset[i]->data_count > MINIMUM);

    BPlusTree<T>* left_child = subset[i];
    BPlusTree<T>* right_child = subset[i+1];

    // Transfer the last item of subset[i] to the beginning of subset[i+1]
    T temp;
    detach_item(left_child->data, left_child->data_count, temp);
    insert_item(right_child->data, 0, right_child->data_count, temp);

    // Update data[i] with the new first item of subset[i+1]
    data[i] = right_child->data[0];

    if (!left_child->is_leaf())
    {
        // Transfer the last child of subset[i] to the beginning of subset[i+1]
        BPlusTree<T>* child;
        detach_item(left_child->subset, left_child->child_count, child);
        insert_item(right_child->subset, 0, right_child->child_count, child);
    }
}

template <class T>
BPlusTree<T> *BPlusTree<T>::merge_with_next_subset(int i)
{
    // assert(i < child_count - 1);

    // BPlusTree<T>* left_child = subset[i];
    // BPlusTree<T>* right_child = subset[i+1];

    // T temp;
    // delete_item(data, i, data_count, temp);

    // if (!left_child->is_leaf())
    // {
    //     attach_item(left_child->data, left_child->data_count, temp);
    // }

    // for (int j = 0; j < right_child->data_count; j++)
    // {
    //     attach_item(left_child->data, left_child->data_count, right_child->data[j]);
    // }

    // if (!left_child->is_leaf())
    // {
    //     for (int j = 0; j < right_child->child_count; j++)
    //     {
    //         attach_item(left_child->subset, left_child->child_count, right_child->subset[j]);
    //     }
    // }

    // BPlusTree<T>* temp_ptr = right_child;

    // delete_item(subset, i+1, child_count, right_child);

    // if (left_child->is_leaf())
    // {
    //     left_child->next = temp_ptr->next;
    // }

    // delete temp_ptr;

    // return left_child;

    T top;
    delete_item(data, i , data_count, top);

    attach_item(subset[i]->data, subset[i]->data_count, top);
    merge(subset[i]->data, subset[i]->data_count, subset[i + 1]->data, subset[i + 1]->data_count);

    merge(subset[i]->subset, subset[i]->child_count, subset[i + 1]->subset, subset[i + 1]->child_count);

    BPlusTree<T>* loose_subtree = subset[i + 1];
    delete loose_subtree;

    child_count--;
    
    return subset[i];
}

#endif
