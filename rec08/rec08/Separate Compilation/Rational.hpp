#ifndef Rational_hpp
#define Rational_hpp
#include <iostream>

namespace CS2124 {
    class Rational {
        friend std::ostream& operator <<(std::ostream& os, const Rational& theRat);
        friend std::istream& operator >>(std::istream& is, Rational& theRat);
        friend bool operator== (const Rational& leftRat, const Rational& rightRat);
        friend bool operator< (const Rational& leftRat, const Rational& rightRat);
    public:
        Rational(int num = 0, int denom = 1);
        Rational& operator +=(const Rational& theRat);
        Rational& operator++();
        Rational operator++(int);
        explicit operator bool() const;
        void normalize();
    private:
        int numerator, denominator;
    };

Rational& operator--(Rational&);
Rational operator--(Rational& lhs, int);
bool operator != (const Rational&, const Rational&);
bool operator <= (const Rational&, const Rational&);
bool operator > (const Rational&, const Rational&);
bool operator >= (const Rational&, const Rational&);
Rational operator + (const Rational&, const Rational&);
Rational operator - (const Rational&, const Rational&);
}

#endif /* Rational_hpp */
