#include <string>
#include <iostream>
#include <vector>
//This program simulates Nobles battling, the Nobles have warriors to battle for them, and these Nobles
//hire and fire warriors. If all of the warriors lose their strength, then the Noble is declared dead.
using namespace std;

class Warrior {
    //the output operator, which is defined outside of the class.
    friend ostream& operator << (ostream& os, const Warrior& theWarrior);
public:
    //The constructor, takes the name and strength of the warrior and sets the appropriate fields.
    //The employed field is automatically initilized to false once a warrior is created.
    Warrior(const string& name, int strength) : name(name), strength(strength), employed(false)
    {}
    //this method returns a bool regarding the status of employment. it is marked const to prevent
    //modification
    bool isHired() const{
        return employed;
    }
    //this method is called when a warrior is attempting to get hired. it will fail if the
    //warrior is already employed, but if the warrior isnt employed, it will be abled to become hired
    bool hire() {
        if (!employed) {
            employed = true;
            return true;
        }
        return false;
    }
    //this method is like the hire method, it will only fire the warrior if it is employed. if not, the
    //warrior will not be fired cause it wasn't employed to begin with. Nobles cannot fire warriors that
    //are not in his army.
    bool fire() {
        if (employed) {
            employed = false;
            return true;
        }
        return false;
    }
    //method returns the strength of the warrior, marked const to prevent modification
    int warStren() const {
        return strength;
    }
    //method sets the strength of the warrior/
    void setStrength(int val) {
        strength = val;
    }
    //method gets the name of the warrior, marked const to prevent modifications
    string getName() const {
        return name;
    }
    
    
private:
    string name;
    int strength;
    bool employed;
};
//The output operator, which will allow for warriors to be printed with their name and strength.
ostream& operator << (ostream& os, const Warrior& theWarrior) {
    os << theWarrior.name << ": " << theWarrior.strength;
    return os;
}


class Noble {
    //The output operator, which is defined outside of the class.
    friend ostream& operator << (ostream& os, const Noble& theNoble);
public:
    //The constructor, which initlizes the Nobles name, and his life as true.
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
    int strength() {
        int strength = 0;
        for(Warrior* warrior : army) {
            strength += warrior->warStren();
        }
        return strength;
    }
    //The setStrength method takes in a val, and a parameter to check if the value is a ratio or not.
    //If the value is not a ratio, it will just set all of the warriors strength to the value.
    //If the value is a ratio, it will deduct all of the warriors strength by the ratio.
    void setStrength(double val, bool ratio = false) {
        for(Warrior* warrior : army) {
            if (ratio) {
                double reduc = warrior->warStren()*val;
                warrior->setStrength(warrior->warStren() -
                                     reduc);
            }
            else {
                warrior->setStrength(val);
            }
        }
    }
    //the hire method takes a warrior and adds it to its army. A noble is only able to add a warrior to his
    //army if its alive, and if the warrior is able to be hired. else, false.
    bool hire(Warrior& theWarrior) {
        if (life && theWarrior.hire()) {
            army.push_back(&theWarrior);
            return true;
        }
        return false;
    }
    //the fire method iterates through the Nobles army and checks if the warriors address is the same
    //as the address of the warrior passed in the parameter. if it matches, then the warrior is fired
    //and the respective message is printed. it swaps the warrior to the back of the army in a while loop,
    //and it removed the warrior from the army. this is successful, so it returns true.
    //else, it prints that the specific warrior doesn't work for the noble, so the noble cannot fire him.
    //returns false cause its unsucessful.
    bool fire(Warrior& theWarrior) {
        if (life && theWarrior.isHired()) {
            for(size_t i = 0; i < army.size(); ++i) {
                if (army[i] == &theWarrior) {
                    theWarrior.fire();
                    cout << "You dont work for me anymore " << theWarrior.getName() << "! -- " << name << "." << endl;
                    while (i < (army.size() - 1)) {
                        swap(army[i], army[i + 1]);
                    }
                    army.pop_back();
                    return true;
                }
            }
        }
        cout << "You don't work for this Noble so he can't fire you." << endl;
        return false;
    }
private:
    string name;
    vector<Warrior*> army;
    bool life;
};
//The ostream operator for the Noble allows for the Noble's name, army size, and all the warriors in his
//army to be printed. Since the army is a army of warrior pointers, they warriors are dereferenced.
ostream& operator << (ostream& os, const Noble& theNoble) {
    os << theNoble.name << " has an army of " << theNoble.army.size() << "\n";
    for (Warrior* warrior : theNoble.army) {
        os << *warrior << " ";
    }
    return os;
}


int main() {
    
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
    
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
    
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    
    cout << "==========\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";
    
    art.fire(cheetah);
    cout << art << endl;
    
    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";
    
}
