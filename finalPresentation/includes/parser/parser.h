#ifndef Co_PARSER_H
#define Co_PARSER_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cassert>

#include "../table/table.h"
#include "../tokenizer/stokenize.h"

#include "typedefs.h"

using namespace std;

class Parser{

public:
    Parser();
    Parser(const char* command);

    mmap_ss parse_tree(); 
    void set_string(const char* command);
    void print_lookup();

    void create_mmaps(const char* command);
    void create_mapping();

    void make_table();
private:
    mmap_ss parser_tree;
    map_sl index;
    bool success_state;
    int _table[MAX_ROWS][MAX_COLUMNS];
};

Parser::Parser(){
    make_table();
    create_mapping();
}

Parser::Parser(const char* command){
    make_table();
    create_mapping();
    set_string(command);
}

mmap_ss Parser::parse_tree(){
    return parser_tree;
}

void Parser::set_string(const char* command){
    parser_tree.clear();

    const char* walker = command;
    int index_walker = 0;
    vector<string> temp;
    string str = "";
    bool in_quotes = false;

    while (walker[index_walker] != '\0') {
        if (walker[index_walker] == '\"' && !in_quotes) {
            // Start of quoted string
            in_quotes = true;
            index_walker++;
            continue;
        }
        if (walker[index_walker] == '\"' && in_quotes) {
            // End of quoted string
            in_quotes = false;
            temp.push_back(str);
            str = "";
            index_walker++;
            continue;
        }

        if (in_quotes) {
            // Collect characters within quotes
            str += walker[index_walker++];
            continue;
        }

        if (isspace(walker[index_walker]) || walker[index_walker] == ',') {
            if (!str.empty()) {
                temp.push_back(str);
                str = "";
            }
            if (walker[index_walker] == ',') {
                temp.push_back(",");
            }
            index_walker++;
            continue;
        }

        if (walker[index_walker] == '(' || walker[index_walker] == ')') {
            if (!str.empty()) {
                temp.push_back(str);
                str = "";
            }
            str += walker[index_walker];
            temp.push_back(str);
            str = "";
            index_walker++;
            continue;
        }

        if (walker[index_walker] == '>' || walker[index_walker] == '<' || walker[index_walker] == '=') {
            if (!str.empty()) {
                temp.push_back(str);
                str = "";
            }
            str += walker[index_walker];
            if (walker[index_walker + 1] == '=') {
                str += "=";
                index_walker++;
            }
            temp.push_back(str);
            str = "";
            index_walker++;
            continue;
        }

        // Regular character collection
        str += walker[index_walker++];
    }

    if (!str.empty()) {
        temp.push_back(str);
    }

    //cout << temp << endl;

    // const char* walker = command;
    // int index_walker = 0;
    // vectorstr temp;
    // string str = "";
    // string strTemp = "";
    // while(walker[index_walker] != '\0'){
    //     if(walker[index_walker] == ' ' || walker[index_walker] == ','){
    //         temp.push_back(str);
    //         str = "";
    //         if(walker[index_walker] == ','){
    //             temp.push_back(",");
    //             index_walker++;
    //         }
    //         index_walker++;
    //     }
    //     if(isdigit(walker[index_walker])){
    //         temp.push_back(str);
    //         str = "";
    //     }
    //     if(walker[index_walker] == '('){
    //         temp.push_back("(");
    //         index_walker++;
    //     } 
    //     else if(walker[index_walker] == ')'){
    //         temp.push_back(")");
    //         index_walker++;
    //     } 
    //     else if(walker[index_walker] == '>'){
    //         strTemp = ">";
    //         if(walker[index_walker + 1] == '='){
    //             strTemp += "=";
    //             index_walker++;
    //         }
    //         temp.push_back(strTemp);
    //         index_walker++;
    //     } 
    //     else if(walker[index_walker] == '<'){
    //         strTemp = ">";
    //         if(walker[index_walker + 1] == '='){
    //             strTemp += "=";
    //             index_walker++;
    //         }
    //         temp.push_back(strTemp);
    //         index_walker++;
    //     }
    //     else if (walker[index_walker] == '='){
    //         temp.push_back("=");
    //         index_walker++;
    //     } 
    //     str += walker[index_walker++];
    // }
    // temp.push_back(str);

    // cout << temp << endl;
    string currStr;
    string where = "yes";
    int col;
    int currState = 0;
    int lState = 0;
    int i = 0;


    for(; i < temp.size() && currState != -1; i++)
    {
        currStr = temp[i];
        if (index.contains(currStr))
            col = index[currStr];
        else
            col = SYMBOL;
        
        lState = currState;
        currState = _table[currState][col];

        switch(currState){
            case 1:  
            case 7:  
            case 13:  
                parser_tree["command"] += currStr;
                break;
            case 3:   
            case 9:  
            case 18:  
                parser_tree["table_name"] += currStr;
                break;
            case 14: 
            case 15:  
                parser_tree["fields"] += currStr;
                break;
            case 5:  
                parser_tree["col"] += currStr;
                break;
            case 19:  
                 parser_tree["where"] += where;
                break;
            case 20:  
                parser_tree["condition"] += currStr;
                break;
            case 11:  
                parser_tree["values"] += currStr;
                break;
            default:
                break;
        } 
    } 
    //cout << parser_tree;
    if(_table[currState][0] == 1) 
        return;
    
    parser_tree.clear();
    
    // cout << "last: " << lState << endl;

    if(lState == 14)
        throw("Expected: Comma");
    else if(lState == 16)
        throw("Expected: Field Name");
    else if(lState == 17)
        throw("Expected: Table Name");
    else if(lState == 18)
        throw("Expected: Condition");
    //parser_tree.clear();  

}

