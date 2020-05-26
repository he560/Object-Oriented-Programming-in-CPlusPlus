//Hellen Ekpo
//Recitation 4
//CS  2124
//2/21/2020

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Complex {
   double real;
   double img;
};

class SpeakerSystem {
   public:
   void vibrateSpeakerCones(unsigned signal) const {

      cout << "Playing: " << signal << "Hz sound..." << endl;
      cout << "Buzz, buzzy, buzzer, bzap!!!\n";
   }
};

class Amplifier {
public:
  void attachSpeakers(const SpeakerSystem& spkrs)
   {
      if(attachedSpeakers)
         cout << "already have speakers attached!\n";
      else
          attachedSpeakers = &spkrs;
   }
  
   void detachSpeakers() { // should there be an "error" message if not attached?
      attachedSpeakers = nullptr;
   }
  
   void playMusic( ) const {
      if (attachedSpeakers)
         attachedSpeakers -> vibrateSpeakerCones(440);
      else
         cout << "No speakers attached\n";
   }
private:
   const SpeakerSystem* attachedSpeakers = nullptr;
};
class Colour {
public:
    Colour(const string& name, unsigned r, unsigned g, unsigned b)
        : name(name), r(r), g(g), b(b) {}
    void display() const {
        cout << name << " (RBG: " << r << "," << g<< "," << b << ")";
    }
private:
    string name;      // what we call this colour
    unsigned r, g, b; // red/green/blue values for displaying
};


class PlainOldClass {
public:
   PlainOldClass() : x(-72) {}
   int getX() const { return x; }
   void setX( int val )  { x = val; }
private:
   int x;
};

class PlainOldClassV2 {
public:
   PlainOldClassV2() : x(-72) {}
   int getX() const { return x; }
   void setX( int x )  { this->x = x; } // HMMMM???
private:
   int x;
};

class Person {
public:
    Person(const string& name) : name(name) {}
    bool movesInWith(Person& newRoomate) {
        if (roomie) {
            cout << name << " already has a roommate! Their name is: "
            << getRoomiesName();
            return false;
        }
        else if (newRoomate.roomie) {
            cout << newRoomate.name << " already has a roomate! Their name is: "
            << newRoomate.roomie->name;
            return false;
        }
        else if (&newRoomate == this) {
            cout << "You can't be your own roommate!\n";
            return false;
        }
        roomie = &newRoomate;        // now I have a new roomie
        newRoomate.roomie = this;    // and now they do too
        return true;
    }
    const string& getName() const { return name; }
    // Don't need to use getName() below, just there for you to use in debugging.
    const string& getRoomiesName() const { return roomie->getName(); }
private:
    Person* roomie = nullptr;
    string name;
};



