#ifndef Co_TABLE_H
#define Co_TABLE_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include <vector>
#include "assert.h"
#include <fstream>
#include <algorithm>

#include "typedefs.h"

//Shunting and RPN shit
#include "../shunting_rpn/queue/MyQueue.h"
#include "../shunting_rpn/new_token/token.h"
#include "../shunting_rpn/new_token/new_token.h"

#include "../shunting_rpn/rpn/rpn.h"
#include "../shunting_rpn/shunting_yard/shunting_yard.h"



#include "../bplustree/map.h"
#include "../bplustree/multimap.h"
#include "../binary_files/file_record.h"





using namespace std;

class Table{
public:
    static unsigned long RecCount;

    Table(string _name, vectorstr _category);
    Table(string _name);
    void insert_into(const vectorstr& row);
    Table select_all();
    Table select_all(const vectorstr& _category);

    Table select(const vectorstr& _category, const string& want_type, const string& operator_type, const string& want);
    Table select(const vectorstr& _category, const vectorstr& conditions);
    Table select(const vectorstr& _category, Queue<Token *> conditions);
    Table select(const vectorstr& _category, const queuestr& conditions);
    
    //string wordConvert (int which);
    vectorlong eval(Queue<Token *> conditions);

    vectorlong select_recnos(){return selected;}
    vectorstr get_category(){return category;}
    void set_category();
    vectorstr get_categories(){return category;}
    bool empty();

    void print(ostream& outs) const;


    friend ostream& operator<<(ostream& outs, const Table& _table)
    {
        //_table.print_table([vector of catagories], [vector of record number]);
        _table.print(outs);
        return outs;
    }

    void test_print(){
        // cout << organize[0]["Flo"] << endl;
        // vectorlong temp = organize[0]["Flo"];
        // cout << temp;

        Queue<Token *> post;
        post.push(new TokenStr("lname"));
        post.push(new TokenStr("YaoMING"));
        post.push(new Relational("="));

        vectorlong evaluation = eval(post);
        cout << "\nSIZE: " << evaluation.size() << endl;
    }


private:
    fstream f;
    FileRecord scribe;

    fstream list_category;    
    string name;
    
    vectorstr category;
    vectorMMap organize;
    map_sl index;

    vectorlong selected;

    unsigned long RecNum = -1;
};

unsigned long Table::RecCount = 0;

Table::Table(string _name, vectorstr _category):name(_name), category(_category){
    //CONVERTING STRING TO C STRING WITH ".bin" AT END
    char _fileName[name.size() + 5];
    strcpy(_fileName, name.c_str());
    strcat(_fileName, ".bin");

    // list_category.open("poopy.bin");
    // if (list_category.is_open()) { // check if the file was opened successfully
    //     list_category << "Hello, world PEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE!\n"; // write data to the file
    //     list_category.close();
    // }

    //Open binary file with the name given by user
    open_fileW(f, _fileName);
    
    //making a map of the catagories
    for(int i = 0; i < _category.size(); i++)
        index[_category[i]] = i; 

    // for(int i = 0; i < _category.size(); i++){
    //     cout << "index[" << _category[i] << "] = " << index[_category[i]] << endl;
    // }
    // cout << "\n\n";

    ofstream list_category(_name + ".txt");
    if (list_category.is_open()) {
        // for (const auto& cat : _category) {
        //     list_category << cat << endl;
        // }
        for(int i = 0; i < _category.size(); i++){
            if(i != 0)
                list_category << endl;
            list_category << _category[i];
        }
             
        list_category.close();
    } else {
        cout << "Unable to open file " << _name << ".txt" << endl;
    }
    
    organize.resize(_category.size());
    // organize.push_back(mmap_sl());
}

Table::Table(string _name){
    name =_name + "_" + to_string(RecCount++);
    //ifstream((name + "_fields.txt").c_str());
    char _file[_name.size() + 5];
    strcpy(_file, _name.c_str());
    strcat(_file, ".txt");
    ifstream file(_file);
    string str;
    while (getline(file, str))
    {
        category.push_back(str);
    }
    file.close();

    strcpy(_file, _name.c_str());
    strcat(_file, ".bin");
    open_fileRW(list_category, _file);  // reading from

    char _fileName[name.size() + 5];
    strcpy(_fileName, name.c_str());
    strcat(_fileName, ".bin");
    open_fileW(f, _fileName);  // wrtiing to

    ofstream _list_category(name + ".txt");
    if (_list_category.is_open()) {
        // for (const auto& cat : _category) {
        //     _list_category << cat << endl;
        // }
        for(int i = 0; i < category.size(); i++){
            if(i != 0)
                _list_category << endl;
            _list_category << category[i];
        }
             
        _list_category.close();
    } else {
        cout << "Unable to open file " << _name << ".txt" << endl;
    }

    for(int i = 0; i < category.size(); i++)
        index[category[i]] = i; 
    organize.resize(category.size());

    int a = 0;

    long byteRead = scribe.read(list_category, a);     //read the readirst record
    // cout << "\n----------PEANUTS---------\n" << string(temp.scribe._record[0]) << "\n---------BUTTERS-------\n";
    vectorstr tempVStr(category.size(), "");
    for (int i = 0; i < category.size(); i++){
        tempVStr[i] = string(scribe._record[i]);
        //cout << "record: " << i << " VSTR:" << tempVStr[i] << endl;
    } 
    while (byteRead > 0){
        a++;
        insert_into(tempVStr);

        byteRead = scribe.read(list_category, a);         //read next record.
        for (int i = 0; i < category.size(); i++){
            tempVStr[i] = string(scribe._record[i]);
            //cout << "record: " << i << " VSTR:" << tempVStr[i] << endl;
        } 
    }

}

