//Hellen Ekpo
//CS 2124
//Recitation 7
//March 13th  2020

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& theCourse);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student*);
    void removeStudentsFromCourse();

private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course*);

    // Student method needed by Course
    void removedFromCourse(Course*);

private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();
    bool addCourse(const string&);
    bool addStudent(const string&);
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);
    bool cancelCourse(const string& courseName);
    void purge();

private:
    size_t findStudent(const string&) const;
    size_t findCourse(const string&) const;

    vector<Course*> courses;
    vector<Student*> students;
};



int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;
     
    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;
   
    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;
    */

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}


//Student methods needed by the Registrar:
Student::Student(const string& name) : name(name) {}
const string& Student::getName() const { return name; }
bool Student:: addCourse(Course* theCourse) {
    for (Course* course : courses) {
        if (theCourse -> getName() == course -> getName()) {
            return false;
        }
    }
    courses.push_back(theCourse);
    return true;
}

//Student method needed by Course
void Student:: removedFromCourse(Course* theCourse) {
    for(size_t i = 0; i < courses.size(); ++i) {
        if (courses[i] == theCourse) {
            swap(courses[i], courses[courses.size() - 1]);
            courses.pop_back();
            break;
        }
    }
}


ostream& operator<<(ostream& os, const Student& theStudent) {
    os << theStudent.name << ": ";
    if (theStudent.courses.size() > 0) {
        for (const Course* course : theStudent.courses) {
            os << course -> getName() << " ";
        }
    }
    else {
        os << "No Coueses";
    }
    return os;
}

//Course methods needed by Registrar
Course::Course(const string& courseName) : name(courseName) {}
const string& Course:: getName() const { return name; }
bool Course:: addStudent(Student * theStu) {
    for (Student* student : students) {
        if (theStu -> getName() == student -> getName()) {
            return false;
        }
    }
    students.push_back(theStu);
    return true;
}

void Course:: removeStudentsFromCourse() {
    for (Student* student : students) {
        student -> removedFromCourse(this);
    }
    students.clear();
}

ostream& operator<<(ostream& os, const Course& theCourse) {
    os << theCourse.name << ": ";
    if (theCourse.students.size() > 0) {
        for (const Student* student : theCourse.students) {
            os << student -> getName() << " ";
        }
    }
    else {
        os << "No Students";
    }
    return os;
}


//public Registrar Methods
Registrar:: Registrar()  {}
bool Registrar:: addStudent(const string & stuName) {
    for (const Student* student : students) {
        if (student -> getName() == stuName) {
            return false;
        }
    }
    Student* student = new Student(stuName);
    students.push_back(student);
    return true;
}

bool Registrar:: addCourse(const string & courseName) {
    for (const Course* course : courses) {
        if (course -> getName() == courseName) {
            return false;
        }
    }
    Course* course = new Course(courseName);
    courses.push_back(course);
    return true;
}

bool Registrar:: enrollStudentInCourse(const string& studentName, const string & courseName) {
    size_t stuNdx = findStudent(studentName);
    size_t courNdx = findCourse(courseName);
    if (stuNdx != students.size() &&
        courNdx != courses.size()) {
        students[stuNdx] -> addCourse(courses[courNdx]);
        courses[courNdx] -> addStudent(students[stuNdx]);
        return true;
    }
    return false;
}

bool Registrar:: cancelCourse(const string& courseName) {
    size_t courNdx = findCourse(courseName);
    if (courNdx != courses.size()) {
        courses[courNdx] -> removeStudentsFromCourse();

        delete courses[courNdx];
        courses[courNdx] = nullptr;
        swap(courses[courNdx], courses[courses.size()-1]);
        courses.pop_back();
        return true;
    }
    return false;
}

void Registrar:: purge() {
    for (Course* course : courses) {
        delete course;
        course = nullptr;
    }
    for (Student* student : students) {
        delete student;
        student = nullptr;
    }
    courses.clear();
    students.clear();
}

//private Registrar Methods
size_t Registrar:: findStudent(const string & stuName) const {
    size_t stuIndex = students.size();
    for(size_t i = 0; i < students.size(); ++i) {
        if (students[i] -> getName() == stuName) {
            stuIndex = i;
            break;
        }
    }
    return stuIndex;

}

size_t Registrar:: findCourse(const string& courseName) const {
    size_t courseIndex = courses.size();
    for(size_t i = 0; i < courses.size(); ++i) {
        if (courses[i] -> getName() == courseName) {
            courseIndex = i;
            break;
        }
    }
    return courseIndex;
}


ostream& operator<<(ostream& os, const Registrar& theRegistrar) {
    os << "Registrar's Report\n" << "Courses: \n";
    if (theRegistrar.courses.size() > 0) {
        for(const Course* course : theRegistrar.courses) {
            os << *course << endl;
            
        }
    }
    os << "Students: \n";
    if (theRegistrar.students.size() > 0) {
        for(const Student* student : theRegistrar.students) {
            os << *student << endl;
        }
    }
    return os;
}
