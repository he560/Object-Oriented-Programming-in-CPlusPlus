//Hellen Ekpo
//Recitation 05
//CS 2124
//February 28, 2020

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


class Section {
    friend ostream& operator << (ostream& os, const Section& theSection) {
        os << "Section: " << theSection.secName << ", Time Slot: " << theSection.timeslot;
        os << "\nStudents:\n";
        if (theSection.students.size() == 0) os << "None";
        else {
            for (Student* student : theSection.students) {
                os << *student << endl;
            }
        }
        return os;
    }
public:
    Section(const string& secName, const string& day, int time) : secName(secName), timeslot(day, time) {}
    
    void addStudent(const string& stuName) {
        Student* student = new Student(stuName);
        students.push_back(student);
    }
    Section(const Section& anotherSect) : timeslot(anotherSect.timeslot) {
        secName = anotherSect.secName;
        for (Student* student : anotherSect.students) {
            Student* newStu = new Student(*student);
            students.push_back(newStu);
        }
    }
    bool addGrade(const string& name, int grade, int slot) {
        for (Student* student : students) {
            if (student->getName() == name) {
                student->addGrade(grade, slot);
                return true;
            }
        }
        cout << "That student isn't in this section!\n";
        return false;
    }
    
    ~Section() {
        //1. free up resources on the heap
        cout << "Section " << secName << " is being deleted...\n";
        for(Student* student : students) {
            cout << "Deleting: " << student->getName() << endl;
            delete student;
            student = nullptr;
        }
        students.clear();
    }
private:
    class Student {
        friend ostream& operator << (ostream& os, const Student& theStudent) {
            os << "Name: " << theStudent.getName() << ", Grades: ";
            for(int grade : theStudent.grades) {
                os << grade << " ";
            }
            return os;
        }
    public:
        Student(const string& name) : name(name), grades(vector<int>(14, -1)){}
        Student(const Student& otherStu) {
            name = otherStu.name;
            grades = otherStu.grades;
        }
        void addGrade(int grade, int slot) {
            grades[slot-1] = grade;
        }
        string getName() const {
            return name;
        }
    private:
        string name;
        vector<int> grades;
    };
    class TimeSlot {
        friend ostream& operator << (ostream& os, const TimeSlot& theTimeSlot) {
            os << "[Day: " << theTimeSlot.day << ", Start time: ";
            if( 0 <= theTimeSlot.time && theTimeSlot.time<= 12) {
                os << theTimeSlot.time << "am]";
            }
            else {
                os << theTimeSlot.time - 12 << "pm]";
            }
            return os;
        }
    public:
        TimeSlot(const string& day, int time) : day(day), time(time) {}
        TimeSlot(const TimeSlot& anotherTime) {
            day = anotherTime.day;
            time = anotherTime.time;
        }
        void setDay(const string& dayRHS) {
            day = dayRHS;
        }
        void setTime(int timeRHS) {
            time = timeRHS;
        }
    private:
        string day;
        int time;
        
    };
    string secName;
    vector<Student*> students;
    TimeSlot timeslot;
};

class LabWorker {
    friend ostream& operator << (ostream& os, const LabWorker& theLabInstruc) {
        if (theLabInstruc.lab == nullptr)
            os << theLabInstruc.name << " does not have a section.\n";
        else {
            os << theLabInstruc.name << " has a section:\n" << *theLabInstruc.lab;
        }
        return os;
    }
public:
    LabWorker(const string& name) : name(name), lab(nullptr) {}
    bool addSection(Section& theSection) {
        if (lab == nullptr) {
            lab = &theSection;
            return true;
        }
        cout << "This TA is already teaching a section!\n";
        return false;
    }
    void addGrade(const string& stuName, int grade, int slot) {
        lab->addGrade(stuName, grade, slot);
    }
private:
    string name;
    Section* lab;
};

void doNothing(Section sec) {
      cout << sec << endl;;
  }

int main() {
        cout << "Test 1: Defining a section\n";
        Section secA2("A2", "Tuesday", 16);
        cout << secA2 << endl;

        cout << "\nTest 2: Adding students to a section\n";
        secA2.addStudent("John");
        secA2.addStudent("George");
        secA2.addStudent("Paul");
        secA2.addStudent("Ringo");
        cout << secA2 << endl;

        cout << "\nTest 3: Defining a lab worker.\n";
        LabWorker moe("Moe");
        cout << moe << endl;

        cout << "\nTest 4: Adding a section to a lab worker.\n";
        moe.addSection(secA2);
        cout << moe << endl;
    
        cout << "\nTest 5: Adding a second section and lab worker.\n";
        LabWorker jane( "Jane" );
        Section secB3( "B3", "Thursday", 11 );
        secB3.addStudent("Thorin");
        secB3.addStudent("Dwalin");
        secB3.addStudent("Balin");
        secB3.addStudent("Kili");
        secB3.addStudent("Fili");
        secB3.addStudent("Dori");
        secB3.addStudent("Nori");
        secB3.addStudent("Ori");
        secB3.addStudent("Oin");
        secB3.addStudent("Gloin");
        secB3.addStudent("Bifur");
        secB3.addStudent("Bofur");
        secB3.addStudent("Bombur");
        jane.addSection(secB3);
        cout << jane << endl;
    
    cout << "\nTest 6: Adding some grades for week one\n";
       moe.addGrade("John", 17, 1);
       moe.addGrade("Paul", 19, 1);
       moe.addGrade("George", 16, 1);
       moe.addGrade("Ringo", 7, 1);
       cout << moe << endl;
    
    
    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);
    moe.addGrade("Paul", 20, 3);
    moe.addGrade("Ringo", 0, 3);
    moe.addGrade("George", 16, 3);
    cout << moe << endl;
    
    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works properly, i.e. no memory leaks\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";
}
