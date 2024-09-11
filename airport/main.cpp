#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main(int argv, char** argc) {
    // char bin[100] = "0110101";
    // int binary = 0;
    // for(int i = 0; bin[i] != '\0'; ++i) {
    //     binary *= 2;
    //     binary += bin[i] - '0';
    // }
    // cout << "Decimal: " << binary << endl;

    int binary = 0;
    char yes = ' ';
    cout << "ENTER BINARY: ";
    while (true) {
        cin >> yes;
        if(yes == 'b'){
            cout << binary;
            return 0;
        }
        if(yes == '1' || yes == '0'){
            binary *= 2;
            binary += int(yes) - '0';
        }
    }

}

// int main(int argv, char** argc) {
//     int deci;
//     string binary = "";
//     cout << "ENTER DECIMAL: ";
//     cin >> deci;
//     int count = 0;
//     while (deci) {
//         binary = to_string(deci % 2) + binary;
//         deci /= 2;

//         count++;        
//         if (count % 4 == 0)
//             binary = " " + binary;
//     }

//     while(count % 4){
//         binary = "0" + binary;
//         count++;
//     }

//     cout << binary;
//}
