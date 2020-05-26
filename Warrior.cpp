#include "Noble.h"
#include "Warrior.h"
#include <iostream>
#include <string>
//In the Warrior.cpp file, it contains the definitions of the Warrior methods. They are qualified using Warrior::
//The Noble and Warrior header files are included so that it is aware of the both of the classes public methods.
using namespace std;

namespace WarriorCraft {
//The constructor, it takes the Warrior's name and it's strength, it sets the Warrior's name and strength, and it
//also sets the employment to false, and the boss is initially nullptr since warriors aren't created with bosses.
Warrior::Warrior(const string& name, int strength) : name(name), strength(strength),
employed(false), boss(nullptr) {}
//This method returns name, function marked constant to prevent modification and name
//is returned by constant reference to avoid making a copy of the string.
const string& Warrior::getName() const {
    return name;
}
//This method returns the strength, marked constant to prevent modification.
int Warrior::getStrength() const {
    return strength;
}
//This method returns the status of employment, and marked constant to prevent modification.
bool Warrior::isHired() const {
    return employed;
}
//The employment method changes the status of the employment but only under the condition that:
//The warrior is employed and is trying to become unemployed or
//The warrior is unemployed and is trying to become employed.
//If any of those conditions are true, then the appropriate change will occur and the method
//will return true, else it will return false.
bool Warrior::employement(bool status) {
    if (employed && !status) {
        employed = false;
        return true;
    }
    else if (!employed && status) {
        employed = true;
        return true;
    }
    return false;
}
//This method sets the strength of the warrior.
void Warrior::setStrength(int val) {
    strength = val;
}
//This method allows for a Warrior to run away from the army he's apart of. First, his employment status
//is changed to false. Then, the message is printed. Then the boss is notified to abandon the warrior
//and then the warrior's boss is changed to nullptr. If all of these occur successfully, then the
//method returns true, else returns false.
bool Warrior::runaway() {
    if (employed) {
        employed = false;
        cout << name << " flees in terror, abandoning his lord, " << boss->getName()
        << endl;
        boss->abandon(*this);
        boss = nullptr;
        return true;
    }
    return false;
}
//This method sets the Warrior's boss only under the conditions that:
//The warrior is unemployed, and the boss passes in is not a nullptr AKA its a valid boss
//This will result in the warrior having a boss, and the employment status changes to true.
//The warrior is employed, and the boss passed in is a nullptr AKA the process of firing.
//This will result in the warrior not having a boss and the employment status set to false.
bool Warrior::setBoss(Noble* noble) {
    if (!employed && noble != nullptr) {
        boss = noble;
        employed = true;
        return true;
    }
    else if (employed && noble == nullptr) {
        boss = noble;
        employed = false;
        return true;
    }
    return false;
}
//The output operator allows for the Warriors name and its strength to be printed.
ostream& operator << (ostream& os, const Warrior& theWarrior) {
    os << "  -->" << theWarrior.name << ": " << theWarrior.strength;
    return os;
}
}
