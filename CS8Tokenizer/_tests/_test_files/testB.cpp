#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include "../../includes/tokenizer/stokenize.h"
using namespace std;

bool test_stub(bool debug = false)
{
  if (debug){
    cout << "testB:: test-sub() entering test_sub" << endl;
  }
    char s[] = "it was the night of october 17th. pi was still 3.14.";
    STokenizer stk(s);
    Token t;
    //The all too familiar golden while loop:
    stk>>t;
    while(stk.more()){
        //process token here...
        cout<<setw(10)<<t.type_string()<<setw(10)<<t<<endl;


        t = Token();
        stk>>t;
    }
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