int main() {
    int x;
    x = 10;
    cout << "x = " << x << endl;
    cout << &x << endl;
    // cout << 0xB << endl;
    // cout << hex << 0xB << endl;
    // cout << oct << 0x10 << endl;
    int* p;
    p = &x;
    //p = 0x7ffeefbff56c; //assigning in from incompatible type long
    cout << "p = " << p << endl << endl;
    //p is a pointer pointing to the address of the location x.
    //if you dereference p, which is the address of x, you will get x which is 10
    //it is COPYING the adress into p using the assignment operator
    cout << "before the change!\n" << endl;
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p contains " << *p << endl << endl;
    cout << "after the change\n\n";
    *p = -2763;
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    cout << "x now contains " << x << endl;
    //we are able to change the value of x using a pointer that points to its memory location
    
    int y(13);
    cout << "y contains " << y << endl;
    p = &y;
    cout << "p now points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    *p = 980;
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    cout << "y now contains " << y << endl;
    //p was changed to the adress of y. the value of y was changed through p.
    
    int* q;
    q = p;
    cout << "q points to where " << *q << " is stored\n";
    cout << "*q contains " << *q << endl;
    //q is nother pointer that has the same address as p, which is the adress of y
    
    double d(33.44);
    double* pD(&d);
    //double and a double pointer is created
    *pD = *p;
    //the value of the double d is change to what y is, since p is a pointer to the address of y
    *pD = 73.2343;
    //the value of d is changed to this double.
    *p  = *pD;
    //y is assigned to what is stored in d, 73.2343
    *q  = *p;
    //y is assigned to what is stored in y, similar to y = y
    //pD  = p;
    // cannot assign a int pointer to a double pointer
    //p   = pD
    // cannot assign a double pointer to an int pointer
    
    int joe = 24;
    const int sal = 19;
    int*  pI;
    //joe is an int, sal is a constant in, and pI is an int pointer.
//      pI = &joe;
//     *pI = 234;
//      pI = &sal;
//     *pI = 7623;
    //pI points to joe and changes the value of joe. however pI cannot point to sal because
    //sal is a constant int, and the pointer is not an constant int pointer.
    const int* pcI;
      pcI = &joe;
     //*pcI = 234;
      pcI = &sal;
    //*pcI = 7623;
    //a constant int pointer is created, pcI. the constant int pointer can point to joe
    //but joe cannot be modified through this pointer.
    //a constant int pointer can point to sal, but sal cannot be modified through this constant pointer.

//    int* const cpI;
//    int* const cpI(&joe);
//    int* const cpI(&sal);
//      cpI = &joe;
//     *cpI = 234;
//      cpI = &sal;
//     *cpI = 7623;
    // this is a constant int pointer, meaning that the constant int pointer has to be inilizaed with
    //its value, and it cannot be redefined. However, the value of stored in the address of the the constant int pointer can be
    //modified through it.

//    const int* const cpcI;
//    const int* const cpcI(&joe);
//    const int* const cpcI(&sal);
//      cpcI = &joe;  // *cpcI = 234;
//      cpcI = &sal;
//     *cpcI = 7623;
    //a constant int pointer to a constant int cannot be modified at all, the value cannot be modified
    //through the pointer and the pointer be modified to point to another int.
    
    Complex c = {11.23,45.67};
    Complex* pC(&c);
    //cout << "real: " << *pC.real << "\nimaginary: " << *pC.img << endl;
    cout << "real: " << (*pC).real << "\nimaginary: " << (*pC).img << endl;
    cout << "real: " << pC->real << "\nimaginary: " << pC->img << endl;
    
    PlainOldClass poc;
    PlainOldClass* ppoc( &poc );
    cout << ppoc->getX() << endl;
    ppoc->setX( 2837 );
    cout << ppoc->getX() << endl;
    
    int* pDyn = new int(3); // p points to an int initialized to 3 on the heap
    *pDyn = 17;
    cout << "The " << *pDyn
    << " is stored at address " << pDyn
    << " which is in the heap\n";
    cout << pDyn << endl;
    delete pDyn;
    cout << pDyn << endl;
    cout << "The 17 might STILL be stored at address " << pDyn<< " even though we deleted pDyn\n";
    cout << "But can we dereference pDyn?  We can try.  This might crash... " << *pDyn << ".  Still here?\n";
    //my compiler still compiled, and the 17 is still in the address.
    pDyn = nullptr;
    //cout << *pDyn << endl;
    double* pDouble = nullptr;
    //pointers are usually initilized with a nullptr to prevent the pointer
    //from being initlized by pointing to a garbage adress
   // cout << "Can we dereference nullptr?  " << *pDyn << endl;
   // cout << "Can we dereference nullptr?  " << *pDouble << endl;
    // the compiler WILL crash if you try to dereference a nullptr
    double* pTest = new double(12);
    delete pTest;
    pTest = nullptr;
    delete pTest; // safe
    
    short* pShrt = new short(5);
    delete pShrt;
    //delete pShrt;
    
    long jumper = 12238743;
    //delete jumper;
    long* ptrTolong = &jumper;
    //delete ptrTolong;
    Complex cmplx;
    //delete cmplx;
    //cannot deleted things that are stored on the stack. delete can only be used to things allocated
    //on the heap.
    
    vector<Complex*> complV; // can hold pointers to Complex objects
    Complex* tmpPCmplx;      // space for a Complex pointer
    for (size_t ndx = 0; ndx < 3; ++ndx) {
       tmpPCmplx = new Complex; // create a new Complex object on the heap
       tmpPCmplx->real = ndx;   // set real and img to be the
       tmpPCmplx->img  = ndx;   // value of the current ndx
       complV.push_back(tmpPCmplx); // store the ADDRESS of the object in a vector or pointer to Complex
    }
    // display the objects using the pointers stored in the vector
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        cout << complV[ ndx ]->real << endl;
        cout << complV[ ndx ]->img  << endl;
    }
    // release the heap space pointed at by the pointers in the vector
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        delete complV[ndx];
    }
    // clear the vector
    complV.clear();
    

    vector<Colour*> colours;
    string inputName;
    unsigned inputR, inputG, inputB;

    // fill vector with Colours from the file
    // this could be from an actual file but here we are using the keyboard instead of a file
    // (so we don't have to create an actual file)
    // Do you remember the keystroke combination to indicate "end of file" at the keyboard?
    // somehow the while's test has to fail - from keyboard input
    
//    while (cin >> inputName >> inputR >> inputG >> inputB) {
//        colours.push_back(new Colour(inputName, inputR, inputG, inputB));
//    }

    // display all the Colours in the vector:
    for (size_t ndx = 0; ndx < colours.size(); ++ndx) {
        colours[ndx]->display();
        cout << endl;
    }
    
    for (size_t ndx = 0; ndx < colours.size(); ++ndx) {
        delete colours[ndx];
        colours[ndx] = nullptr;
    }
    colours.clear();
    

    
    SpeakerSystem JBL;
    Amplifier Sony;
    SpeakerSystem JBL1;
    Amplifier Sony1;
    JBL.vibrateSpeakerCones(100);
    Sony.attachSpeakers(JBL);
    Sony.playMusic();
    Sony1.attachSpeakers(JBL1);
    JBL1.vibrateSpeakerCones(200);
    Sony1.playMusic();
    


    // write code to model two people in this world
    Person joeBob("Joe Bob"), billyJane("Billy Jane");
    Person john("John");
    // now model these two becoming roommates
    joeBob.movesInWith(billyJane);

    // did this work out?
    cout << joeBob.getName() << " lives with " << joeBob.getRoomiesName() << endl;
    cout << billyJane.getName() << " lives with " << billyJane.getRoomiesName() << endl;
    cout << john.getName() << " tries to move in with " << joeBob.getName() << endl;
    cout << "What happens?" << endl;
    john.movesInWith(joeBob);
}
