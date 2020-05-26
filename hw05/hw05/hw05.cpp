//Hellen Ekpo
//CS 2124
//Homework 5

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
//This program is going to simulate Nobles battling, and they battle with the warriors within their armies.
class Warrior {
    //the output stream for the warrior, defined outside of the class.
    friend ostream& operator << (ostream& os, const Warrior& theWarrior);
public:
    //the constructor/initialization list, initialized the warrior with its name and strength,
    // and sets the employment status automatically to false.
    Warrior(const string& name, int strength) : name(name), strength(strength),
    employed(false) {}
    //the methods getname, getstrength, and ishired are all getters, returning the warriors
    //private fields. marked constant to prevent modification
    const string& getName() const {
        return name;
    }
    int getStrength() const {
        return strength;
    }
    bool isHired() const {
        return employed;
    }
    // the methods fire and hire check if the warrior is already hired or unemployed respectively.
    // if so, the apporopriate change will occur. if not, then the change fails.
    bool employement(bool status) {
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
    //this method sets the strength of the warrior
    void setStrength(int val) {
        strength = val;
    }
private:
    string name;
    double strength;
    bool employed;
};

class Noble {
    //the output operator, defined outside of the class.
    friend ostream& operator << (ostream& os, const Noble& theNoble);
public:
    //the constructor, initializes the name and sets life to truw
    Noble(const string& name) : name(name), life(true) {}
    
    void battle(Noble& theNoble) {
        //nobles can delcare war even if they are dead so dont check for life status
        cout << name << " battles " << theNoble.name << endl;
        //if both of the Nobles involved are dead, then it prints...
        if (!life && !theNoble.life) {
            cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
        }
        //if both of the Nobles strengths are equal to one another, their strengths are set to 0
        //which sets all of the warriors strength to 0. Both of their lives are now false, and its prints..
        //that they die at each others hands
        else if (strength() == theNoble.strength()) {
            setStrength(0);
            theNoble.setStrength(0);
            life = false;
            theNoble.life = false;
            cout << "Mutual Annhilation: " << name << " and " << theNoble.name << " die at each other's hands!" << endl;
        }
        //if the initial Noble is dead then it tells the other Noble that he is dead
        else if (!life) {
            cout << "He's dead, " << theNoble.name << "." << endl;
        }
        //If the other Noble is dead, then it tells the initial Noble that he is dead.
        
        else if (!theNoble.life) {
            cout << "He's dead, " << name << "." << endl;
        }
        //If the other Noble strength is greater than the initial Noble
        else if (theNoble.strength() > strength()) {

            cout << theNoble.name << " defeats " << name << endl;
            //the other noble's army strength deducts by the ratio, the initial Noble dies and
            //its army strength is set to 0.
            double ratio = (1.0 - theNoble.strength()/strength());
            life = false;
            theNoble.setStrength(ratio, true);
            theNoble.setStrength(0);
        }
        else if (theNoble.strength() < strength()) {
        //If the initial strength is greater than the other noble's strength
            cout << name << " defeats " << theNoble.name << endl;
            //the inital noble's army strength deducts by the ratio, the other Noble dies, and it's
            //armys strength is set to 0.
            double ratio = 1.0*theNoble.strength()/strength();
            theNoble.life = false;
            theNoble.setStrength(0);
            setStrength(ratio, true);
        }
    }
    
