#include "array_functions.h"
#include "assert.h"

using namespace std;

void _array_init(int a[], int size, int x)
{
    // iterates over the array and sets the elements to the value of x
    for (int i = 0; i < size; i++)
    {
        a[i] = x;
    }
};

void _append(int a[], int &size, int append_me)
{
    // increments size by 1 and append the append_me value to the index of size
    a[size++] = append_me;
};

int _find(const int a[], int size, int find_me)
{
    // iterate the array
    for (int i = 0; i < size; i++)
    {
        // return the index of the array when find_me is found
        if (a[i] == find_me)
            return i;
    }

    return -1;
};

int &_at(int a[], int size, int pos)
{
    // end the program if size is not greater than pos
    assert(pos < size && "pos cannot be bigger than size");
    assert(pos >= 0 && "pos cannot be negative");
    return a[pos];
}

ostream &_print_array(const int a[], int size, ostream &outs)
{
    outs << "[";
    for (int i = 0; i < size; i++)
    {
        outs << a[i] << "|";
    }
    outs << "]";
    return outs;
};
