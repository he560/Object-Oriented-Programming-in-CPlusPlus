#include "Protector.hpp"
#include <string>
#ifndef Wizard_hpp
#define Wizard_hpp
//The wizard inherits from protector
class Wizard : public Protector {
public:
    Wizard(const std::string& name, int strength);
    void setStrength(int val);
};

#endif /* Wizard_hpp */
