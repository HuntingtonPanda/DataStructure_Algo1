#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include "../../includes/array_functions/array_functions.h"
using namespace std;

bool test_stub(bool debug = false)
{
  if (debug)
  {
    cout << "testB:: test-sub() entering test_sub" << endl;
  }
  return true;
}

bool test_init_array(bool debug = false)
{
  // creates an array
  int a[20];
  int size = 5;
  const char tabs[] = "\t----------------\t";

  // if debug is true
  if (debug)
  {
    cout << tabs << "size: " << size << ", init array to -1" << endl;
  }
  _array_init(a, size, -1);
  if (debug)
  {
    cout << tabs;
    _print_array(a, size);
    cout << endl;
  }

  // check if every element of the array (up to the size) is -1
  for (int i = 0; i < size; i++)
  {
    if (a[i] != -1)
    {
      cout << "FAILED: Expected -1 at a[" << i
           << "] but found: " << a[i] << endl;
      return false;
    }
  }

  return true;
}

bool test_append(bool debug = false)
{
  // creates an array
  const int MAX = 20;
  int a[MAX];
  int size = 5;

  const char tabs[] = "\t---------------\t";

  // if debug is true
  if (debug)
  {
    cout << tabs << "size: 5, init array to -1" << endl;
  }

  // fill the array (up to the index of size) with -1
  _array_init(a, size, -1);
  if (debug)
  {
    cout << tabs;
    if (debug)
      _print_array(a, size);
    cout << endl;
  }

  // from a[size] to a[9], appends i * 10
  for (int i = size; i < 10; i++)
  {
    _append(a, size, i * 10);
    if (debug)
    {
      cout << tabs << " " << i << ": ";
      _print_array(a, size);
      cout << endl;
    }
  }

  // the array should be of size 10
  if (size != 10)
  {
    cout << "FAILED: Expected size to be 10, but found" << size << endl;
    return false;
  }

  // rechecks the calculation implemented above
  if (a[size - 1] != (size - 1) * 10)
  {
    cout << "FAILED: Expected " << (size - 1) * 10 << " at a[" << size << "]"
         << "but found: " << a[size - 1] << endl;
    return false;
  }
  return true;
}

bool test_at(bool debug = false)
{
  // creates an array
  int a[20];
  int size = 5;
  const char tabs[] = "\t--------------\t";

  // if debug is true
  if (debug)
  {
    cout << tabs << "size: 5, init array to -1" << endl;
  }

  // fill the array with -1 (up to the index of size)
  _array_init(a, size, -1);
  if (debug)
  {
    cout << tabs;
    _print_array(a, size);
    cout << endl;
  }

  int at_i;

  for (int i = 0; i < size; i++)
  {
    // make sure the current element at index i is -1
    at_i = _at(a, size, i);
    if (at_i != -1)
    {
      cout << "FAILED: Expected at(i) to return -1 but found " << at_i;
      return false;
    }
  }

  _at(a, size, 3) = 300;  // a[3] is now 300
  at_i = _at(a, size, 3); // false if a[3] is not 300
  if (at_i != 300)
  {
    cout << "FAILED: Expected to find 300 at(3), but found: " << at_i;
    return false;
  }
  return true;
}

bool test_find(bool debug = false)
{
  // create an array
  const int SIZE = 20;
  int a[SIZE];

  // create our target integer randomly
  int target = 7;

  // our target will be in the array and at a[13]
  a[13] = target;

  // function returns the index if found
  // function returns a negative number if not found
  int index = _find(a, SIZE, target);

  // actually you should test more and include like 3 test cases, finding one at the start, one in the middle, one in the back

  if (index < 0)
  {
    cout << "NOT FOUND";
    return false;
  }
  else
  {
    cout << "FOUND [" << index << "]";
  }

  return true;
}

// carry out tests are every functions
TEST(TEST_STUB, TestStub)
{

  // EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_stub(false));
}

TEST(TEST_ARRAY, TestInitArray)
{

  // EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_init_array(false));
}

TEST(TEST_ARRAY, TestAppend)
{

  // EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_append(false));
}

TEST(TEST_ARRAY, TestAt)
{

  // EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_append(false));
}

TEST(TEST_ARRAY, TestFind)
{

  // EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_find(false));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  std::cout << "\n\n----------running testB.cpp---------\n\n"
            << std::endl;
  return RUN_ALL_TESTS();
}