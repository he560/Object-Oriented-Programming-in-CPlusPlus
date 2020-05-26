#include "Rational.hpp"
#include <iostream>

using namespace std;

namespace CS2124 {
int greatestCommonDivisor(int x, int y) {
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}
    ostream& operator <<(ostream& os, const Rational& theRat) {
        if (theRat.denominator == 1) {
            os << theRat.numerator;
        }
        else {
           os << theRat.numerator << "/" << theRat.denominator;
        }
        return os;
    }
    istream& operator >>(istream& is, Rational& theRat) {
        char slash;
        is >> theRat.numerator >> slash >> theRat.denominator;
        theRat.normalize();
        return is;
    }
    bool operator== (const Rational& leftRat, const Rational& rightRat) {
        return (leftRat.numerator == rightRat.numerator) &&
               (leftRat.denominator == rightRat.denominator);
    }
    bool operator< (const Rational& leftRat, const Rational& rightRat) {
        double leftSide = ((double)leftRat.numerator/(double)leftRat.denominator);
        double rightSide = ((double)rightRat.numerator/(double)rightRat.denominator);
        return (leftSide < rightSide);
    }
    Rational::Rational(int num, int denom) : numerator(num), denominator(denom) {
        normalize();
    }
    void Rational::normalize() {
      int divisor = greatestCommonDivisor(numerator, denominator);
      numerator = numerator/divisor;
      denominator = denominator/divisor;
      if (denominator < 0) {
          numerator = -numerator;
          denominator = -denominator;
      }
    }
    Rational& Rational::operator +=(const Rational& theRat) {
        int newDen = denominator*theRat.denominator;
        numerator = (numerator*theRat.denominator) + (theRat.numerator*denominator);
        denominator = newDen;
//        int numer1 = numerator*theRat.denominator;
//        int numer2 = theRat.numerator*denominator;
//        denominator = denominator*theRat.denominator;
//        numerator = numer1 + numer2;
        normalize();
        return *this;
    }
    Rational& Rational::operator++() {
        numerator += (denominator);
        return *this;
    }
    Rational Rational::operator++(int) {
        Rational temp(*this);
        numerator += (denominator);
        return temp;
    }
    Rational::operator bool() const{
        return numerator != 0;
    }

Rational operator+(const Rational& leftRat, const Rational& rightRat) {
    Rational temp = leftRat;
    return temp+= rightRat;
}

Rational& operator--(Rational& lhs) {
    Rational minusOne(-1);
    lhs += minusOne;
    return lhs;
}

Rational operator--(Rational& lhs, int) {
    Rational temp(lhs);
    Rational minusOne(-1);
    lhs += minusOne;
    return temp;
}

bool operator!= (const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

bool operator<= (const Rational& lhs, const Rational& rhs) {
    return (lhs < rhs || lhs == rhs);
}

bool operator> (const Rational& lhs, const Rational& rhs) {
    if (lhs == rhs) return false;
    return !(lhs < rhs);
}

bool operator>= (const Rational& lhs, const Rational& rhs) {
    return (lhs > rhs || lhs == rhs);
}
    
}
