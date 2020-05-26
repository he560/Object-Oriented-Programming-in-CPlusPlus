/*
 Hellen Ekpo
  Recitation 06
  CS2124
 March 6th, 2020
  Focus: Dynamic arrays and copy control
 */

#include <string>
#include <iostream>
using namespace std;

class Position {
    friend ostream& operator<<(ostream& os, const Position& rhs) {
        os << '[' << rhs.title << ',' << rhs.salary << ']';
        return os;
    }
public:
    Position(const string& aTitle, double aSalary)
        : title(aTitle), salary(aSalary) {}
    //the initialization list ttakes a title and a salary and sets the title and salary
    Position(const Position& otherPosition) : title(otherPosition.title), salary(otherPosition.salary)
    {}
    const string& getTitle() const { return title; }
    //this method gets the title and returns it
    double getSalary() const { return salary; }
    //this method returns the salary
    void changeSalaryTo(double d) { salary = d; }
    //this method changes the salary
private:
    string title;
    double salary;
}; // class Position

class Entry {
    friend ostream& operator<<(ostream& os, const Entry& rhs) {
        os << rhs.name << ' ' << rhs.room
           << ' ' << rhs.phone << ", " << *rhs.pos;
        return os;
    }
    //The entry ostream allows for the entry to print out the name, space, room space
    //phone, and the position dereferenced
public:
    Entry(const string& name, unsigned room, unsigned phone, Position& position)
        : name(name), room(room), phone(phone), pos(&position) {
    }
    Entry(const Entry& otherEntry) : name(otherEntry.name), room(otherEntry.room),
    phone(otherEntry.phone), pos(otherEntry.pos) {}
    // the intialization list takes the name, whatever room type whatever phone type and a postition
    const string& getName() const { return name; }
    //returns name of entry
    unsigned getPhone() const { return phone; }
    //returns phone
    
    Position operator[](size_t index) const {
        return *(pos + index);
    }
    
    Position operator[](size_t index) {
        return pos[index];
    }
private:
    string name;
    unsigned room;
    unsigned phone;
    Position* pos;
}; // class Entry

class Directory {
    // Overload output operator
    friend ostream& operator<<(ostream& os, const Directory& theDirectory) {
        for(size_t i = 0; i < theDirectory.size; ++i) {
            os << *(theDirectory.entries[i]) << endl;
        }
        return os;
    }
public:
    // Of course the first function you need to write for this (or
    // any) class is...
    // ???
    // ...
    Directory() : size(0), capacity(1) {
        entries = new Entry*[size];
    }
    
    ~Directory() {
        for (size_t i = 0; i < size; ++i) {
            delete entries[i];
            entries[i] = nullptr;
        }
        delete [] entries;
        entries = nullptr;
        cout << "Destructing the directory....\n";
    }
    
    Directory(const Directory& theDirectory) : size(theDirectory.size),
    capacity(theDirectory.capacity) {
        entries = new Entry*[capacity];
        
        for (size_t i = 0; i < size; ++i) {
            entries[i] = new Entry(*(theDirectory.entries[i]));
        }
        
    }
    
    // We'll get you started with the add method, but obviously you
    // have a lot of work to do here.
    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
        if (size == capacity)    {
            // something is missing!!!  Add it!
            Entry** oldEntries = entries;
            entries = new Entry*[2 * capacity];
            for (size_t i = 0; i < size; ++i) {
                entries[i] = oldEntries[i];
            }
        } // if
        entries[size] = new Entry(name, room, ph, pos);
        ++size;
    } // add
    
    Directory& operator=(const Directory& otherDirect) {
        if (this != &otherDirect) {
            for (size_t i = 0; i < size; ++i) {
                delete entries[i];
                entries[i] = nullptr;
            }
        delete [] entries;
            
        size = otherDirect.size;
        capacity = otherDirect.capacity;
        entries = new Entry*[capacity];
            
        for (size_t i = 0; i < size; ++i) {
            entries[i] = new Entry(*(otherDirect.entries[i]));
        }
    }
    return *this;
}
    int operator[](const string& theName) const {
        for(size_t i = 0; i < size; ++i){
            if (entries[i] -> getName() == theName) {
                return entries[i] -> getPhone();
            }
        }
        return 111;
    }
private:	
    Entry** entries;
    size_t size;
    size_t capacity;
}; // class Directory

void doNothing(Directory dir) { cout << dir << endl; }

int main() {
	
    // Note that the Postion objects are NOT on the heap.
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);
	
    // Create a Directory
    Directory d;
    d.add("Marilyn", 123, 4567, boss);
    cout << d << endl;

    Directory d2 = d;	// What function is being used??
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << d << endl;

    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";

    Directory d3;
    d3 = d2;

    // Should display 1592
    cout << d2["Carmack"] << endl;
	
} // main
