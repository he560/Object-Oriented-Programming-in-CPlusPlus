//Hellen Ekpo
//CS2124
//Homework 7
//April 12 2020

#include <string>
#include <vector>
#include <iostream>
#include "Archer.hpp"
#include "Lord.hpp"
#include "PersonWithStrengthToFight.hpp"
#include "Swordsman.hpp"
#include "Wizard.hpp"
using namespace std;

//class Noble;
//
//class Protector {
//public:
//    Protector(const string& name, int strength);
//    virtual void setStrength(int val) = 0;
//    virtual int getStrength() const = 0;
//    bool isHired() const;
//    const string& getName() const;
//    bool employement(bool status);
//    bool setBoss(Noble* noble);
//private:
//    string name;
//    int strength;
//    bool employed;
//protected:
//    Noble* boss;
//};
//Protector::Protector(const string& name, int strength) : name(name),
//strength(strength), employed(false), boss(nullptr) {}
//
//bool Protector::isHired() const{
//    return employed;
//}
//
//const string& Protector::getName() const {
//    return name;
//}
//
//
//bool Protector::setBoss(Noble* noble) {
//    if (!employed && noble != nullptr) {
//        boss = noble;
//        employed = true;
//        return true;
//    }
//    else if (employed && noble == nullptr) {
//        boss = noble;
//        employed = false;
//        return true;
//    }
//    return false;
//}
//
//bool Protector::employement(bool status) {
//    if (employed && !status) {
//        employed = false;
//        return true;
//    }
//    else if (!employed && status) {
//        employed = true;
//        return true;
//    }
//    return false;
//}
//
//int Protector::getStrength() const {
//    return strength;
//}
//
//void Protector::setStrength(int val) {
//    strength = val;
//}

//class Wizard : public Protector {
//public:
//    Wizard(const string& name, int strength);
//    int getStrength() const;
//    void setStrength(int val);
//};

//Wizard::Wizard(const string& name, int strength) : Protector(name, strength) {}
//void Wizard::setStrength(int val) {
//    cout << "POOF!\n";
//    Protector::setStrength(val);
//}
//
//int Wizard::getStrength() const {
//    return Protector::getStrength();
//}

//class Warrior : public Protector {
//public:
//    Warrior(const string& name, int strength);
//    int getStrength() const;
//};
//Warrior::Warrior(const string& name, int strength) : Protector(name, strength) {}
//int Warrior::getStrength() const {
//    return Protector::getStrength();
//}
//
//class Archer : public Warrior {
//public:
//    Archer(const string& name, int strength);
//    void setStrength(int val);
//};

//Archer::Archer(const string& name, int strength) : Warrior(name, strength) {}
//void Archer::setStrength(int val) {
//    cout << "TWANG! " << getName() << " says: Take that in the name of my lord, \n";
//    //<< boss->getName() << endl;
//}

//class Swordsman : public Warrior {
//public:
//    Swordsman(const string& name, int strength);
//    void setStrength(int val);
//};

//Swordsman::Swordsman(const string& name, int strength) : Warrior(name, strength) {}
//void Swordsman::setStrength(int val) {
//    cout << "CLANG! " << getName() << " says: Take that in the name of my lord, \n";
//    //<< boss->getName() << endl;
//}

//class Noble {
//public:
//    Noble(string name) : name(name), life(true) {}
//    virtual void battle(Noble& noble) = 0;
//    virtual int strength() const = 0;
//    virtual void setStrength(double val, bool ratio = false) = 0;
//private:
//    bool life;
//protected:
//    string name;
//};

