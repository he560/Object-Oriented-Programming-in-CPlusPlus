
#include "Archer.hpp"
#include "Noble.hpp"
using namespace std;

//the archer constructor takes the name and strength and sets its base classes name
//and strength
Archer::Archer(const string& name, int strength) : Warrior(name, strength) {}
//when the archer battles, it prints that message.
void Archer::setStrength(int val) {
    cout << "TWANG! " << getName() << " says: Take that in the name of my lord, \n"
    << boss->getName() << endl;
    Warrior::setStrength(val);
}