void Table::insert_into(const vectorstr& row){
    scribe = FileRecord(row);
    RecNum = scribe.write(f);
    //cout << RecNum << endl;
    // cout << "\n----------------------------\n";
    // cout << RecCount++;
    // cout << "\n----------------------------\n";
    
    // for(int i = 0; i < category.size(); i++)
    //     organize[index[category[i]]][row[i]] += RecNum;
    for(int i = 0; i < category.size(); i++)
        organize[i].insert(row[i], RecNum);
        //(organize[i])[category[i]] += RecNum;
    // for(int i = 0; i < category.size(); i++)
    //     cout << "------------------------\n       " << category[i] << "\n----------------------\n" << organize[i];
}

// string Table::wordConvert (int which){
//     int i = 0;
//     while(scribe._record[which][i] != '/0')
//     scribe._record[which][];
    
// }

Table Table::select_all(){
    /*
    scribe = FileRecord(row);
    RecNum = scribe.write(f);
    */

    Table temp(name + "_" + to_string(RecCount++), category);

    //------------------------------------------
    char _fileName[name.size() + 5];
    strcpy(_fileName, name.c_str());
    strcat(_fileName, ".bin");
    
    fstream read;
    open_fileRW(read, _fileName);
    //-----------------------------------------------


    int i = 0;
    //the famous Golden While Loop:
    long byteRead = temp.scribe.read(read, i);     //read the readirst record
    // cout << "\n----------PEANUTS---------\n" << string(temp.scribe._record[0]) << "\n---------BUTTERS-------\n";
    vectorstr tempVStr(category.size(), "");
    for (int i = 0; i < category.size(); i++){
        tempVStr[i] = string(temp.scribe._record[i]);
        //cout << "record: " << i << " VSTR:" << tempVStr[i] << endl;
    } 
    while (byteRead > 0){
        i++;
        temp.insert_into(tempVStr);

        byteRead = temp.scribe.read(read, i);         //read next record.
        for (int i = 0; i < category.size(); i++){
            tempVStr[i] = string(temp.scribe._record[i]);
            //cout << "record: " << i << " VSTR:" << tempVStr[i] << endl;
        } 
    }
    //outs<< setw(width) << i <<r2<<endl;
    temp.f.close();
    read.close();

    return temp;
}

