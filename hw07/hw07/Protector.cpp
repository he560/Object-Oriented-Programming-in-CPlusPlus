#include "Protector.hpp"
#include "Noble.hpp"
//This is the Protector.cpp file, it includes it's header file and the Noble header file
//so it knows what Noble is for its member "boss"
using namespace std;
//The constructor takes the name and strength, and sets the name and strength accordingly
//It also sets employed to false and the boss to nullptr
Protector::Protector(const string& name, int strength) : name(name),
strength(strength), employed(false), boss(nullptr) {}
//The getter for employment. returns the status.
bool Protector::isHired() const{
    return employed;
}
//The getter for name. returns name.
const string& Protector::getName() const {
    return name;
}
//This setter sets the boss.
bool Protector::setBoss(Noble* noble) {
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
//This setter sets the employment
bool Protector::employement(bool status) {
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
//This getter returns strength.
int Protector::getStrength() const {
    return strength;
}
//This setter sets the strength.
void Protector::setStrength(int val) {
    strength = val;
}
