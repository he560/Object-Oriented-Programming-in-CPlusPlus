#include "Protector.hpp"
#include "Noble.hpp"
using namespace std;
//The nobles battle function
void Noble:: battle(Noble& theNoble) {
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
        theNoble.setStrength(theNoble.strength());
        cout << "He's dead, " << theNoble.name << "." << endl;
    }
    //If the other noble is dead, then it tells the current Noble then they are dead.
    else if (!theNoble.life) {
        setStrength(strength());
        cout << "He's dead, " << name << "." << endl;
    }
    //If the other Noble's strength is greater than the current Noble, then they battle accordingly.
    //The current Noble dies.
    else if (theNoble.strength() > strength()) {
        double ratio = (1.0*theNoble.strength()/strength());
        life = false;
        setStrength(0);
        theNoble.setStrength(ratio, true);
        cout << theNoble.name << " defeats " << name << endl;
    }
    //If the current Noble's strength is greater than the other Noble, then they battle accordingly.
    //The other Noble dies.
    else if (theNoble.strength() < strength()) {
        double ratio = 1.0*theNoble.strength()/strength();
        theNoble.life = false;
        setStrength(ratio, true);
        theNoble.setStrength(0);
        cout << name << " defeats " << theNoble.name << endl;
    }
}
//The getter for Noble's name.
const string& Noble::getName() const {
    return name;
}

