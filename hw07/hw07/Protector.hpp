#ifndef Protector_hpp
#define Protector_hpp
#include <string>
#include <vector>
#include <iostream>
//Header for Protector. Include Noble class so it knows what boss is. All methods are defined in cpp.
//The Protector has 3 private fields and and one protected.
class Noble;

class Protector {
public:
    Protector(const std::string& name, int strength);
    virtual void setStrength(int val) = 0;
    int getStrength() const;
    bool isHired() const;
    const std::string& getName() const;
    bool employement(bool status);
    bool setBoss(Noble* noble);
private:
    std::string name;
    int strength;
    bool employed;
protected:
    Noble* boss;
};

#endif /* Protector_hpp */