vectorlong Table::eval(Queue<Token *> conditions){
    Stack<Token*> stack;
    Token* tokenIt;

    TokenStr* first;
    TokenStr* second;

    RecordSet* setFirst;
    RecordSet* setSecond;

    Relational* queueRel;
    Logical* queueLog;

    mmap_sl* search;
    mmap_sl::Iterator it;
    mmap_sl::Iterator it2;

    vectorlong recNums;
    vectorlong toAdd;

    while(conditions.begin() != conditions.end()){
        tokenIt = conditions.pop();
        recNums.resize(0); 
        switch(tokenIt->type()){
            case STRING: stack.push(tokenIt);
                          break;
            case RELATIONAL:
                //cout << "Hello\n"; 
                queueRel = static_cast<Relational*>(tokenIt);
                first = static_cast<TokenStr*>(stack.pop());
                second = static_cast<TokenStr*>(stack.pop());
                
                search = &(organize[index[second->get_string()]]);

                switch(queueRel -> get_relationType()){
                    case EQ: stack.push(new RecordSet(organize[index[second->get_string()]][first->get_string()]));
                                break;
                    case GE: recNums = organize[index[second->get_string()]][first->get_string()];            
                    case G: 
                            it = organize[index[second->get_string()]].upper_bound(first->get_string());
                            while(it != organize[index[second->get_string()]].end()){
                                toAdd = (*it).getVals();
                                //cout << "recNum Size: " << recNums.size() << " getVal Size: " << toAdd.size() << "SUUUUUUUUUURE\n";
                                recNums.insert(recNums.end(), toAdd.begin(), toAdd.end());
                                it++;
                            }
                            // cout << "recNum Size: " << recNums.size() << " getVal Size: " << toAdd.size() <<"COOOOOOl\n";
                            // it = organize[index["age"]].upper_bound("20");
                            // toAdd = (*it).getVals();
                            // recNums.insert(recNums.end(), toAdd.begin(), toAdd.end());
                            //cout << "\nNUMS: " << recNums << endl;
                            // cout << "upper_bound(20): " << *it << endl;
                            // cout << "\n\nTHIS RAN\n\n";
                            //recNums.insert(recNums.end(), *it.getVals().begin(), *it..getVals().end());
                            //stack.push(new RecordSet(organize[index[second->get_string()]][first->get_string()]));
                            stack.push(new RecordSet(recNums));
                                break;
                    case L: //cout << "THIS RAN<12>";
                            it2 = organize[index[second->get_string()]].lower_bound(first->get_string());
                            //cout << "\nit2: " << *it2;
                            it = organize[index[second->get_string()]].begin();
                            //cout << "\nit: " << *it;
                            while(it != it2){
                                toAdd = (*it).getVals();
                                //cout << "recNum Size: " << recNums.size() << " getVal Size: " << toAdd.size() << "SUUUUUUUUUURE\n";
                                recNums.insert(recNums.end(), toAdd.begin(), toAdd.end());
                                it++;
                            }
                            stack.push(new RecordSet(recNums));           
                                break;
                    case LE://cout << "THIS RAN<12>";
                            it2 = organize[index[second->get_string()]].lower_bound(first->get_string());
                            // cout << "\nit2: " << *it2;
                            it = organize[index[second->get_string()]].begin();
                            // cout << "\nit: " << *it;
                            while(it != it2){
                                toAdd = (*it).getVals();
                                //cout << "recNum Size: " << recNums.size() << " getVal Size: " << toAdd.size() << "SUUUUUUUUUURE\n";
                                recNums.insert(recNums.end(), toAdd.begin(), toAdd.end());
                                it++;
                            }
                            //stack.push(new RecordSet(recNums));    
                             toAdd = organize[index[second->get_string()]][first->get_string()];
                             recNums.insert(recNums.end(), toAdd.begin(), toAdd.end());
                             stack.push(new RecordSet(recNums));
                                break;
                    default: //cout << "YOU SUCK\n";
                            assert(false);
                }
                    break;
                case LOGICAL:
                    setFirst = static_cast<RecordSet*>(stack.pop());
                    setSecond = static_cast<RecordSet*>(stack.pop());
                    queueLog = static_cast<Logical*>(tokenIt);
                    switch(queueLog -> get_logicType()){
                        case AND:
                            sort(setFirst->get_records().begin(), setFirst->get_records().end());
                            sort(setSecond->get_records().begin(), setSecond->get_records().end());
                            set_intersection(setFirst->get_records().begin(), setFirst->get_records().end(),
                                                        setSecond->get_records().begin(), setSecond->get_records().end(), back_inserter(recNums));
                            stack.push(new RecordSet(recNums));
                            //cout << "\n-AND-<" << recNums << ">-AND-\n"; 
                            break;
                        case OR:
                            sort(setFirst->get_records().begin(), setFirst->get_records().end());
                            sort(setSecond->get_records().begin(), setSecond->get_records().end());
                            set_union(setFirst->get_records().begin(), setFirst->get_records().end(),
                                                        setSecond->get_records().begin(), setSecond->get_records().end(), back_inserter(recNums));
                            stack.push(new RecordSet(recNums));
                            //cout << "\n-OR-<" << recNums << ">-OR-\n"; 
                            break;
                        default:
                            assert(false);
                    }


            // case OPERATION:
            //     queueOper = static_cast<Operator*> (tokenIt);
            //     stack.push(queueOper -> eval(stack.pop(), stack.pop()));
            //     break;
            
    //         default: //cout << "YOU SUCK ALOT\n";
    //                 assert(false);

        }
    }

    setFirst = static_cast<RecordSet*>(stack.pop());
    selected = setFirst -> get_records();
    //cout << "\n\nSELECTED:   " << selected << "\n\n";
    // cout << "\n\nSELECTED:   " << selected << "\n\n";
    return selected;
}


