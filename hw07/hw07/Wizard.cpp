#include "Protector.hpp"
#include "Wizard.hpp"
using namespace std;
//The constructor for the Wizards takes the name and strength. It sets the base classes
//With name and strength.
Wizard::Wizard(const string& name, int strength) : Protector(name, strength) {}
//When the Wizard sets the its value aka when it is battling, it makes the noise POOF
//it uses the set strength from base class.
void Wizard::setStrength(int val) {
    cout << "POOF!\n";
    Protector::setStrength(val);
}
//It uses the get strength from base class.

