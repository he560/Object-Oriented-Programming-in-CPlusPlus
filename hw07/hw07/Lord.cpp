#include "Lord.hpp"
#include "Noble.hpp"
using namespace std;
//The lord only has a name and it sets the base nobles name
Lord::Lord(string name) : Noble(name) {}
//the battle function uses the nobles battle function
void Lord::battle(Noble& noble) {
    Noble::battle(noble);
}
//The strength getter sums up all the strength in the army and returns it.
int Lord::strength() const{
    int strength = 0;
    for(const Protector* protect : army) {
        strength += protect->getStrength();
    }
    return strength;
}
//the set strength method sets the strength to a certain value if theres a ratio.
//if not it just sets its  strength to the value.
void Lord::setStrength(double val, bool ratio) {
    for(Protector* protect : army) {
        if (ratio) {
            double reduc = protect->getStrength()*val;
            protect->setStrength(protect->getStrength() -
                                     reduc);
        }
        else {
            protect->setStrength(val);
        }
    }
}
//the hires method first checks if the lord is alive. if its not then it  states
//the appropriate message, and then returns false. else if the protector is not
//hired, then it does the appropriate actions to hire appropriately. returns true.
//if not then it prints the message that the protector is already hired.
bool Lord::hires(Protector& protector) {
    if (!life) {
        cout << "error: lord " << name << " is attempting to hire protector "
        << protector.getName() << " but this lord is dead!\n";
        return false;
    }
    if (!protector.isHired()) {
        army.push_back(&protector);
        protector.setBoss(this);
        protector.employement(true);
        return true;
    }
    cout << "error: lord " << name << " is attempting to hire protector "
    << protector.getName() << " who is already employed.\n";
    return false;
}
//if the lord is dead, then the appropriate message is printed and returns false.
//if the preotector is hired and it finds the warrior in the army. if it does, then it
//fires correctly and returns true. if not then the message is printed that the lord is
//trying to fire someone who isn't in his army.
bool Lord::fires(Protector& protector) {
    if (!life) {
        cout << "error: lord " << name << " is attempting to fire protector "
        << protector.getName() << " but this lord is dead!\n";
        return false;
    }
    if (protector.isHired()) {
        for(size_t i = 0; i < army.size(); ++i) {
            if (army[i] == &protector) {
                protector.employement(false);
                cout << "You dont work for me anymore " <<
                protector.getName() << "! -- " << name << "." << endl;
                while (i < (army.size() - 1)) {
                    swap(army[i], army[i + 1]);
                }
                army.pop_back();
                protector.setBoss(nullptr);
                return true;
            }
        }
        cout << "error: noble " << name << " is attempting to fire warrior " << protector.getName()
        << " but this warrior doesn't work for him!\n";
    }
    cout << "error: noble " << name << " is attempting to fire warrior " << protector.getName()
    << " but he doesn't work for him and he wasn't employed to begin with!\n";
    return false;
}
