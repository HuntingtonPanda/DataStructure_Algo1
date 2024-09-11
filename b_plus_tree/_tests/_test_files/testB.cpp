#include "gtest/gtest.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>


//------------------------------------------------------------------------------------------
//Files we are testing:
#include "../../includes/bplustree/btree_array_funcs.h"
#include "../../includes/bplustree/bplustree.h"
#include "../../includes/bplustree/map.h"
#include "../../includes/bplustree/multimap.h"


//------------------------------------------------------------------------------------------
using namespace std;

/*
bool test_stub(bool debug = false)
{
  if (debug){
    cout << "testB:: test-sub() entering test_sub" << endl;
  }
  return true;
}

TEST(TEST_STUB, TestStub) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_stub(false));
}
*/

bool test_c(bool debug = false)
{
  // BPlusTree<int> bt1;
  // bt1.makeTree();

  // BPlusTree<int> bt2;
  // bt2.copy_tree(bt1);
  // bt2.print_tree();
  // BPlusTree<int>::Iterator it = bt2.begin();
  // it.print_Iterator();

  // cout << "\n-------------TESTING begin-----------------\n";
  // BPlusTree<int>::Iterator it = bt1.begin();
  // it.print_Iterator();

  // cout << "Size: " << bt1.size() << endl;

  return true;
}

TEST(TEST_STUB, TestStub) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_c(false));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

