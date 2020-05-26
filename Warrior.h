#ifndef WARRIOR_H
#define WARRIOR_H

#include <string>
#include <iostream>
#include <vector>
//The Warrior header file contains the definition of the Warrior class, and contains the
//header portion of all the methods within the class.
namespace WarriorCraft {
    class Warrior {
        friend std::ostream& operator << (std::ostream& os, const Warrior& theWarrior);
    public:
        Warrior(const std::string& name, int strength);
        const std::string& getName() const;
        int getStrength() const;
        bool isHired() const;
        bool employement(bool status);
        void setStrength(int val);
        bool runaway();
        bool setBoss(Noble* noble);
    private:
        std::string name;
        double strength;
        bool employed;
        Noble* boss;
    };
}

#endif
