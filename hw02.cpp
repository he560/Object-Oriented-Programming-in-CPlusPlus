//Hellen Ekpo
//CS 2124
//February 3rd, 2020
//Homework 2

//This programs simulates Warriors battling, it reads in a file of commands that either created and
//initialize Warriors, makes them battle, or show the Status of the Warriors.
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

struct Warrior {
    string name;
    int strength = 0;
};

void openFile(ifstream& warriorStream);

//This function reads commands from the filestream. It takes in a filestream and a vector of Warriors.
void readCommands(ifstream& warriorStream, vector<Warrior>& warriors);

//This function takes the names of the warriors and the vector of warriors.
//The function iterates through the vector of warriors to find the placement of each warrior using the strings that have their names.
//Using the found warriors, they battle, and they strengths deduct respectively.
void battle(const string& war1, const string& war2, vector<Warrior>& warriors);


int main() {
    vector<Warrior> warriors;
    ifstream warriorStream;
    readCommands(warriorStream, warriors);
}


void openFile(ifstream& warriorStream) {
    warriorStream.open("warriors.txt");
    if (!warriorStream) {
           cerr << "Couldn't open the warrior file!\n";
           exit(1);
    }
}

void readCommands(ifstream& warriorStream, vector<Warrior>& warriors) {
    openFile(warriorStream);
    string command;
    string war1, war2;
    while (warriorStream >> command) {
        if (command == "Warrior") {
            Warrior warrior;
            warriorStream >> warrior.name >> warrior.strength;
            warriors.push_back(warrior);
        }
        else if (command == "Status") {
            cout << "There are: " << warriors.size() << " warriors.\n";
            for (const Warrior& warrior : warriors) {
                cout << "Warrior: " << warrior.name << ", Strength: "
                << warrior.strength << endl;
            }
        }
        else if (command == "Battle") {
            warriorStream >> war1 >> war2;
            battle(war1, war2, warriors);
        }
    }
    warriorStream.close();
}

void battle(const string& war1, const string& war2, vector<Warrior>& warriors) {
    size_t warIndex1 = 0, warIndex2 = 0;
    for (size_t i = 0; i < warriors.size(); ++i) {
        if (warriors[i].name == war1) {
            warIndex1 = i;
        }
        else if (warriors[i].name == war2) {
            warIndex2 = i;
        }
    }
    cout << war1 << " battles " << war2 << endl;
    //If the weaker warrior is already dead, then it should output, telling
    //the stronger warrior that he's already dead.
    //Else they should battle normally.
    if (warriors[warIndex1].strength > warriors[warIndex2].strength) {
        if (warriors[warIndex2].strength == 0) {
            cout << "He's dead, " << war1 << endl;
        }
        else {
            cout << war1 << " defeats " << war2 << endl;
        }
        warriors[warIndex1].strength -= warriors[warIndex2].strength;
        warriors[warIndex2].strength = 0;
    }
    else if (warriors[warIndex1].strength < warriors[warIndex2].strength) {
        if (warriors[warIndex1].strength == 0) {
            cout << "He's dead, " << war2 << endl;
        }
        else {
            cout << war2 << " defeats " << war1 << endl;
        }
        warriors[warIndex1].strength = 0;
        warriors[warIndex2].strength -= warriors[warIndex1].strength;
    }
    //If the first warrior's strength is 0, meaning that they're both 0
    //It should output that they're both dead.
    //If they're not already dead, then they die at each others hands.
    else if (warriors[warIndex1].strength == warriors[warIndex2].strength) {
        if (warriors[warIndex1].strength == 0) {
            cout << "Oh, NO! They're both dead! YUCK!\n";
        }
        else {
            cout << "Mutual Annihilation: " << war1 << " and " << war2
            << " die at each others hands!\n";
        }
        warriors[warIndex1].strength = 0;
        warriors[warIndex2].strength = 0;
    }
}
