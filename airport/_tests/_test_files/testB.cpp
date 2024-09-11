#include "gtest/gtest.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>


#include "../../includes/node/node.h"
#include "../../includes/linked_list_functions/linkedlistfunctionsTemplated.h"
#include "../../includes/stack/MyStack.h"
#include "../../includes/queue/MyQueue.h"
using namespace std;

bool test_stub(bool debug = false)
{
  if (debug){
    cout << "testB:: test-sub() entering test_sub" << endl;
  }
  /*
  cout << "\n\n";

  node<int> *head=nullptr;
  cout << "Hello";
  for (int i = 0; i < 10; i++){
    _insert_head(head, (i+1) * 10);
  }
  cout << "Bye";

  _print_list(head);


  cout << "\n\n";
  */
  Queue<int> q;
  for (int i = 0; i < 10; i++) {
      q.push(i * 10);
      // cout << "Queue after pushing " << i * 10 << ": " << q << endl;
      // cout << "QB";
      // q.print_list_backwards();
      q.print_pointers();
      cout << endl;
  }
  typename Queue<int>::Iterator it;
  for(it = q.begin(); it != q.end(); ++it)
    cout << *it << " ";

  cout << endl;
  // typename Queue<int>::Iterator it = q.begin();
  // typename Queue<int>::Iterator end = q.end();

  // cout << "Begin: " << *it << endl; // Print the value at the beginning
  // cout << "End: " << *end << endl;  // Print the value at the end


  // Iterate over the queue using iterators
  // for (; it != end; it++) {
  //     cout << "it-> " << *it << endl;
  //     cout << "End: " << *end << endl; // Print the value at the end in each iteration
  //     cout << "it != end: " << (it != end) << endl; // Print the result of comparison
  // }

  return true;
}

TEST(TEST_STUB, TestStub) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_stub(false));
}




int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

