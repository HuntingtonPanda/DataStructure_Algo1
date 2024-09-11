#ifndef Co_BTREE_ARRAY_FUNCTIONS_H
#define Co_BTREE_ARRAY_FUNCTIONS_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "assert.h"

using namespace std;

template <class T>
T maximal(const T& a, const T& b);                      //return the larger of the two items

template <class T>
void Swap(T& a, T& b);  //swap the two items

template <class T>
int index_of_maximal(T data[ ], int n);                 //return index of the largest item in data

template <class T>
void ordered_insert(T data[ ], int& n, T entry);        //insert entry into the sorted array
                                                        //data with length n

template <class T>
int first_ge(const T data[ ], int n, const T& entry);   //return the first element in data that is
                                                        //not less than entry

template <class T>
void attach_item(T data[ ], int& n, const T& entry);    //append entry to the right of data

template <class T>
void insert_item(T data[ ], int i, int& n, T entry);    //insert entry at index i in data

template <class T>
void detach_item(T data[ ], int& n, T& entry);          //remove the last element in data and place
                                                        //it in entry

template <class T>
void delete_item(T data[ ], int i, int& n, T& entry);   //delete item at index i and place it in entry

template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2);   //append data2 to the right of data1

template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2);   //move n/2 elements from the right of data1
                                                        //and move to data2

template <class T>
void copy_array(T dest[], const T src[],
                int& dest_size, int src_size);              //copy src[] into dest[]

template <class T>
void print_array(const T data[], int n, int pos = 0);  //print array data

template <class T>
void push_right(const T data[], int& n);  //print array data


template <class T>
bool is_gt(const T data[], int n, const T& item);       //item > all data[i]

template <class T>
bool is_le(const T data[], int n, const T& item);       //item <= all data[i]

//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list); //print vector list

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme); //list.push_back addme


/*------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------
DEFINITION DEFINITION DEFINITION DEFINITION DEFINITION DEFINITION DEFINITION DEFINITION DEFINITION DEFINITION 
DEFINITION DEFINITION DEFINITION DEFINITION DEFINITION DEFINITION DEFINITION DEFINITION DEFINITION DEFINITION 
--------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------*/


template <class T>
T maximal(const T& a, const T& b){
    return max(a, b);
}                      //return the larger of the two items

template <class T>
void Swap(T& a, T& b){
    T temp = a;
    a = b;
    b = temp;
}  //swap the two items

template <class T>
int index_of_maximal(T data[ ], int n){
    int temp = 0;
    for(int i = 0; i < n; i++){
        if(data[temp] != maximal(data[temp], data[i]))
            temp = i;
    }
    return temp;
}                 //return index of the largest item in data

template <class T>
void ordered_insert(T data[ ], int& n, T entry){
   insert_item(data, first_ge(data, n, entry), n, entry);
}        //insert entry into the sorted array
                                                        //data with length n

template <class T>
int first_ge(const T data[ ], int n, const T& entry){
    for(int i = 0; i < n; i ++){
        if (data[i] >= entry)
            return i;
    }
    return n;
}   //return the first element in data that is
                                                        //not less than entry

template <class T>
void attach_item(T data[ ], int& n, const T& entry){
    data[n] = entry;
    ++n;
}    //append entry to the right of data

template <class T>
void insert_item(T data[ ], int i, int& n, T entry){
   int tempSize = n++;
   for(; data[i] != data[tempSize]; tempSize--){
      data[tempSize] = data[tempSize - 1];
   }
   data[i] = entry;
}    //insert entry at index i in data

template <class T>
void detach_item(T data[ ], int& n, T& entry){
   entry = data[--n];
   //data[n] = NULL;

}          //remove the last element in data and place
                                                        //it in entry

template <class T>
void delete_item(T data[ ], int i, int& n, T& entry){
   entry = data[i];
   int tempPlace = i;
   for(int j = 0; j < n - 1; j++){
      data[tempPlace + j] = data[tempPlace + j + 1];
   }
   --n;

}   //delete item at index i and place it in entry

template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2){
   for(int i = 0; i < n2; i++){
      data1[n1 + i] = data2[i];
   }
   n1 += n2;
}   //append data2 to the right of data1

template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2){
   n2 = n1 / 2;
   n1 -= n2;
   for (int i = 0; i < n2; i++){
      data2[i] = data1[i + n1];
   }
}   //move n/2 elements from the right of data1
                                                        //and move to data2

template <class T>
void copy_array(T dest[], const T src[], int& dest_size, int src_size){
   dest_size = src_size;
   for(int i = 0; i < src_size; i++){
      dest[i] = src[i]; 
   }
}              //copy src[] into dest[]

template <class T>
void print_array(const T data[], int n, int pos){
   for (int i = pos; i < n; i++){
      cout << setw(4) << "[" << data[i] << "] ";
   }
   cout << endl;
}  //print array data

template <class T>
bool is_gt(const T data[], int n, const T& item){
   for(int i = 0; i < n; i++){
      if(item <= data[i])
         return false;
   }
    return true;
}       //item > all data[i]

template <class T>
bool is_le(const T data[], int n, const T& item){
   for(int i = 0; i < n; i++){
      if(item > data[i])
         return false;
   }
    return true;
}       //item <= all data[i]

template <class T>
void push_right(T data[], int& n){
   int tempSize = n++;
   for(; data[0] != data[tempSize]; tempSize--){
      data[tempSize] = data[tempSize - 1];
   }
}  //print array data


//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list){
    return outs;
} //print vector list

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme){
    return list;
} //list.push_back addme



#endif