    //The strength method of the Noble depends on the sum of all the warriors in his army.
    //The method iterates through the army, adds up the strength, and returns it.
    int strength() const{
        int strength = 0;
        for(const Warrior* warrior : army) {
            strength += warrior->getStrength();
        }
        return strength;
    }
    //The setStrength method takes in a val, and a parameter to check if the value is a ratio or not.
    //If the value is not a ratio, it will just set all of the warriors strength to the value.
    //If the value is a ratio, it will deduct all of the warriors strength by the ratio.
    void setStrength(double val, bool ratio = false) {
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
    //this getter returns the name, marked constant to prevent modification and passed by reference
    //to prevent making a copy
    const string& getName() const {
        return name;
    }
    //the hire method checks if the warrior is unemployed. if so then the hire is successful
    //however if the wariror is already hired it fails
    bool hire(Warrior& warrior) {
        if (!warrior.isHired()) {
            army.push_back(&warrior);
            warrior.employement(true);
            return true;
        }
        cout << "error: noble " << name << " is attempting to hire warrior "
        << warrior.getName() << " who is already employed.\n";
        return false;
    }
    //the fire method checks if the warrior is hired, and then it checks if the warrior
    //is in the noble's army. if the warrior is in the army it fires the warrior swaps it
    //to the back of the army vector, and removes him from the army.
    bool fire(Warrior& warrior) {
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
private:
    string name;
    vector<Warrior*> army;
    bool life;
};
//the openFile function attempts to open the file "nobleWarriors.txt" if the stream to the file is
//unsucessful, then the program ends immediately.
void openFile(ifstream& ifs);
//the reads command function reads commands from the file stream and does the appropriate
//command.
void readCommands(ifstream& ifs, vector<Noble*>& nobles, vector<Warrior*>& warriors);

//the output operator for the warrior allows for the warror name and strength to be printed everytime a
//warrior is printed.
ostream& operator << (ostream& os, const Warrior& theWarrior) {
    os << "  -->" << theWarrior.name << ": " << theWarrior.strength;
    return os;
}
//the output operator for the noble allows for the noble's name, sizde of army, and warriors in
//the army to be printed accordingly.
ostream& operator << (ostream& os, const Noble& theNoble) {
    os << theNoble.name << " has an army of: " << theNoble.army.size() << endl;
    for (const Warrior* warrior : theNoble.army) {
        os << *warrior;
        os << endl;
    }
    return os;
}

int main() {
    ifstream ifs;
    vector<Noble*> nobles;
    vector<Warrior*> warriors;
    readCommands(ifs, nobles, warriors);
}
//this helper function is for hiring and firing. if the the command is hire it hires the warrior
//to the the appropriate nobles army, if the warrior is initially unemployed.
//it also fires the warrior from the appropriate nobles army if the warrior worked for the noble.
//there are booleans to check if these nobles and warriors exist, and if they do, they are changed
//to true. however, if one, the other, or both are false, then the appropriate error message is printed.
bool hireFire(const string& command, ifstream& ifs,
              vector<Noble*>& nobles, vector<Warrior*>& warriors) {
    string nobeName, warName;
    ifs >> nobeName >> warName;
    if (command == "Hire") {
        for (Noble* noble : nobles) {
            if (noble->getName() == nobeName) {
                for (Warrior* warrior : warriors) {
                    if (warrior->getName() == warName) {
                        noble->hire(*warrior);
                        return true;
                    }
                }
                cout << "error: noble " << nobeName << " is attempting to hire an unknown warrior "
                << warName << ".\n";
                return false;
            }
        }
        cout << "error: noble " << nobeName << " does not exist!\n";
    }
    else if (command == "Fire" ) {
        for(Noble* noble : nobles) {
            if (noble->getName() == nobeName) {
                for(Warrior* warrior : warriors) {
                    if (warrior->getName() == warName) {
                        noble->fire(*warrior);
                        return true;
                    }
                }
                cout << "error: noble " << nobeName << " is attempting to fire an unknown warrior " <<
                warName << ".\n";
                return false;
            }
        }
        cout << "error: noble " << nobeName << " does not exist!\n";
    }

    return false;
}
//this helper function prints the status of the nobles and the warriors in their army.
//it also prints the unemployed warriors if any. if not, the unemployed warriors section
//will state NONE; likewise for the nobles.
void printStatus(const vector<Noble*>& nobles, const vector<Warrior*>& warriors) {
    cout << "Status\n=======\nNobles:\n";
    if (nobles.size() == 0) {
        cout << "NONE!\n";
    }
    else {
        for(const Noble* noble : nobles) {
            cout << *noble;
        }
    }
    cout << "Unemployed Warriors:\n";
    bool unemployment = false;
    for (const Warrior* warrior : warriors) {
        if (!warrior->isHired()) {
            unemployment = true;
            cout << *warrior << endl;
        }
    }
    if (!unemployment) cout << "NONE!\n";
}
//this helper functions adds a warrior or noble to the army, it depends on the command.
//it iterates through the vector of warrior pointers and the vector of noble pointers and checks
//if there is a warrior or noble with the same name. if so, the function returns false and the add fails
//else, the add is successful and eventually returns true. the warriors and nobles are allocated on the heap.
bool addNobleWarrior(const string& command, ifstream& ifs,
                     vector<Noble*>& nobles, vector<Warrior*>& warriors) {
    string name;
    int strength;
    ifs >> name;
    if (command == "Noble") {
        //Check for error: 1
        for (const Noble* noble : nobles) {
            if (noble->getName() == name) {
                cout << "This noble already exist!\n";
                return false;
            }
        }
        Noble* noble = new Noble(name);
        nobles.push_back(noble);
        
    }
    else if (command == "Warrior") {
        //Check for error: 2
        for (const Warrior* warrior : warriors) {
            if (warrior->getName() == name ) {
                cout << "This warrior already exist!\n";
                return false;
            }
        }
        ifs >> strength;
        Warrior* warrior = new Warrior(name, strength);
        warriors.push_back(warrior);
    }
    return true;
}
//this the helper function for the battle, it reads in the two nobles name, and iterates through
//the vectors to find the index of these nobles. if they are found, meaning when the names match up
//the indices are set accordingly. the two indices are initialized to the size of the vector to
//signify the noble hasnt been found yet. if one or both of the indices are equal to the size of the
//nobles vector, the appropriate message is printed to state that one or both nobles havent been found.
//if they are both found, then they battle normally

bool battle(ifstream& ifs, vector<Noble*>& nobles) {
    string nobeName1, nobeName2;
    size_t noble_1 = nobles.size(), noble_2 = nobles.size();
    ifs >> nobeName1 >> nobeName2;
    for(size_t i = 0; i < nobles.size(); ++i) {
        if (nobles[i]->getName() == nobeName1) {
            noble_1 = i;

        }
        else if (nobles[i]->getName() == nobeName2) {
            noble_2 = i;
        }
    }
    if (noble_1 && noble_2 == nobles.size()) {
        cout << "These two nobles don't exist!\n";
        return false;
    }
    else if (noble_1 == nobles.size()) {
        cout << nobeName1 << " does not exist!\n";
        return false;
    }
    else if (noble_1 == nobles.size()) {
        cout << nobeName2 << " does not exist!\n";
        return false;
    }
    nobles[noble_1]->battle(*(nobles[noble_2]));
    return true;
}

// the readCommands function reads commands from the filestream and does the appropriate command
//the clear function doesn't have a helper so: it removes all of the warriors and nobles from the heap.
//then it sets all the dangling pointers to nullptrs so they arent pointers to garbage values.
//then both vectors are cleared.
void readCommands(ifstream& ifs, vector<Noble*>& nobles, vector<Warrior*>& warriors) {
    string command;
    openFile(ifs);
    while (ifs >> command) {
        if (command == "Noble") {
            addNobleWarrior(command, ifs, nobles, warriors);
        }
        else if (command == "Warrior") {
            addNobleWarrior(command, ifs, nobles, warriors);
        }
        else if (command == "Hire") {
            hireFire(command, ifs, nobles, warriors);
        }
        else if (command == "Fire" ) {
            hireFire(command, ifs, nobles, warriors);
        }
        else if (command == "Status" ) {
            printStatus(nobles, warriors);
        }
        else if (command == "Battle" ) {
            battle(ifs, nobles);
        }
        else if (command == "Clear") {
            for(Warrior* warrior : warriors) {
                delete warrior;
                warrior = nullptr;
            }
            for(Noble* noble : nobles) {
                delete noble;
                noble = nullptr;
            }
            nobles.clear();
            warriors.clear();
        }
    }
    ifs.close();
}
//the openFile function initalizes the filestream to the nobleWarriors.txt file. if the
//filestream isn't initialized properly, then it closes the program immediately and prints
//the error message.
void openFile(ifstream& ifs) {
    ifs.open("nobleWarriors.txt");
    if (!ifs) {
        cerr << "Couldn't open the file!!\n";
    }
}


