#ifndef NOBLE_H
#define NOBLE_H

#include <string>
#include <vector>
#include <iostream>
//The Noble header file contains the definition of the Noble class, and contains the
//header portion of all the methods within the class.
namespace WarriorCraft {
class Warrior;
    class Noble {
        friend std::ostream& operator << (std::ostream& os, const Noble& theNoble);
    public:
        Noble(const std::string& name);
        void battle(Noble& theNoble);
        int strength() const;
        void setStrength(double val, bool ratio = false);
        const std::string& getName() const;
        bool hire(Warrior& warrior);
        bool fire(Warrior& warrior);
        bool abandon(Warrior& warrior);
    private:
        std::string name;
        std::vector<Warrior*> army;
        bool life;
    };
}

#endif
