//Hellen Ekpo
//Rec 10
//April 10th, 2020


#include <iostream>
#include <vector>
using namespace std;

class Instrument {
public:
    virtual void makeSound() const = 0;
    virtual void play() const = 0;
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
    void play() const {
        cout << "Blat.";
    }
};

class Trumpet : public Brass {
public:
    Trumpet(unsigned size) : Brass(size) {}
    void play() const {
        cout << "Toot.";
    }
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
    void play() const {
        cout << "Squawk.";
    }
};

class Violin : public String {
public:
    Violin(unsigned level) : String(level) {}
    void play() const {
        cout << "Screech.";
    }
};

class Percussion : public Instrument {
public:
    void makeSound() const {
        Instrument::makeSound();
        cout << "hit me!\n";
    }
};

class Drum : public Percussion {
public:
    void play() const {
        cout << "Boom.";
    }
};

class Cymbal : public Percussion {
public:
    void play() const {
        cout << "Crash.";
    }
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
    
    void play() const {
        if (instr) instr->play();

    }

private:
    Instrument* instr;
};

class MILL {
public:
    void receiveInstr(Instrument& instru) {
        //bool space = false;
        for (size_t i = 0; i < inventory.size(); ++i) {
            if (inventory[i] == nullptr) {
                inventory[i] = &instru;
                return;
                //space = true;
                //break;
            }
        }
        //if (!space)
        inventory.push_back(&instru);
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
    void dailyTestPlay() const{
        for (Instrument* instru : inventory) {
            if (instru != nullptr) instru->makeSound();
        }
    }
private:
    vector<Instrument*> inventory;
};

class Orch {
public:
    bool addPlayer(Musician& musician) {
        for (const Musician* musc: band) {
            if (musc == &musician) return false;
        }
        band.push_back(&musician);
        return true;
    }
    
    void play() const{
        for (const Musician* musc: band) {
            musc->play();
        }
        cout << endl;
    }
private:
    vector<Musician*> band;
};

int main() {
    // The initialization phase

    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12);
    Violin violin(567);

    MILL mill;
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);

    Musician bob;
    Musician sue;
    Musician mary;
    Musician ralph;
    Musician jody;
    Musician morgan;

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

} // main
