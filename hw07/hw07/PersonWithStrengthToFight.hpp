#include "Noble.hpp"
#ifndef PersonWithStrengthToFight_hpp
#define PersonWithStrengthToFight_hpp
//This class inherits from Noble.
//the only member it has on its own is strength or stren
class PersonWithStrengthToFight : public Noble {
public:
    PersonWithStrengthToFight(const std::string& name, int strength);
    void battle(Noble& noble);
    int strength() const;
    void setStrength(double val, bool ratio = false);
private:
    int stren;
};

#endif /* PersonWithStrengthToFight_hpp */
