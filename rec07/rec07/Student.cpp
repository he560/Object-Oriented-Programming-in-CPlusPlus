//Hellen Ekpo
//CS 2124
//March 13th 2020
#include "Course.hpp"
#include <iostream>
#include <string>
#include "Student.hpp"
using namespace std;
class Course;

namespace BrooklynPoly {
    //Student methods needed by the Registrar:
    Student::Student(const string& name) : name(name) {}
    const string& Student::getName() const { return name; }
    bool Student:: addCourse(Course* theCourse) {
        for (Course* course : courses) {
            if (theCourse == course ) {
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

}
