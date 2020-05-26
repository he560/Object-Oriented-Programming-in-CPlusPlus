#include "Noble.hpp"
#include "Protector.hpp"
#include <string>
#include <vector>
#include <iostream>
#ifndef Lord_hpp
#define Lord_hpp
//the lord inherits from the noble class. it has an army of protectors pointers,
//so that anything that derives from protector class can join this army.
class Lord : public Noble {
public:
    Lord(std::string name);
    void battle(Noble& noble);
    int strength() const;
    void setStrength(double val, bool ratio);
    bool hires(Protector& protector);
    bool fires(Protector& protector);
    
private:
    std::vector<Protector*> army;
};

#endif /* Lord_hpp */
