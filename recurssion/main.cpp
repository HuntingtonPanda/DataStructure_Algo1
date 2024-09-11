#include <iostream>
#include <iomanip>
#include <string>


using namespace std;

void writing(int max, int current){
    ++current;
    for(int i = 1; i < current; i++){
        cout << " ";
    }
    cout << "This was written by call number " << current <<".\n";

    if(current < max)
        writing(max, current);

    for(int i = 1; i < current; i++){
        cout << " ";
    }
    cout << "This ALSO written by call number " << current << ".\n";
}

void printSections(string prefix, int levels) {
    if (levels == 0){
        return;
    }
    
    string s;

    for (int i = 1; i <= 9; ++i) {
        s = prefix;
        s += char('0' + i);
        if (levels != 1)
            s += '.';
        printSections(s, levels - 1);
        if (levels == 1)
            cout << s << endl;
    }
}

// THIS ONE DOES NOT WORK 

// void printSections(string prefix, int levels) {
//     if (levels == 0){
//         return;
//     }

//     for (int i = 1; i <= 9; ++i) {
//         prefix += char('0' + i);
//         if (levels != 1)
//             prefix += '.';
//         printSections(prefix, levels - 1);
//         if (levels == 1)
//             cout << prefix << endl;
//     }
// }

void catman(string first, string second){
    if (first.length() == 0) {
        cout << second << endl;
        return;
    }

    for (size_t i = 0; i < first.length(); ++i) {
        second.insert(0, 1, first[i]);
        first.erase(i, 1);

        catman(first, second);

        first.insert(i, 1, second[0]);
        second.erase(0, 1);
    }
}


int countBoxesInBox(string boxId) {
    int numberOfBoxes;
    cout << "How many boxes are inside box " << boxId << "? ";
    cin >> numberOfBoxes;

    int totalBoxes = numberOfBoxes;

    for (int i = 1; i <= numberOfBoxes; ++i) {
        string newBoxId = boxId + "." + to_string(i);
        totalBoxes += countBoxesInBox(newBoxId);
    }

    return totalBoxes;
}

void BoxesInBox() {
    int initialBoxes;
    cout << "How many unnumbered boxes can you see? ";
    cin >> initialBoxes;

    int totalBoxes = 0;
    for (int i = 1; i <= initialBoxes; ++i) {
        totalBoxes += countBoxesInBox(to_string(i));
    }

    cout << "Total number of boxes in the room: " << totalBoxes << endl;
}

double sumover(unsigned int n) {
    if (n == 0) {
        return 0.0;
    } else {
        return 1.0 / n + sumover(n - 1);
    }
}

int Choose(int n, int r) {
    if (r == 0 || r == n) {
        return 1;
    }
    return Choose(n - 1, r - 1) + Choose(n - 1, r);
}

int main(int argv, char** argc) {
    cout << "\n\n"
         << endl;

    //writing(4, 0);
    //printSections("Box: ", 3);
    //catman("CAT", "MAN");
    BoxesInBox();
    //cout << sumover(2);
    //cout << Choose(4, 2);

    cout << "\n\n\n=====================" << endl;
    return 0;
}
