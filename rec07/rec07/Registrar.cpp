//Hellen Ekpo
//CS 2124
//March 13th 2020
#include "Course.hpp"
#include <string>
#include <iostream>
#include "Student.hpp"
#include "Registrar.hpp"
using namespace std;

namespace BrooklynPoly {
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
}

