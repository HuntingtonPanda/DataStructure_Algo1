#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include "../../includes/btree_array_functions/btree_array_functions.h"
#include "../../includes/btree/btree.h"

using namespace std;

// bool test_stub(bool debug = false)
// {
//   if (debug){
//     cout << "testB:: test-sub() entering test_sub" << endl;
//   }
//   return true;
// }

bool test_remove(bool debug = false)
{
    BTree<int> bt1;
    bt1.insert(5);
    bt1.insert(15);
    bt1.insert(10);
    bt1.insert(20);
    bt1.insert(50);
    bt1.insert(40);
    bt1.insert(70);

    cout << "\n------------------------\n";
    bt1.print_tree();

    bt1.remove(20);

    cout << "\n------------------------\n";
    bt1.print_tree();
    return true;
}  

bool test_add_remove(bool debug = false)
{
  if (debug){
    cout << "testB:: test-sub() entering test_sub" << endl;
  }
    cout << "\n\n";

  int size = 5;
  int foo [7] = { 1, 2, 3, 14, 50};
  int copied[7];
  int cpSize = 0;
  print_array(foo, size);
  cout << "ORDERED INSERT\n";
  ordered_insert(foo, size, 5);
  print_array(foo, size);
  attach_item(foo, size, 85);
  print_array(foo, size);

  int temp;
  detach_item(foo, size, temp);
  cout << "REMOVED ITEM: " << temp << endl;
  print_array(foo, size);
  delete_item(foo, 0, size, temp);
  cout << "REMOVED ITEM: " << temp << endl;
  print_array(foo, size);

  cout << "\n\n----------TESTING copy_array TESTING-------------\n\n";

  copy_array(copied, foo, cpSize, size);
  print_array(copied, cpSize);
  cout << "FIRST GE then 12: " << first_ge(copied, cpSize, 12) << endl;
  cout << "FIRST GE then 120: " << first_ge(copied, cpSize, 120) << endl;

  cout << "MAX INDEX: " << index_of_maximal(copied, cpSize);

  attach_item(copied, cpSize, 85);
  Swap(copied[0], copied[3]);
  print_array(copied, cpSize);
  cout << "MAX INDEX: " << index_of_maximal(copied, cpSize);
  cout << "\n\n";
  return true;
}

bool test_split_merge(bool debug = false)
{
  if (debug){
    cout << "testB:: test-sub() entering test_sub" << endl;
  }
  cout << "\n\n";
  int arr1Size = 5;
  int arr2Size = 5;
  int arr1[20] = {1, 2, 3, 4, 5};
  int arr2[20] = {6, 7, 8, 9, 10};

  print_array(arr1, arr1Size);
  print_array(arr2, arr2Size);
  
  cout << endl;
  merge(arr1, arr1Size, arr2, arr2Size);
  print_array(arr1, arr1Size);

  cout << endl;
  int arr3[20];
  int arr3Size = 0;
  split(arr1, arr1Size, arr3, arr3Size);
  print_array(arr1, arr1Size);
  print_array(arr3, arr3Size);

  cout << "\n\n";

  return true;
}

bool test_BTree(bool debug = false)
{
  if (debug){
    cout << "testB:: test-sub() entering test_sub" << endl;
  }
  cout << "HELLO\n";
  BTree<int> bt1;
  bt1.makeTree();
  BTree<int> bt2;
  cout << "HELLO";

  // bt2.copy_tree(bt1);
  // bt2.print_tree();
  cout << "\n-----------------------------------\n";
  int hi = 5;
  bt1.insert(hi);
  bt1.print_tree();

  cout << "\n------------ROTATE_RIGHT--------------\n";
  bt1.subset[0]->rotate_right(1);                   //transfer one element RIGHT
  bt1.print_tree();

  cout << "\n------------ROTATE_LEFT--------------\n";
  bt1.subset[0]->rotate_left(0);                   //transfer one element RIGHT
  bt1.print_tree();

  cout << "\n------------REMOVE_BIGGEST--------------\n";
  int big;
  bt1.remove_biggest(big);                   //transfer one element RIGHT
  bt1.print_tree();
  cout << "\nBIGGEST: " << big << endl;
  
  cout << "\n------------REMOVE_BIGGEST from subset 0--------------\n";
  bt1.subset[0]->remove_biggest(big);                   //transfer one element RIGHT
  bt1.print_tree();
  cout << "\nBIGGEST: " << big << endl;

  cout << "\n------------ROTATE_RIGHT_FROM_ROOT--------------\n";
  bt1.rotate_right(1);                   //transfer one element RIGHT
  bt1.print_tree();

  cout << "\n------------ROTATE_LEFT_FROM_ROOT--------------\n";
  bt1.rotate_left(0);                   //transfer one element RIGHT
  bt1.print_tree();
  // if(bt1.find(-200))
  //   cout << "HI\n";
  // cout << "< " << bt1.find(-200) << " >";
  // cout << endl;

  // cout << "[ " << bt1.get(-200) << " ]";
  // cout << endl;

  // if(bt1.contains(200))
  //   cout << "Peanut\n";
  // if(bt1.contains(-100))
  //   cout << "Butter\n";

  
  // cout << "\n-----------------------------------\nCLEAR TREE\n";
  // bt1.clear_tree();
  // bt1.insert(5);
  // bt1.print_tree();
  // cout << "\n-----------------------------------\nCLEAR TREE\n";
  // bt1.insert(10);
  // bt1.print_tree();

  // cout << "\n-----------------------------------\nCLEAR TREE\n";
  // bt1.insert(1);
  // bt1.print_tree();
  // cout << "\n-----------------------------------\n";
  // int hi1 = 1;
  // bt1.insert(hi1);
  // bt1.print_tree();

  return true;
}

// TEST(TEST_STUB, TestStub) {
  
//   //EXPECT_EQ(0, <your individual test functions are called here>);

//   EXPECT_EQ(1, test_stub(false));
// }

TEST(TEST_STUB, TestStub) {

  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_remove(false));
}

// TEST(TEST_BTREE, TestBTree) {
  
//   //EXPECT_EQ(0, <your individual test functions are called here>);

//   EXPECT_EQ(1, test_BTree(false));
// }

// TEST(TEST_ADD_REMOVE, TestAddRemove) {
  
//   //EXPECT_EQ(0, <your individual test functions are called here>);

//   EXPECT_EQ(1, test_add_remove(false));
// }

/*
TEST(TEST_SPLIT_MERGE, TestSplitMerge) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_split_merge(false));
}
*/

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

