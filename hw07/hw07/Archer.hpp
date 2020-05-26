#include "Warrior.hpp"
#include <string>
#ifndef Archer_hpp
#define Archer_hpp
//archer inherits from warrior
class Archer : public Warrior {
public:
    Archer(const std::string& name, int strength);
    void setStrength(int val);
};

#endif /* Archer_hpp */
