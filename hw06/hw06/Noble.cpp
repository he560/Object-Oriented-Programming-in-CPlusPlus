#include "Noble.h"
#include "Warrior.h"
#include <iostream>
#include <string>
#include <vector>
//In the Noble.cpp file, the Noble and Warrior header files are included, so that the file is aware of the classes and their public methods.
//The Noble.cpp file contains all of the definitions to the methods of the Noble class. They are qualified using Noble::
using namespace std;

namespace WarriorCraft {
    //The constructor, takes the name of the warrior and sets the noble's name, and sets their life to true.
    Noble::Noble(const string& name) : name(name), life(true) {}
    //The output operator, it allows for the Noble's name and army's size to be printed. If the
    //Noble's army size is greater than 0, then the warrior's info will be printed.
    ostream& operator << (ostream& os, const Noble& theNoble) {
        os << theNoble.name << " has an army of: " << theNoble.army.size() << endl;
        if (theNoble.army.size() > 0) {
            for (const Warrior* warrior : theNoble.army) {
                os << *warrior << endl;
            }
        }
        return os;
    }
    //This abandon method is called whenever a Warrior abandons the army. If the warrior passed into the method's name
    //is the same as any one of the warriors in the army, then the warrior is swapped to the back of the army, and
    //the warrior exits the army. In regards to using swap, I was told that I could use swap after using it several times
    //in lab. If the warrior is found, then the method returns true, else returns false.
    bool Noble::abandon(Warrior& warrior) {
        for(size_t i = 0; i < army.size(); ++i) {
            if (warrior.getName() == army[i] -> getName()) {
                swap(army[i], army[army.size() - 1]);
                army.pop_back();
                return true;
            }
        }
        return false;
    }
    //The battle method, allows two warriors to Battle accordingly
    void Noble::battle(Noble& theNoble) {
        cout << name << " battles " << theNoble.name << endl;
        //If they are both dead, the error message is printed.
        if (!life && !theNoble.life) {
            cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
        }
        //If their strengths are equivalent, then they both die at each other's hands.
        else if (strength() == theNoble.strength()) {
            setStrength(0);
            theNoble.setStrength(0);
            life = false;
            theNoble.life = false;
            cout << "Mutual Annhilation: " << name << " and " << theNoble.name << " die at each other's hands!" << endl;
        }
        //If the current noble is dead, then it tells the other Noble that they are dead.
        else if (!life) {
            cout << "He's dead, " << theNoble.name << "." << endl;
        }
        //If the other noble is dead, then it tells the current Noble then they are dead.
        else if (!theNoble.life) {
            cout << "He's dead, " << name << "." << endl;
        }
        //If the other Noble's strength is greater than the current Noble, then they battle accordingly.
        //The current Noble dies.
        else if (theNoble.strength() > strength()) {
            cout << theNoble.name << " defeats " << name << endl;
            double ratio = (1.0 - theNoble.strength()/strength());
            life = false;
            theNoble.setStrength(ratio, true);
            theNoble.setStrength(0);
        }
        //If the current Noble's strength is greater than the other Noble, then they battle accordingly.
        //The other Noble dies.
        else if (theNoble.strength() < strength()) {
            cout << name << " defeats " << theNoble.name << endl;
            double ratio = 1.0*theNoble.strength()/strength();
            theNoble.life = false;
            theNoble.setStrength(0);
            setStrength(ratio, true);
        }
    }
    //The strength is the sum of all of the strength of the warrior's in the army.
    //This method sums up all the strength of the warrior's in the army and returns it.
    int Noble::strength() const{
        int strength = 0;
        for(const Warrior* warrior : army) {
            strength += warrior->getStrength();
        }
        return strength;
    }
    //This method sets the strength of the Noble, which sets the strength of the warriors. If there is
    //is a ratio, then the warrior's strength are deducted accordingly. However if there isn't a ratio
    //indicated, then the strength is just set to the value.
    void Noble::setStrength(double val, bool ratio) {
        for(Warrior* warrior : army) {
            if (ratio) {
                double reduc = warrior->getStrength()*val;
                warrior->setStrength(warrior->getStrength() -
                                         reduc);
            }
            else {
                warrior->setStrength(val);
            }
        }
    }
    //This method returns the name by constant reference to prevent making a copy. The function is
    //marked constant to prevent modification.
    const string& Noble::getName() const {
        return name;
    }
    //This method hires the Warrior if and only if the warror isn't hired. It adds the warrior to the Noble's army
    //sets the warrior's boss to be this noble, set it's employment status to true. else the condition fails because
    //the warrior is already hired. the appropriate message is printed.
    bool Noble::hire(Warrior& warrior) {
        if (!warrior.isHired()) {
            army.push_back(&warrior);
            warrior.setBoss(this);
            warrior.employement(true);
            return true;
        }
        cout << "error: noble " << name << " is attempting to hire warrior "
        << warrior.getName() << " who is already employed.\n";
        return false;
    }
    //The fire method only works if the warrior is hired AND if the warrior is in the
    //Noble's army. If so, then the appropriate message is printed, they exit the army,
    //their employment status is set to false, and their boss is send to nullptr.
    bool Noble::fire(Warrior& warrior) {
        if (warrior.isHired()) {
            for(size_t i = 0; i < army.size(); ++i) {
                if (army[i] == &warrior) {
                    warrior.employement(false);
                    cout << "You dont work for me anymore " <<
                    warrior.getName() << "! -- " << name << "." << endl;
                    while (i < (army.size() - 1)) {
                        swap(army[i], army[i + 1]);
                    }
                    army.pop_back();
                    warrior.setBoss(nullptr);
                    return true;
                }
            }
            cout << "error: noble " << name << " is attempting to fire warrior " << warrior.getName()
            << " but this warrior doesn't work for him!\n";
        }
        cout << "error: noble " << name << " is attempting to fire warrior " << warrior.getName()
        << " but he doesn't work for him and he wasn't employed to begin with!\n";
        return false;
    }
}
