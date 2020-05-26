#include "Protector.hpp"
#ifndef Warrior_hpp
#define Warrior_hpp
//Warrior inherits from protector
class Warrior : public Protector {
public:
    Warrior(const std::string& name, int strength);
};

#endif /* Warrior_hpp */
