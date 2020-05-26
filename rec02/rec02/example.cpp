#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ofstream writeStream;
    writeStream.open("example.txt");
    writeStream << "I'm writing to the file! ";
    writeStream << "My name is hellen! ekpo";
    writeStream.clear();
    writeStream.close();
    
}
