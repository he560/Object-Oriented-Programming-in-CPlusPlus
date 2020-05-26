#include "Warrior.hpp"
#include <string>
#ifndef Swordsman_hpp
#define Swordsman_hpp
//the swordsman class inherits from warrior
class Swordsman : public Warrior {
public:
    Swordsman(const std::string& name, int strength);
    void setStrength(int val);
};

#endif /* Swordsman_hpp */
