//Hellen Ekpo
//Recitation 1
//1/31/2020
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void displayVector(vector<int> v) {
    for(size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << ' ';
    }
    cout << endl;
}

void doubleItems(vector<int> v) {
    for(size_t i = 0; i < v.size(); ++i) {
        v[i] = v[i] * 2;
        cout << v[i] << ' ';
    }
    cout << endl;
}

void doubleRangedFor(vector<int>& v) {
    for(int&item : v) {
        item = item * 2;
        cout << item << ' ';
    }
    cout << endl;
}

int main() {
    //1
    std::cout << "Hello World!\n";
    
    //2
    cout << "Hello World!\n";
    
    //3
    int x;
    cout << x << endl;
    
    //4
    int y = 7;
    int z = 2000000017;
    double pie = 3.14159;
    cout << sizeof(x) << " " << sizeof(y) << endl;
    cout << sizeof(z) << " " << sizeof(pie) << endl;
    
    //5
    //x = "felix";
    
    //6
    if (y >= 10 && y <= 20) {
        cout << y << " is between 10 and 20!\n";
    }
    else {
        cout << y << " is not between 10 and 20!\n";
    }
    //7
    for (size_t i = 10; i < 21; ++i) {
        cout << i << ' ';
    }
    cout << endl;
    
    int h = 10;
    while(h != 21) {
        cout << h << ' ';
        ++h;
    }
    cout << endl;
    
    int e = 10;
    
    do {
        cout << e << ' ';
        ++e;
    } while (e != 21);
    cout << endl;
    
    //9
    ifstream ifs;
    bool test = false;
    string filename;
    while (!test) {
        cout << "What is the name of the file you want to open?" << endl;
        cin >> filename;
        ifs.open(filename);
        if (!ifs) {
            cout << "Could not open the file.\n" << "Try again.\n" << endl;
            ifs.clear();
        }
        else {
        test = true;
        }
    }
    //9
    string word;
    while(ifs >> word) {
        cout << word << endl;
    }
    ifs.close();
    
    //10
    vector<int> v1;
    for (int i = 0; i < 21; ++i) {
        v1.push_back(i);
    }
    
    //11
    for(size_t i = 0; i < v1.size(); ++i) {
        cout << v1[i] << ' ';
    }
    cout << endl;
    for(int&item : v1) {
        cout << item << ' ';
    }
    cout << endl;
    for(size_t i = v1.size() - 1; i != -1; --i) {
        cout << v1[i] << ' ';
    }
    cout << endl;
    //12
    vector<int> v2 = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    for(int item : v2) {
        cout << item << ' ';
    }
    cout << "\n";
    cout << "Functions\n";
    //13
    displayVector(v1);
    displayVector(v2);
    //14
    doubleItems(v2);
    // display v2 again to check if items didnt change
    displayVector(v2);
    //15
    doubleRangedFor(v2);
    // display v2 again to check if items actually changed
    displayVector(v2);
}
