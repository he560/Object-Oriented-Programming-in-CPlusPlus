#ifndef Course_hpp
#define Course_hpp

#include <string>
#include <vector>
#include <iostream>
#include "Student.hpp"


namespace BrooklynPoly {
class Student;
    class Course {
        friend std::ostream& operator<<(std::ostream& os, const Course& theCourse);
    public:
        // Course methods needed by Registrar
        Course(const std::string& courseName);
        const std::string& getName() const;
        bool addStudent(Student*);
        void removeStudentsFromCourse();

    private:
        std::string name;
        std::vector<Student*> students;
    };
}

#endif
