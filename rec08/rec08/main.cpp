#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int greatestCommonDivisor(int x, int y) {
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

class Rational {
    friend ostream& operator <<(ostream& os, const Rational& theRat) {
        if (theRat.denominator == 1) {
            os << theRat.numerator;
        }
        else {
           os << theRat.numerator << "/" << theRat.denominator;
        }
        return os;
    }
    friend istream& operator >>(istream& is, Rational& theRat) {
        char slash;
        is >> theRat.numerator >> slash >> theRat.denominator;
        theRat.normalize();
        return is;
    }
    friend bool operator== (const Rational& leftRat, const Rational& rightRat) {
        return (leftRat.numerator == rightRat.numerator) &&
               (leftRat.denominator == rightRat.denominator);
    }
    friend bool operator< (const Rational& leftRat, const Rational& rightRat) {
        double leftSide = ((double)leftRat.numerator/(double)leftRat.denominator);
        double rightSide = ((double)rightRat.numerator/(double)rightRat.denominator);
        return (leftSide < rightSide);
    }
public:
    Rational(int num = 0, int denom = 1) : numerator(num), denominator(denom) {
        normalize();
    }
    void normalize() {
      int divisor = greatestCommonDivisor(numerator, denominator);
      numerator = numerator/divisor;
      denominator = denominator/divisor;
      if (denominator < 0) {
          numerator = -numerator;
          denominator = -denominator;
      }
    }
    Rational& operator +=(const Rational& theRat) {
        int numer1 = numerator*theRat.denominator;
        int numer2 = theRat.numerator*denominator;
        denominator = denominator*theRat.denominator;
        numerator = numer1 + numer2;
        normalize();
        return *this;
    }
    Rational& operator++() {
        numerator += (denominator);
        return *this;
    }
    Rational operator++(int) {
        Rational temp(*this);
        numerator += (denominator);
        return temp;
    }
    explicit operator bool () const{
        return numerator != 0;
    }
private:
    int numerator, denominator;
};

Rational& operator+(const Rational& leftRat, const Rational& rightRat) {
    Rational newLHS = leftRat;
    Rational newRHS = rightRat;
    return newLHS += newRHS;
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
int main() {
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;    // Implement as member
    cout << "a = " << a << endl;

    // Implement as non-member, but not a friend
//    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;

    // How does this manage to work?
    // It does NOT require writing another == operator.
    cout << "1 == one: " << boolalpha << (1 == one) << endl;

    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing?
//    cout << "a-- -- = " << (a-- --) << endl;
    cout << "a = " << a << endl;


    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    }

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    }

    cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalves(3, 2);
    Rational minusFive(-5);
    cout << twoFifths << " < " << threeHalves << " : "
         << (twoFifths < threeHalves) << endl;
    cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
    cout << threeHalves << " < " << twoFifths << " : "
         << (threeHalves < twoFifths) << endl;
    cout << threeHalves << " > " << threeHalves << " : "
         << (threeHalves > threeHalves) << endl;
    cout << threeHalves << " >= " << threeHalves << " : "
         << (threeHalves >= threeHalves) << endl;
    cout << minusFive << " >= " << threeHalves << " : "
         << (minusFive >= threeHalves) << endl;
}
