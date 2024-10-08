#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include "../../includes/array_functions/array_functions.h"
//----------------------------------------------------------------------------------------
//          COPY BASIC_TEST INTO THIS FILE.
//                    AND THEN,
//         DO NOT EDIT THIS FILE ANY FURTHER
//----------------------------------------------------------------------------------------

bool basic_test(bool debug=false){
  const int MAX = 20;
  int a[MAX];
  int size = 5;  //# of interesting elements in the array
  _array_init(a, size, -1);
  cout << "\n\nafter init: ";
  _print_array(a, size);
  cout << endl;
  for (int i = size; i < 10; i++){
    _append(a, size, i * 10);
    _print_array(a, size);
    cout << endl;
  }
  int index = _find(a, size, 70);
  if (index >=0){
    cout << "found 70 at: " << _at(a, size, index) << endl;
    cout << "changing 70 to 700: " << endl;
    _at(a, size, index) = 700;
    _print_array(a, size);
    cout << endl;
  }
  cout << "\n\n";
  return true;
}
TEST(BASIC_TEST, BasicTest) {
  
  //EXPECT_EQ(1, <your individual test functions are called here>);

  EXPECT_EQ(1, basic_test());
}




int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running basic_test.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}