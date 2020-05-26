#include "PersonWithStrengthToFight.hpp"
#include "Warrior.hpp"
#include "Protector.hpp"
//This is the PersonWithStrengthToFight cpp class.
//The constructor takes the name strength and sets its  base class name, and its own member strength
//to the appropriate value
PersonWithStrengthToFight::PersonWithStrengthToFight(const std::string& name, int strength) : Noble(name), stren(strength) {}
//The battle function utilizes the base classes battle
void PersonWithStrengthToFight::battle(Noble& noble) {
    Noble::battle(noble);
}
//The getter returns its strength
int PersonWithStrengthToFight::strength() const {
    return stren;
}
//Yhe set strength. when it loses strength, it yells UGH!
void PersonWithStrengthToFight::setStrength(double val, bool ratio) {
    std::cout << "UGH!\n";
    if (ratio) {
        double reduc = stren*val;
        stren = stren - reduc;
    }
    else {
        stren = val;
    }
}
