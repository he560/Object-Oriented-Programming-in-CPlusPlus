//Hellen Ekpo
//Homework 1
//CS 2124
//January 28, 2020
//This program is a text decryptor. It reads in a file that has been encrypted and prints the decrypted message.
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;
//This function simply decrypts a letter depending on the amount of rotations specified.
//It passes in a char letter by reference and the amount it should rotate by (int) and returns the decrypted letter.
char decryptChar(char letter, int rotation) {
    if (letter >= 'a' && letter <= 'z') {
        letter -= rotation;
        if (letter < 'a') letter += 26;
    }
    return letter;
}
//This function decrypts a string, or a line of characters. The line is passed by reference so that the string could
//be modified accordingly. The rotation is also passed in since the function utilizes the previous function to
//decrypt the line.
void decryptString(string& line, int rotation) {
    for (size_t i = 0; i < line.size(); ++i){
        line[i] = decryptChar(line[i], rotation);
    }
}
//The main streams the file and raises an error if not possible, which ends the program immediately. If not then the file
//stream reads in the rotation int into the variable rotation. It then gets each line from the file stream
//and reads it into a string encryptLine which initializes the string. It decrypts the string and pushes it to a vector.
//To print the message properly, a for loop iterates through the vector backwards and prints the message.
int main(){
    vector<string> lines;
    int rotation;
    string encryptLine;
    ifstream ifs("encrypted.txt");
    if (!ifs) {
        cerr << "Couldn't open file!\n";
        exit(1);
    }
    ifs >> rotation;
    while(getline(ifs, encryptLine)) {
        decryptString(encryptLine, rotation);
        lines.push_back(encryptLine);
    }
    ifs.close();
    for(size_t i = lines.size() - 1; i > 0; --i) {
        cout << lines[i] << endl;
    }
}
