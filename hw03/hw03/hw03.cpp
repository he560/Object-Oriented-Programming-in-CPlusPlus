//Hellen Ekpo
//CS 2124
//2/10/2019

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Warrior {
    //The output operator, it is defined outside of the class
    friend ostream& operator<<(ostream& os, const Warrior& theWarrior);
public:
    //The constructor for a Warrior takes a name, weapon name, and its strength
    //This initializes the warrior with its name, and the weapon with its name
    //and strength
    Warrior(const string& name, const string& weapName, int strength) :
    name(name), weapon(weapName, strength) {}
    void battle(Warrior& otherWarrior) {
        //the battle function is very similar to previous. it prints the two
        //warriors that are battling first.
        cout << name << " battles " << otherWarrior.name << endl;
        // it checks if the initial warriors strength is greater than
        // the other.
         if (weapon.getStrength() > otherWarrior.weapon.getStrength()) {
             //then it checks if the other warriors strength is 0
             //and if it is the other warriors dead
             if (otherWarrior.weapon.getStrength() == 0) {
                 cout << "He's dead, " << name << endl;
             }
             else {
                 //else the initial warrior defeats the other warrior
                 //and the strength deducts accordingly.
                 cout << name << " defeats " << otherWarrior.name << endl;
                 int newStren = weapon.getStrength();
                 newStren -= otherWarrior.weapon.getStrength();
                 weapon.setStrength(newStren);
                 otherWarrior.weapon.setStrength(0);
             }
         }
        //it checks if the other warriors strength is greather than the
        //initial warrior
         else if (weapon.getStrength() < otherWarrior.weapon.getStrength()) {
             if (weapon.getStrength() == 0) {
                 // if the initial warriors strength is 0 then it
                 // tells the other warrior that the initial is dead.
                 cout << "He's dead, " << otherWarrior.name << endl;
             }
             else {
                 //else the other warrior defeats the initial warrior and the
                 //strengths deduct accordingly.
                 cout << otherWarrior.name << " defeats " << name << endl;
                 int newStren = otherWarrior.weapon.getStrength();
                 newStren -= weapon.getStrength();
                 otherWarrior.weapon.setStrength(newStren);
                 weapon.setStrength(0);
             }
         }
        //if their strengths are the same, then it checks if they are already 0
        //if thats the case they are both dead.
         else if (weapon.getStrength() == otherWarrior.weapon.getStrength()) {
             if (weapon.getStrength() ==  0) {
                 cout << "Oh, NO! They're both dead! YUCK!\n";
             }
             //else they die at each others hands and their strength both get set to 0
             else {
                 cout << "Mutual Annihilation: " << name << " and " <<
                 otherWarrior.name << " die at each others hands!\n";
             }
             weapon.setStrength(0);
             otherWarrior.weapon.setStrength(0);
         }
    }
    //This method returns the name of the warrior, and is marked constant
    //To prevent both the function and the returned string from being modified
    const string& getName() const{
        return name;
    }
private:
    //The weapon is apart of the private member of the warrior class, meaning only
    //warriors know what a weapon is. The output operator is implemented so that
    //when weapons are printed, it prints its name along with its strength.
    class Weapon {
        friend ostream& operator<<(ostream& os, const Weapon& theWeapon) {
            os << theWeapon.name << ", " << theWeapon.strength;
            return os;
        }
    public:
        //The constructor of a weapon takes in its name and strength, and it
        //initializes the weapons private fields
        Weapon(const string& name, int strength) : name(name), strength(strength) {}
        int getStrength() const{
            return strength;
        }
        void setStrength(int val) {
            strength = val;
        }
        //the two mthods for the warrior is getstrength and setstrength which gets and
        //sets the strength of the warrior. the get strength is marked constant to prevent
        //modification
    private:
        string name;
        int strength;
    };
    string name;
    Weapon weapon;
};

//The open function takes a filestream and attemps to open the filestream to the "warrior.txt" file.
// checks if its opened properly. if not it wil cclose the program immediately and clear
// the filestream
void open(ifstream& ifs);

//The readsCommands function takes the filestream, and the vector of warriors. it will read
//commands from the file and do the commands respectively. if the command is warrior, its
//creates a warrior and adds it to the vector of warriors, if it is battle, it makes the two
// following warriors battle, if its status then it will print the status of all warriors in
//the vector
void readCommands(ifstream& ifs, vector<Warrior>& warriors);

//this is a helper function which simply adds a warrior initilized with name, weapName,
//and  weapon strength to the vector of warriors.
void addWarriors(ifstream& ifs, vector<Warrior>& warriors);

//this is another helper function which takes the name of the two warriors battling.
//they will battle.
void battleWarriors(ifstream& ifs, vector<Warrior>& warriors);

int main() {
    ifstream ifs;
    vector<Warrior> warriors;
    readCommands(ifs, warriors);
    
}

void open(ifstream& ifs) {
    ifs.open("warriors.txt");
    if (!ifs) {
        cerr << "Couldn't open the file!\n";
        ifs.clear();
    }
}

void battleWarriors(ifstream& ifs, vector<Warrior>& warriors) {
    string warName1, warName2;
    ifs >> warName1 >> warName2;
    size_t war1 = warriors.size();
    size_t war2 = warriors.size();
    for(size_t i = 0; i < warriors.size(); ++i) {
        if (warriors[i].getName() == warName1) {
            war1 = i;
        }
        else if (warriors[i].getName() == warName2) {
            war2 = i;
        }
    }
    warriors[war1].battle(warriors[war2]);
}

void addWarriors(ifstream& ifs, vector<Warrior>& warriors) {
    string name, weapName;
    int strength;
    ifs >> name >> weapName >> strength;
    Warrior warrior(name, weapName, strength);
    warriors.push_back(warrior);
}

void readCommands(ifstream& ifs, vector<Warrior>& warriors) {
    open(ifs);
    string command;
    while (ifs >> command) {
        if (command == "Warrior") {
            addWarriors(ifs, warriors);
        }
        else if (command == "Battle") {
            battleWarriors(ifs, warriors);
        }
        else if (command ==  "Status") {
            cout << "There are " << warriors.size() << " warriors\n";
            for (const Warrior& warrior : warriors) {
                cout << warrior << endl;
            }
        }
    }
    ifs.close();
}
//The ostream operator for the warrior class is implemented so that when a warrior
//is printed, it will print the  warriors name, and the  weapons name and strength,
//according to the ostream operator implemented by the weapon class
ostream& operator<<(ostream& os, const Warrior& theWarrior) {
    os << "Warrior: " << theWarrior.name << ", weapon: " << theWarrior.weapon;
    return os;
}