//void Noble:: battle(Noble& theNoble) {
//    cout << name << " battles " << theNoble.name << endl;
//    //If they are both dead, the error message is printed.
//    if (!life && !theNoble.life) {
//        cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
//    }
//    //If their strengths are equivalent, then they both die at each other's hands.
//    else if (strength() == theNoble.strength()) {
//        setStrength(0);
//        theNoble.setStrength(0);
//        life = false;
//        theNoble.life = false;
//        cout << "Mutual Annhilation: " << name << " and " << theNoble.name << " die at each other's hands!" << endl;
//    }
//    //If the current noble is dead, then it tells the other Noble that they are dead.
//    else if (!life) {
//        theNoble.setStrength(theNoble.strength());
//        cout << "He's dead, " << theNoble.name << "." << endl;
//    }
//    //If the other noble is dead, then it tells the current Noble then they are dead.
//    else if (!theNoble.life) {
//        setStrength(strength());
//        cout << "He's dead, " << name << "." << endl;
//    }
//    //If the other Noble's strength is greater than the current Noble, then they battle accordingly.
//    //The current Noble dies.
//    else if (theNoble.strength() > strength()) {
//        double ratio = (1.0*theNoble.strength()/strength());
//        life = false;
//        setStrength(0);
//        theNoble.setStrength(ratio, true);
//        cout << theNoble.name << " defeats " << name << endl;
//    }
//    //If the current Noble's strength is greater than the other Noble, then they battle accordingly.
//    //The other Noble dies.
//    else if (theNoble.strength() < strength()) {
//        double ratio = 1.0*theNoble.strength()/strength();
//        theNoble.life = false;
//        setStrength(ratio, true);
//        theNoble.setStrength(0);
//        cout << name << " defeats " << theNoble.name << endl;
//    }
//}

//class Lord : public Noble {
//public:
//    Lord(string name);
//    void battle(Noble& noble);
//    int strength() const;
//    void setStrength(double val, bool ratio);
//    bool hires(Protector& protector);
//    bool fires(Protector& protector);
//    
//private:
//    vector<Protector*> army;
//};

//Lord::Lord(string name) : Noble(name) {}
//void Lord::battle(Noble& noble) {
//    Noble::battle(noble);
//}
//
//int Lord::strength() const{
//    int strength = 0;
//    for(const Protector* protect : army) {
//        strength += protect->getStrength();
//    }
//    return strength;
//}
//
//void Lord::setStrength(double val, bool ratio) {
//    for(Protector* protect : army) {
//        if (ratio) {
//            double reduc = protect->getStrength()*val;
//            protect->setStrength(protect->getStrength() -
//                                     reduc);
//        }
//        else {
//            protect->setStrength(val);
//        }
//    }
//}
//
//bool Lord::hires(Protector& protector) {
//    if (!protector.isHired()) {
//        army.push_back(&protector);
//        protector.setBoss(this);
//        protector.employement(true);
//        return true;
//    }
//    cout << "error: noble " << name << " is attempting to hire protector "
//    << protector.getName() << " who is already employed.\n";
//    return false;
//}
//
//bool Lord::fires(Protector& protector) {
//    if (protector.isHired()) {
//        for(size_t i = 0; i < army.size(); ++i) {
//            if (army[i] == &protector) {
//                protector.employement(false);
//                cout << "You dont work for me anymore " <<
//                protector.getName() << "! -- " << name << "." << endl;
//                while (i < (army.size() - 1)) {
//                    swap(army[i], army[i + 1]);
//                }
//                army.pop_back();
//                protector.setBoss(nullptr);
//                return true;
//            }
//        }
//        cout << "error: noble " << name << " is attempting to fire warrior " << protector.getName()
//        << " but this warrior doesn't work for him!\n";
//    }
//    cout << "error: noble " << name << " is attempting to fire warrior " << protector.getName()
//    << " but he doesn't work for him and he wasn't employed to begin with!\n";
//    return false;
//}

//class PersonWithStrengthToFight : public Noble {
//public:
//    PersonWithStrengthToFight(const string& name, int strength);
//    void battle(Noble& noble);
//    int strength() const;
//    void setStrength(double val, bool ratio = false);
//private:
//    int stren;
//};

//PersonWithStrengthToFight::PersonWithStrengthToFight(const string& name, int strength) : Noble(name), stren(strength) {}
//
//void PersonWithStrengthToFight::battle(Noble& noble) {
//    Noble::battle(noble);
//}
//int PersonWithStrengthToFight::strength() const {
//    return stren;
//}
//
//void PersonWithStrengthToFight::setStrength(double val, bool ratio) {
//    cout << "UGH!\n";
//    if (ratio) {
//        double reduc = stren*val;
//        stren = stren - reduc;
//    }
//    else {
//        stren = val;
//    }
//}

int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250);
    joe.battle(randy);
    joe.battle(sam);
    Lord janet("Janet");
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);
    janet.hires(stout);
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);
    janet.battle(barclay);
    janet.hires(samantha);
    Archer pethora("Pethora", 50);
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);
    janet.hires(thora);
    sam.hires(merlin);
    janet.battle(barclay);
    sam.battle(barclay);
    joe.battle(barclay);
}


