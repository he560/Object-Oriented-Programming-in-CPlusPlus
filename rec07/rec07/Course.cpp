//Hellen Ekpo
//CS2124

#include "Course.hpp"
#include <string>
#include <iostream>
#include "Student.hpp"

namespace BrooklynPoly {

    //Course methods needed by Registrar
    Course::Course(const std::string& courseName) : name(courseName) {}
    const std::string& Course:: getName() const { return name; }
    bool Course:: addStudent(Student* theStudent) {
        for(size_t i = 0; i < students.size(); ++i) {
            if (theStudent == students[i]) {
                return false;
            }
        }
        students.push_back(theStudent);
        return true;
    }
    
    void Course:: removeStudentsFromCourse() {
        for(size_t i = 0; i < students.size(); ++i) {
           students[i] -> removedFromCourse(this);
        }
        students.clear();
    }
    
    std::ostream& operator<<(std::ostream& os, const Course& theCourse) {
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
}