Table Table::select_all(const vectorstr& _category){
    Table temp(name + "_" + to_string(RecCount++), _category);
    
    char _fileName[name.size() + 5];
    strcpy(_fileName, name.c_str());
    strcat(_fileName, ".bin");
    
    fstream read;
    open_fileRW(read, _fileName);

    int i = 0;
    long byteRead = temp.scribe.read(read, i);
    //cout << "\n----------PEANUTS---------\n" << string(temp.scribe._record[index[_category[1]]]) << "\n---------BUTTERS-------\n";
    vectorstr tempVStr(_category.size(), "");
    for (int i = 0; i < _category.size(); i++){
        tempVStr[i] = string(temp.scribe._record[index[_category[i]]]);
        //cout << "record: " << i << " VSTR:" << tempVStr[i] << endl;
    } 

    while (byteRead > 0){
        i++;
        temp.insert_into(tempVStr);

        byteRead = temp.scribe.read(read, i);      
        for (int i = 0; i < _category.size(); i++){
            tempVStr[i] = string(temp.scribe._record[index[_category[i]]]);
        } 
    }
    temp.f.close();
    read.close();


    return temp;
}

Table Table::select(const vectorstr& _category, const string& want_type, const string& operator_type, const string& want){
    Queue<Token *> post;
    post.push(new TokenStr(want_type));
    post.push(new TokenStr(want));
    post.push(new Relational(operator_type));
    
    return select(_category, post);
}

Table Table::select(const vectorstr& _category, const vectorstr& conditions){
    Queue<Token *> infix;
    for(int i = 0; i < conditions.size(); i++){
        if(conditions[i] == "=" || conditions[i] == "<=" || conditions[i] == ">=" || 
                                        conditions[i] == "<" || conditions[i] == ">")
            infix.push(new Relational(conditions[i]));
        else if(conditions[i] == "and" || conditions[i] == "or")
            infix.push(new Logical(conditions[i]));
        else if(conditions[i] == "(")
            infix.push(new LeftParen(conditions[i]));
        else if(conditions[i] == ")")
            infix.push(new RightParen(conditions[i]));
        else
            infix.push(new TokenStr(conditions[i]));
    }
    ShuntingYard sy(infix);
    //cout << "\n\n---------------------------\n" << sy.postfix() << "\n-------------------------\n\n";
    return select(_category, sy.postfix());
}

Table Table::select(const vectorstr& _category, Queue<Token *> conditions){
    vectorlong recNums = eval(conditions);

    Table temp(name + "_" + to_string(RecCount++), _category);
    
    char _fileName[name.size() + 5];
    strcpy(_fileName, name.c_str());
    strcat(_fileName, ".bin");
    fstream read;
    open_fileRW(read, _fileName);

    if(recNums.size() > 0){
        int a = 0;
        long byteRead = temp.scribe.read(read, recNums[a]);
        //cout << "\n----------PEANUTS---------\n" << string(temp.scribe._record[index[_category[1]]]) << "\n---------BUTTERS-------\n";
        vectorstr tempVStr(_category.size(), "");
        for (int i = 0; i < _category.size(); i++){
            tempVStr[i] = string(temp.scribe._record[index[_category[i]]]);
            //cout << "record: " << i << " VSTR:" << tempVStr[i] << endl;
        } 

        for(int j = 0; j < recNums.size(); j++){
            read.close();
            open_fileRW(read, _fileName);
            a++;
            temp.insert_into(tempVStr);

            byteRead = temp.scribe.read(read, recNums[a]);      
            for (int i = 0; i < _category.size(); i++){
                tempVStr[i] = string(temp.scribe._record[index[_category[i]]]);
            } 
        }
        temp.f.close();
        read.close();
    }

    return temp;
}

Table Table::select(const vectorstr& _category, const queuestr& conditions){
    return Table("sure" + to_string(RecCount), {"fname", "lname", "age"});
}

void Table::set_category(){

}

bool Table::empty(){
    return RecNum == -1;
}

void Table::print(ostream& outs) const{
    const int width = 25;
    char _fileName[name.size() + 5];
    strcpy(_fileName, name.c_str());
    strcat(_fileName, ".bin");
    
    FileRecord r2;
    fstream read;
    //open the file for reading and writing.
    open_fileRW(read, _fileName);

    outs<<"Table name: " << name <<", records: " << RecNum + 1 << endl << setw(25) << "record";
    for(string cat:category)
        outs << setw(width) << cat;
    outs << endl << endl;

    //int i = 0;
    //long bytes = r2.read(read, i); //empty envelop to be filled by the FileRecord object
    
    // if((bytes > 0)){
    //     outs<< setw(width) << i <<r2<<endl;
    //     i++;
    //     while (bytes>0){
    //         bytes = r2.read(read, i);
    //         outs<< setw(width) << i <<r2<<endl;
    //         i++;
    //     }
    // }
    
    int i = 0;
    //the famous Golden While Loop:
    long byteRead = r2.read(read, i);     //read the readirst record
    while (byteRead > 0){
        //cout << "reading record " <<setw(3)<< i << ": " << r2 << endl;
        outs<< setw(width) << i <<r2<<endl;
        i++;
        byteRead = r2.read(read, i);         //read next record.
    }
    //outs<< setw(width) << i <<r2<<endl;
    read.close();
    //outs << "YESS";
}
#endif