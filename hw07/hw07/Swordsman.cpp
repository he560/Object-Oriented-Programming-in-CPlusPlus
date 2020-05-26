#include "Noble.hpp"
#include "Swordsman.hpp"

using namespace std;
//the constructor takes the name and strength and sets the base's appropriate feilds.
Swordsman::Swordsman(const string& name, int strength) : Warrior(name, strength) {}
//The set strength prints this specific message
void Swordsman::setStrength(int val) {
    cout << "CLANG! " << getName() << " says: Take that in the name of my lord, \n"
    << boss->getName() << endl;
    Warrior::setStrength(val);
}
