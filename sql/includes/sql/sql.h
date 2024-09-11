#ifndef Co_SQL_H
#define Co_SQL_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include "assert.h"

#include "../parser/parser.h"

using namespace std;

class SQL{
public:
    SQL();

    Table command(const string& command);

    vectorlong select_recnos();

    void interactive();
    void batch();

private:
    Parser parserVar;
    mmap_ss ptreeVar;

    vectorlong selected = {};

    Map<string, Table> currentTable;
    FileRecord scribe;
    int tables;
};

SQL::SQL(): tables(0){
        fstream file("SQLTracking.txt", ios::app); // Open the file
        file.close();

        file.open("SQLTracking.txt");
        string line;
        cout << "SQL: Currently tracking these tables:" << endl
             << "-------------------------------------" << endl;
        while (getline(file, line)) { // Read lines from the file
            cout << line << endl;
            currentTable[line] = Table(line); // Appending the tables to the map
            tables++;
        }
        cout << "-------------------------------------" << endl;

        cout << "\n";
        file.close(); // Close the file
}

Table SQL::command(const string& command){
    try
    {
        parserVar.set_string(command.c_str());
        ptreeVar = parserVar.parse_tree();
        string _command = ptreeVar["command"][0];
        // cout << "ptreeVar: " << ptreeVar << endl;

        if(_command == "make" || _command == "create"){
            string name = ptreeVar["table_name"][0];
            Table MakeTable(name, ptreeVar["col"]);
            if(!currentTable.contains(name))
            {
                fstream f;
                f.open("SQLTracking.txt", ios::app);
                cout << "tables: " << tables << endl;
                if(tables != 0){
                    f << endl;
                }
                f << name;
                tables ++;
            }
            currentTable[name] = MakeTable;
            return MakeTable;

            // cout << "create table ";
            //currentTable[ptreeVar["table_name"][0]] = new Table(ptreeVar["table_name"][0], ptreeVar["col"]);
        
            //return *currentTable[ptreeVar["table_name"][0]];
            // return Table(ptreeVar["table_name"][0], ptreeVar["col"]);
        } else if(_command == "select"){
            // Table temp(ptreeVar["table_name"][0]);

            if(!currentTable.contains(ptreeVar["table_name"][0]))
                throw("Invalid table name");
            Table temp = currentTable[ptreeVar["table_name"][0]];
            
            if(ptreeVar["fields"][0] == "*"){ //FOR ALL FIELDS
                if(ptreeVar.contains("where")){
                    // cout << "HERE" << endl;
                    // cout << "ptreeVar[condition]: " << ptreeVar["condition"] << endl;
                    // cout << "temp.get_categories(): " << temp.get_categories() << endl;
                    Table tempSelected = temp.select(temp.get_categories(), ptreeVar["condition"]);
                    selected = temp.select_recnos();
                    return tempSelected;
                }
                // cout << "There is no condition\n";
                
                Table tempSelected = temp.select_all();
                selected = temp.select_recnos();
                return tempSelected;
            }else{ //FOR SPECIFIC FIELDS NOT ALL

                if(ptreeVar.contains("where")){
                    Table tempSelected = temp.select(ptreeVar["fields"], ptreeVar["condition"]);
                    selected = temp.select_recnos();    
                    return tempSelected;
                }
                // cout << "There is no condition\n";
                Table tempSelected = temp.select_all(ptreeVar["fields"]);
                selected = temp.select_recnos();
                return tempSelected;
            }

        } else if(_command == "insert"){
            if(!currentTable.contains(ptreeVar["table_name"][0]))
                throw("Invalid table name");
            // Table temp(ptreeVar["table_name"][0]);
            currentTable[ptreeVar["table_name"][0]].insert_into(ptreeVar["values"]);
            return currentTable[ptreeVar["table_name"][0]];
        }
    }
    catch(const char* str)
    {
        cout << str << '\n';
        return Table();
    }
    catch(...)
    {
        cout << "Invalid command\n";
        return Table();
    }
    
    
// and
//or
//and or
//or and
//and or and
//or and or
//and and or
//or and and
//...
//check double parentheses ((...))
//empty vector and/or regular/empty vector (vice versa)

/* 
    cout<<"input: ["<< command.c_str() <<"]"<<endl<<endl;
    ptreeVar.print_lookup();

    //cout << "\n---------------------------------\n" << ptreeVar["command"] << "\n---------------------------------\n";

    vectorstr cats = {"last", "first", "dep", "salary", "year"};
    Table tempTable("employee", cats);
    return tempTable;
*/
}

vectorlong SQL::select_recnos(){
    return selected;
}

void SQL::interactive(){
    //SQL sql;

    batch();
    string _command;
    
    while (true){
        cout << ">";
        getline(cin, _command);
        cout << command(_command) << endl;

        if (_command == "exit"){
            return;
        }
    }

}

void SQL::batch()
{
    Table table;

    const vector<string> make_commands = {

    /*00*/     "make table employee fields  last, first, dep, salary, year",
    /*01*/     "insert into employee values Blow, Joe, CS, 100000, 2018",
    /*02*/     "insert into employee values Blow, JoAnn, Physics, 200000, 2016",
    /*03*/     "insert into employee values Johnson, Jack, HR, 150000, 2014",
    /*04*/     "insert into employee values Johnson, \"Jimmy\" ,Chemistry,140000, 2018",

    /*05*/     "make table student fields fname, lname, major, age, company",
    /*06*/     "insert into student values Flo, Yao, CS, 20, Google",
    /*07*/     "insert into student values Bo, Yang, CS, 28, Microsoft",
    /*08*/     "insert into student values \"Sammuel L.\", Jackson, CS, 40, Uber",
    /*09*/     "insert into student values \"Flo\", \"Jackson\", Math, 21, Google",
    /*10*/     "insert into student values \"Greg\", \"Pearson\", Physics, 20, Amazon"
    };

    const vector<string> select_commands = {
    /*01*/     "select lname, fname, major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson",
    /*02*/     "select lname fname, major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson",
    /*03*/     "select lname, , major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson",
    /*04*/     "select lname, fname, major  student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson",
    /*05*/     "select lname, fname, major from  where ((lname=Yang or major=CS) and age<23 )or lname=Jackson",
    /*06*/     "select lname, fname, major from student where",
    /*07*/     "select lname, fname, major from student where (lname=Yang or major=CS) and age<23 )or lname=Jackson",
    /*08*/     "select lname, fname, major from student where ((lname=Yang or major=CS and age<23 )or lname=Jackson",
    /*09*/     "select lname, fname, major from student where ((lname= or major=CS) and age<23 )or lname=Jackson",
    /*10*/     "select lname, fname, major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson",
    /*11*/     "select lname, fname, major from student where ((lname=Yang  major=CS) and age<23 )or lname=Jackson",
    /*12*/     "select lname, fname, major from student where ((lname=Yang or ) and age<23 )or lname=Jackson",
    /*13*/     "select lname, fname, major from student where ((lname=Yang or major=CS) and age<23 )or ",
    /*14*/     "select lname, fname, major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson",
    };

    for (int i = 0; i < make_commands.size(); i++)
    {
        // cout << ">" << make_commands[i] << endl;
        command(make_commands[i]);
    }

    for(int i = 0; i < select_commands.size(); i++)
    {
        cout << (i+1) << ") " << select_commands[i] << "\n\n";

        table = command(select_commands[i]);

        cout << table << "\n\n";  
    }

}

#endif