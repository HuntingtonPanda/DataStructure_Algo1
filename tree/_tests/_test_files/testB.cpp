#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include "../../includes/table/table.h"
#include "../../includes/table/typedefs.h"
using namespace std;

bool test_stub(bool debug = false)
{
  if (debug){
    cout << "testB:: test-sub() entering test_sub" << endl;
  }
  return true;
}

bool test_select1(bool debug = false)
{
  bool debug2 = true;
  if(debug)
  {
    vectorstr v = {"fname", "lname", "age", "major", "Salary"};
    Table t("test_select", v);
    //student 1
    v = {"Alex", "Tatoian", "19", "CS", "100"};
    t.insert_into(v);
    //student 2
    v = {"Ryan", "Tokumoto", "20", "Art", "100"};
    t.insert_into(v);
    //student 3
    v = {"Matthew", "Karvelas", "19", "Art", "200"};
    t.insert_into(v);
    //student 4
    v = {"Matthew", "Le", "19", "CS", "400"};
    t.insert_into(v);
    //student 5
    v = {"Liam", "Carson", "12", "PE", "101"};
    t.insert_into(v);
    //student 6
    v = {"Patrick", "Xuerra", "11", "Math", "101"};
    t.insert_into(v);
    //student 7
    v = {"Qnoxx", "Decker", "11", "History", "500"};
    t.insert_into(v);
    if(debug)
      cout << "\n\n" << t << endl;

    //TESTING SELECT
    // v = {"fname", "lname", "major"};
    cout << "\n\n-------------------------------------------------\n\n";
    v = {"fname", "lname", "age", "major", "Salary"};
    Table newTable = t.select(v, {"lname", ">", "To", "and", "major", "=", "CS", "or", "age", "<", "20", "and", "Salary", "<=", "101"});
    if(debug)
      cout <<"Searching for first lname < Tatoian:\n" <<  newTable << endl;
    // cout << "OLD TABLE:\n" << t;


    Queue<Token *> post;
    post = Queue<Token *>();
    post.push(new TokenStr("lname"));
    post.push(new TokenStr("To"));
    post.push(new Relational(">"));
    post.push(new TokenStr("major"));
    post.push(new TokenStr("CS"));
    post.push(new Relational("="));
    post.push(new Logical("and"));

    post.push(new TokenStr("age"));
    post.push(new TokenStr("20"));
    post.push(new Relational("<"));
    post.push(new TokenStr("Salary"));
    post.push(new TokenStr("101"));
    post.push(new Relational("<="));
    post.push(new Logical("and"));

    post.push(new Logical("or"));
    cout << "\n\n---------------------------\n" << post << "\n-------------------------\n\n";
    Table selected = t.select(v, post);
    cout << "recnos from all all the 17 to 20 year olds (non inclusive) along with all the Gomezes: " << t.select_recnos() << endl;
    cout << "" << endl
      << selected << endl;
  }
  return true;
}

TEST(TEST_BRUH, TestBruh)
{
  EXPECT_EQ(1, test_select1(1));
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

