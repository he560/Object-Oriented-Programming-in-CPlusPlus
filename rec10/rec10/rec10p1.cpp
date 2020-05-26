//Hellen Ekpo
//Rec 10
//April 10th, 2020


#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Instrument {
public:
    virtual void makeSound() const = 0;
private:
    
};
void Instrument:: makeSound() const {
    cout << "To make a sound...";
}
class Brass : public Instrument {
public:
    Brass(unsigned size) : mouthpieceSize(size){}
    void makeSound() const {
        Instrument::makeSound();
        cout << "blow on a mouthpiece of size " << mouthpieceSize << endl;
    }
private:
    unsigned mouthpieceSize;
};

class Trombone : public Brass {
public:
    Trombone(unsigned size) : Brass(size) {}
};

class Trumpet : public Brass {
public:
    Trumpet(unsigned size) : Brass(size) {}
};

class String : public Instrument {
public:
    String(unsigned level) : pitch(level) {}
public:
    void makeSound() const {
        Instrument::makeSound();
        cout << "bow on a string with pitch " << pitch << endl;
    }
private:
    unsigned pitch;
};

class Cello : public String {
public:
    Cello(unsigned level) : String(level) {}
};

class Violin : public String {
public:
    Violin(unsigned level) : String(level) {}
};

class Percussion : public Instrument {
public:
    void makeSound() const {
        Instrument::makeSound();
        cout << "hit me!\n";
    }
};

class Drum : public Percussion {
};

class Cymbal : public Percussion {
};

class Musician {
public:
    Musician() : instr(nullptr) {}

    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }

    void testPlay() const {
        if (instr) instr->makeSound();
        else cerr << "have no instr\n";
    }

private:
    Instrument* instr;
};

class MILL {
public:
    void receiveInstr(Instrument& instru) {
        instru.makeSound();
        bool space = false;
        for (size_t i = 0; i < inventory.size(); ++i) {
            if (inventory[i] == nullptr) {
                inventory[i] = &instru;
                space = true;
                break;
            }
        }
        if (!space) inventory.push_back(&instru);
    }
    Instrument* loanOut() {
        for (size_t i = 0; i < inventory.size(); ++i) {
            if (inventory[i] != nullptr) {
                Instrument* address = inventory[i];
                inventory[i] = nullptr;
                return address;
            }
        }
        return nullptr;
    }
    void dailyTestPlay() {
        for (Instrument* instru : inventory) {
            if (instru != nullptr) instru->makeSound();
        }
    }
private:
    vector<Instrument*> inventory;
};


int main() {

    // cout << "Define some instruments ------------------------------------\n";
     Drum drum;
     Cello cello(673);
     Cymbal cymbal;
     Trombone tbone(4);
     Trumpet trpt(12) ;
     Violin violin(567) ;

     // use the debugger to look at the mill
     cout << "Define the MILL --------------------------------------------\n";
     MILL mill;

     cout << "Put the instruments into the MILL --------------------------\n";
     mill.receiveInstr(trpt);
     mill.receiveInstr(violin);
     mill.receiveInstr(tbone);
     mill.receiveInstr(drum);
     mill.receiveInstr(cello);
     mill.receiveInstr(cymbal);

     cout << "Daily test -------------------------------------------------\n";
     cout << endl;
     cout << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();
     cout << endl;

     cout << "Define some Musicians---------------------------------------\n";
     Musician harpo;
     Musician groucho;

     cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
     groucho.testPlay();
     cout << endl;
     groucho.acceptInstr(mill.loanOut());
     cout << endl;
     groucho.testPlay();
     cout << endl;
     cout << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();

     cout << endl << endl;

     groucho.testPlay();
     cout << endl;
     mill.receiveInstr(*groucho.giveBackInstr());
     harpo.acceptInstr(mill.loanOut());
     groucho.acceptInstr(mill.loanOut());
     cout << endl;
     groucho.testPlay();
     cout << endl;
     harpo.testPlay();
     cout << endl;
     cout << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();

     cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";

     // fifth
     mill.receiveInstr(*groucho.giveBackInstr());
     cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
     mill.receiveInstr(*harpo.giveBackInstr());


     cout << endl;
     cout << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();
     cout << endl;

     cout << endl;
}
