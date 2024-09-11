#include <iostream>
#include <iomanip>

#include "includes/table/table.h"

using namespace std;

int main(int argv, char** argc) {
    
    vectorstr fields={"fname", "lname", "age"};

    Table t("student", fields);
    vectorstr row;
    row = {"Joe", "Gomez", "20"};
    t.insert_into(row);
    //cout << t << "\nHAHAHHAHAHAHAHHAHAHAH\n";
    row = {"Karen", "Orozco", "21"};
    t.insert_into(row);
    row = {"Flo", "Yao", "29"};
    t.insert_into(row);
    row = {"Jack", "Yao", "19"};
    t.insert_into(row);
    row = {"Flo", "Jackson", "20"};
    t.insert_into(row);
    row = {"Flo", "Gomez", "20"};
    t.insert_into(row);
    row = {"Karen", "Jackson", "15"};
    t.insert_into(row);

    cout << t << endl;

    Table t5("student");
    cout << "THIS IS T5\n\n" << t5 << endl;
    //  cout << "\nolder than 20 years old:" << endl;
    //  cout << t.select({"age", "fname", "lname"}, "age", "<=", "20");
    //  cout <<"record numbers from original table: "<< t.select_recnos() << endl
    //       << endl;

    // Queue<Token *> post;
    // vector<string> condition = {"(", "age", "<", "17", "or", "age", ">", "20", ")", "and", "lname", "=", "Jackson"};
    //  cout << "here is the table: " << endl
    //       << t << endl;
    //  Table selected = t.select({"lname", "age"}, condition);
    //  cout << "recnos from all all younger than 17, all older than 20, who are Jacksons: " << t.select_recnos() << endl;
    //  cout << endl
    //       << selected << endl;
//   cout << "here is the table: " << endl
//        << t << endl;
//   post = Queue<Token *>();
//   post.push(new TokenStr("age"));
//   post.push(new TokenStr("20"));
//   post.push(new Relational("<"));
//   post.push(new TokenStr("age"));
//   post.push(new TokenStr("17"));
//   post.push(new Relational(">"));
//   post.push(new Logical("and"));
//   post.push(new TokenStr("lname"));
//   post.push(new TokenStr("Gomez"));
//   post.push(new Relational("="));
//   post.push(new Logical("or"));
//   Table selected = t.select({"lname", "age"}, post);
//   cout << "recnos from all all the 17 to 20 year olds (non inclusive) along with all the Gomezes: " << t.select_recnos() << endl;
//   cout << "" << endl
//      << selected << endl;

    // cout << t << endl;


    // vectorstr fields1 = {"fname", "lname"};

    // cout << t.select_all(fields1) << "\n-------------------\n";
    //t.test_print();
    // cout << t.select_all() << "\n-------------------\n";

    // cout << t << endl;
    // FileRecord r2;
    // fstream f;
    // //open the file for reading and writing.
    // open_fileRW(f, "student.bin" );
    // int i = 0;
    // long bytes = r2.read(f, i); //empty envelop to be filled by the FileRecord object
    // cout<<"record "<<i<<": "<<r2<<endl;
    // i++;
    // while (bytes>0){
    //     bytes = r2.read(f, i);
    //     cout<<"record "<<i<<": "<<r2<<endl;
    //     i++;
    // }

    
    // Queue<int> test;
    // test.push(5);
    // test.push(15);
    // test.push(7);
    // test.push(19);
    // cout << endl << test << endl;
    cout << "\n\nDODNE DONE ODNE" << endl;
    return 0;
}
