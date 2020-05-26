
#ifndef Noble_hpp
#define Noble_hpp
#include <string>
#include <iostream>
#include <vector>
//Yhe header for Noble. It has 2 protected fields, so that derived classes can access its
//life status and its name
class Noble {
public:
    Noble(std::string name) : name(name), life(true) {}
    virtual void battle(Noble& noble) = 0;
    virtual int strength() const = 0;
    virtual void setStrength(double val, bool ratio = false) = 0;
    const std::string& getName() const;
protected:
    bool life;
    std::string name;
};

#endif /* Noble_hpp */
