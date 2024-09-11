#ifndef Co_FILE_RECORD_H
#define Co_FILE_RECORD_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include <vector>
#include "assert.h"
#include "utilities.h"

using namespace std;

class FileRecord{
public:
    static const int MAX = 100;
    char _record[MAX][MAX+1];
    //when you construct a Record, it's either empty or it
    //  contains a word
    FileRecord(){
        //_record[0] = '\0';
        for(int i = 0; i < MAX; i++){
            _record[i][0] = '\0';
        }
        recno = -1;
    }

    FileRecord(vector<char*> str){
        //strncpy(_record, str, MAX);
        for(int i = 0; i < MAX; i++){
            _record[i][0] = '\0';
        }
        for(int i = 0; i < str.size() && i < MAX; i++){
            strncpy(_record[i], str[i], MAX);
        }
    }
    FileRecord(vector<string> s){
        //strncpy(_record, s.c_str(), MAX);
        for(int i = 0; i < MAX; i++){
            _record[i][0] = '\0';
        }
        for(int i = 0; i < s.size(); i++){
            strncpy(_record[i], s[i].c_str(), MAX);
        }
    }

    long write(fstream& outs);              //returns the record number
    long read(fstream& ins, long recno);    //returns the number of bytes
                                            //      read = MAX, or zero if
                                            //      read passed the end of file


    friend ostream& operator<<(ostream& outs,
                               const FileRecord& r);
private:

    int recno;
    
};

long FileRecord::write(fstream &outs){
    //r.write(f); //take the Record r and write it into file f
    //  and return the record number of this Record

    //write to the end of the file.
    outs.seekg(0, outs.end);


    long pos = outs.tellp();    //retrieves the current position of the
                                //      file pointer

    //outs.write(&record[0], sizeof(record));
    //outs.write(_record, sizeof(_record)); I COMMENTED OUT

    //-----------------------------------
    
    for(int i = 0; i < MAX; i++)
    {
        outs.write(_record[i], sizeof(_record[i]));
    }

    //-----------------------------------

    return pos/sizeof(_record);  //record number
}

long FileRecord::read(fstream &ins, long recno){ //IDK
    //returns the number of bytes read.
    //    r.read(f, 6);
    //    cout<<r<<endl;
    long pos= recno * sizeof(_record);
    ins.seekg(pos, ios_base::beg);

    //ins.read(&_record[0], sizeof(_record))
    //ins.read(_record, sizeof(_record)); I COMMENTED THIS OUT --------
    
    // for(int i = 0; i < MAX; i++)
    // {
    //     ins.read(_record[i], sizeof(_record[i]));
    //     _record[i][ins.gcount()] = '\0';
    // }
    
    long totalBytesRead = 0;
    for (int i = 0; i < MAX; i++) {
        ins.read(_record[i], sizeof(_record[i]));
        long bytesRead = ins.gcount();
        totalBytesRead += bytesRead;
        _record[i][bytesRead] = '\0';
        if (bytesRead < sizeof(_record[i])) {
            break;  // Stop reading if fewer bytes are read, indicating EOF
        }
    }

    // for(int i = 0; i < MAX; i ++){
    //     cout << "-----------------PEANUT BUTTER-------------------\n";
    //     for(int j = 0; j < MAX+1; j++){
    //         if (_record[i][j] == '/0')
    //             break;
    //         cout << _record[i][j];
    //     }
    // }
    // cout << ins.gcount() << endl;
    // cout << totalBytesRead << endl;
    return totalBytesRead;
    
    //-------------------------HUNTINGTON REMEMBER LOOK AT THIS GCOUNT IS BEHAVING WEIRD

    //don't you want to mark the end of  the cstring with null?
    //_record[] => [zero'\0'trash trash trash trash]
    //don't need the null character, but for those of us with OCD and PTSD:
    
    //_record[ins.gcount()] = '\0';
    
    
    //return ins.gcount();

}
ostream& operator<<(ostream& outs, const FileRecord& r){
    //outs << "\n--------PRINTING---------------\n";
    //outs<<r._record;
    for(int i = 0; i < r.MAX && r._record[i][0] != '\0'; i++){
        outs << setw(25) << r._record[i];
    }
    //outs << "\n----------------------------------\n";
    return outs;
}




#endif