void Parser::make_table(){
    init_table(_table);
    //MAKE COMMAND
    mark_fail(_table, 0);
    mark_fail(_table, 1);
    mark_fail(_table, 2);
    mark_fail(_table, 3);
    mark_fail(_table, 4);

    mark_success(_table, 5);

    mark_fail(_table, 6);

    //INSERT COMMAND
    mark_fail(_table, 7);
    mark_fail(_table, 8);
    mark_fail(_table, 9);
    mark_fail(_table, 10);

    mark_success(_table, 11);

    mark_fail(_table, 12);

    //SELECT COMMAND
    mark_fail(_table, 13);
    mark_fail(_table, 14);
    mark_fail(_table, 15);
    mark_fail(_table, 16);
    mark_fail(_table, 17);

    mark_success(_table, 18);

    mark_fail(_table, 19);

    mark_success(_table, 20);



    //ROW 0
    //NAME OF COMMANDS
    mark_cell(0, _table, MAKE, 1);
    mark_cell(0, _table, CREATE, 1);
    mark_cell(0, _table, INSERT, 7);
    mark_cell(0, _table, SELECT, 13);
    

    //ROW 1
    //THIS IS THE MAKE BRANCH
    mark_cell(1, _table, TABLE, 2);

    //ROW 2
    //mark_cell(2, _table, TABLE_NAME, 3);
    mark_cell(2, _table, SYMBOL, 3);

    //ROW 3
    mark_cell(3, _table, FIELDS, 4);

    //ROW 4
    //mark_cell(4, _table, COL, 5);
    mark_cell(4, _table, SYMBOL, 5);

    //ROW 5
    mark_cell(5, _table, COMMA, 6);

    //ROW 6
    mark_cell(6, _table, SYMBOL, 5);

    //ROW 7 
    //THIS IS FOR THE INSERT COMMAND
    mark_cell(7, _table, INTO, 8);
    
    //ROW 8
    // mark_cell(8, _table, TABLE_NAME, 9);
    mark_cell(8, _table, SYMBOL, 9);
    
    //ROW 9
    mark_cell(9, _table, VALUES, 10);

    //ROW 10
    // mark_cell(10, _table, VALS, 11);
    mark_cell(10, _table, SYMBOL, 11);

    //ROW 11
    mark_cell(11, _table, COMMA, 12);

    //ROW 12
    //mark_cell(12, _table, VALS, 11);
    mark_cell(12, _table, SYMBOL, 11);

    //ROW 13
    //SELECT BRANCH
    //mark_cell(13, _table, FIELDS_LIST, 14);
    mark_cell(13, _table, SYMBOL, 14);
    mark_cell(13, _table, STAR, 15);

    //ROW 14
    mark_cell(14, _table, COMMA, 16);
    mark_cell(14, _table, FROM, 17);

    //ROW 15
    mark_cell(15, _table, FROM, 17);

    //ROW 16
    // mark_cell(16, _table, FIELDS_LIST, 14);
    mark_cell(16, _table, SYMBOL, 14);

    //ROW 17
    // mark_cell(17, _table, TABLE_NAME, 18);
    mark_cell(17, _table, SYMBOL, 18);

    //ROW 18
    mark_cell(18, _table, WHERE, 19);

    //ROW 19
    // mark_cell(19, _table, CONDITIONS, 20);
    mark_cell(19, _table, SYMBOL, 20);

    //ROW 20
    // mark_cell(20, _table, CONDITIONS, 20);
    mark_cell(20, _table, SYMBOL, 20);
}

void Parser::print_lookup(){

}

void Parser::create_mmaps(const char* command){
    // char s[] = 
    //         "make table student fields last, first, age, major, class";
    // STokenizer stk(s);
    // Token t;
    // stk>>t;
    // while(stk.more()){
    //     //process token here...
    //     cout<<setw(10)<<t.type_string()<<setw(10)<<t<<endl;


    //     t = Token();
    //     stk>>t;
    // }
    
    const char* walker = command;
    int index_walker = 0;
    vectorstr temp;
    string str = "";
    string strTemp = "";
    while(walker[index_walker] != '\0'){
        if(walker[index_walker] == ' ' || walker[index_walker] == ','){
            temp.push_back(str);
            str = "";
            if(walker[index_walker] == ','){
                temp.push_back(",");
                index_walker++;
            }
            index_walker++;
        }
        if(walker[index_walker] == '('){
            temp.push_back("(");
            index_walker++;
        } 
        else if(walker[index_walker] == ')'){
            temp.push_back(")");
            index_walker++;
        } 
        else if(walker[index_walker] == '>'){
            strTemp = ">";
            if(walker[index_walker + 1] == '='){
                strTemp += "=";
                index_walker++;
            }
            temp.push_back(strTemp);
            index_walker++;
        } 
        else if(walker[index_walker] == '<'){
            strTemp = ">";
            if(walker[index_walker + 1] == '='){
                strTemp += "=";
                index_walker++;
            }
            temp.push_back(strTemp);
            index_walker++;
        }
        else if (walker[index_walker] == '='){
            temp.push_back("=");
            index_walker++;
        } 
        str += walker[index_walker++];
    }
    temp.push_back(str);

    cout << temp << endl;

}

void Parser::create_mapping(){
    index["make"] = MAKE;
    index["table"] = TABLE;
    index["table_name"] = TABLE_NAME;
    index["fields"] = FIELDS;
    index["col"] = COL;
    index[","] = COMMA;
    index["insert"] = INSERT;
    index["into"] = INTO;
    index["values"] = VALUES;
    index["vals"] = VALS;
    index["select"] = SELECT;
    index["fields_list"] = FIELDS_LIST;
    index["*"] = STAR;
    index["from"] = FROM;
    index["where"] = WHERE;
    index["conditions"] = CONDITIONS;
}

#endif