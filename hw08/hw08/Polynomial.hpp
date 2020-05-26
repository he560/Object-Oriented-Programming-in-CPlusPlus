//Hellen Ekpo
//4 - 21 - 2020
//Homework 8
#include <string>
#include <vector>
#include <iostream>


#ifndef Polynomial_hpp
#define Polynomial_hpp
//The
struct Node {
    Node(int data = 0, Node* next = nullptr);
    int data;
    Node* next;
};

class Polynomial {
    //output operator
    friend std::ostream& operator << (std::ostream& os, const Polynomial& thisPoly);
    //equality operator
    friend bool operator == (const Polynomial& thisPoly, const Polynomial& otherPoly);
public:
    //constructor that takes vector
    Polynomial(const std::vector<int>& polyInts);
    //default constructor
    Polynomial();
    //copy constructor
    Polynomial(const Polynomial& otherPoly);
    //assignment operator
    Polynomial& operator=(const Polynomial& otherPoly);
    //plus equals operator
    Polynomial& operator+=(const Polynomial& otherPoly);
    //destructor
    ~Polynomial();
    int evaluate(int num);
private:
    void cleanup();
    Node* coefficients = nullptr;
    int degrees;
};

//addition operator.
Polynomial operator+(const Polynomial& thisPoly, const Polynomial& otherPoly);
//doesnt equal operator
bool operator != (const Polynomial& thisPoly, const Polynomial& otherPoly);
#endif /* Polynomial_hpp */
