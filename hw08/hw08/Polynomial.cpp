//Hellen Ekpo
//4 - 21 - 2020
//Homework 8


#include "Polynomial.hpp"
#include <math.h>

using namespace std;

//Node functions
Node::Node(int data, Node* next) : data(data), next(next) {}

Node* listFindTail(Node* headPtr) {
    if (headPtr == nullptr) return nullptr;
    Node* p = headPtr;
    while (p->next != nullptr) {
        p = p->next;
    }
    return p;
}
//created this Node* function to find a node before the target, using the target and headptr
Node* listFindPrevNode(Node* headPtr, Node* target) {
    //if the headptr is null return nullptr
    if (headPtr == nullptr) return nullptr;
    //p is assigned to the headptr
    Node* p = headPtr;
    //if the next ptr equals the target, that means p is the prev node, return p.
    if (p->next == target) return p;
    //else, while p's next ptr is not the target, and target is not null, move down the linked list
    while (p->next != target && p != nullptr) {
        p = p->next;
    }
    //once it finally finds the previous node the while loop will stop, return p.
    return p;
}
void listInsertTail(Node*& headPtr, int data) {
    if (headPtr == nullptr) {
        headPtr = new Node(data);
    }
    else {
        Node* last = listFindTail(headPtr);
        last->next = new Node(data);
    }
}

void listInsertHead(Node*& headPtr, int data) {
    headPtr = new Node(data, headPtr);
}

//Polynomial methods

//Polynomial constructor with vectors. It inserts the appropriate nodes backwards in a linked list
//and sets the degrees to the length of the list - 1.
Polynomial::Polynomial(const vector<int>& polyInts) : degrees(-1) {
    for (size_t i = 0; i < polyInts.size(); ++i) {
        listInsertHead(coefficients, polyInts[i]);
        ++degrees;
    }
    cleanup();
}
//Polynomial constructor with nothing in the parameters. It sets degrees to 0, and the coefficents linked list
//with one node that has the 0.
Polynomial::Polynomial() : degrees(0) {
    listInsertTail(coefficients, 0);
}
//Polynomial copy constructor. sets the degrees to be the same amount as the other polynomial degrees.
//then it iterates through the otherpolynomials' coefficient list and sets the same values for the
//list.
Polynomial::Polynomial(const Polynomial& otherPoly) : degrees(otherPoly.degrees) {
    Node* rightcoeff = otherPoly.coefficients;
    while(rightcoeff != nullptr) {
        listInsertTail(coefficients, rightcoeff->data);
        rightcoeff = rightcoeff->next;
    }
}
//Polynomial assignment operator. Checks for self assignment. If its not self assiignment then
//it iterates through the coefficients pointer, removing them from the heap and setting them
//as nullptrs. it finally removes the last node from the list and sets it to nullptr (destruction)
//it then assigns the degrees to be the same as the otherpolynomial's degrees, and add the
//coefficients in a linked list with nodes being on the heap. It finally returns this polynomial, dereferenced.
Polynomial& Polynomial::operator=(const Polynomial& otherPoly) {
    if (this != &otherPoly) {
        while (coefficients->next != nullptr) {
            Node* next = coefficients->next;
            delete coefficients;
            coefficients = next;
        }
        delete coefficients;
        coefficients = nullptr;
    }
    degrees = otherPoly.degrees;
    Node* rightcoeff = otherPoly.coefficients;
    while(rightcoeff != nullptr) {
        listInsertTail(coefficients, rightcoeff->data);
        rightcoeff = rightcoeff->next;
    }
    return *this;
}
//The polynomial plus equals operator. if the otherpoly's degrees is less than or equal to the degrees,
//then it iterates through polynomials, incrementing the left coefficient by the right coefficent at each node.
//it cleansup the coefficient linked list to prevent any leading 0's in the coefficient, then returns this, dereferenced.
//if the otherpoly's degrees is greater than the degrees, then it sets the degrees to be the otherpoly's degrees,
//going into the while condition and increments/adds new nodes if necessary as it moves down the linked list.
//returns this, dereferenced.
Polynomial& Polynomial::operator+=(const Polynomial& otherPoly) {
    Node* leftcoeff = coefficients;
    Node* rightcoeff = otherPoly.coefficients;
    int count = 0, initialDeg = degrees;
    if (otherPoly.degrees <= degrees) {
        while (rightcoeff != nullptr) {
            leftcoeff->data += rightcoeff->data;
            leftcoeff = leftcoeff->next;
            rightcoeff = rightcoeff->next;
        }
        cleanup();
        return *this;
    }
    degrees = otherPoly.degrees;
    while (rightcoeff != nullptr) {
        if (count == degrees) break;
        if (rightcoeff->next && !leftcoeff->next) {
            Node* newNode = new Node(rightcoeff->next->data);
            leftcoeff->next = newNode;
            if (leftcoeff && count == initialDeg) leftcoeff->data += rightcoeff->data;
            ++count;
        }
        else {
            leftcoeff->data += rightcoeff->data;
            ++count;
        }
        leftcoeff = leftcoeff->next;
        rightcoeff = rightcoeff->next;
    }
    return *this;
}
//The destructor. It iterates down the linked list. it gets the next node, deletes the current node, and moves down.
//then it finally deletes the last node and sets it to nullptr.
Polynomial::~Polynomial() {
    while (coefficients->next != nullptr) {
        Node* next = coefficients->next;
        delete coefficients;
        coefficients = next;
    }
    delete coefficients;
    coefficients = nullptr;
}
//the private method cleanup(). it is used in the constructor and in the plus equals operator. it cleans
//leading zeros by deleting the end of the linked list (the beginning of the polynomial), and then
//sets it to nullptr by using the previous node. degrees decrements. this will happen in a loop as long
//as theres a leading 0, so it will stop once the end of the linked list doesn't equal 0.
void Polynomial::cleanup() {
    while (listFindTail(coefficients)->data == 0) {
        delete listFindTail(coefficients);
        Node* previousLast = listFindPrevNode(coefficients, listFindTail(coefficients));
        previousLast->next = nullptr;
        --degrees;
    }
}
//the evaluate method. it takes a number to evauluate within the polynomial. there is a final number and
//the current degree set to 0. while looking at a value node pointer, if the current degree equals 0
//then the final should just increment the value (constant). else the coefficient should be multiplied
//by the number raised to the current degree. the currentt degree increments and the node pointer moves
//down the linked list.
int Polynomial::evaluate(int num) {
    int finalNum = 0, currDegree = 0;
    Node* coeff = coefficients;
    while(coeff != nullptr) {
        if (currDegree == 0) finalNum += coeff->data;
        else {
            int result = coeff->data * pow(num, currDegree);
            finalNum += result;
        }
        ++currDegree;
        coeff = coeff->next;
    }
    return finalNum;
}
//The plus operator. it creates a temp polynomial that copies thisPoly. it returns
//the temp incremented by otherPoly.
Polynomial operator+(const Polynomial& thisPoly, const Polynomial& otherPoly) {
    Polynomial temp(thisPoly);
    return temp += otherPoly;
}
//The output operator. if the degrees is equal 0, then it should just output the constant. returns os.
//if not, then copies of the coefficient,  last node, the node before the last node are made.
//the degrees of thepolynomial is also stored in a variable.
ostream& operator << (ostream& os, const Polynomial& thisPoly) {
    if (thisPoly.degrees == 0) {
        os << thisPoly.coefficients->data;
        return os;
    }
    Node* leftcoeff = thisPoly.coefficients;
    Node* last = listFindTail(leftcoeff);
    Node* prevlast = listFindPrevNode(leftcoeff, last);
    int degrees = thisPoly.degrees;
    //while the degrees doesnt equal -1
    while (degrees != -1) {
        //if current last node pointer doesn't equal the actual last node pointer (meaning that its the
        //(middle)
        if (last != listFindTail(leftcoeff)) {
            //if the coefficient is greater than 0, it should output a plus
            if (last->data > 0) {
                os << " + ";
                //if the coefficient is greater than 1, it should output the number
                if (last->data > 1) os << last->data;
            }
            //else if the coefficient is less than 0 it should output a minus
            else if (last->data < 0) {
                os << " - ";
                //if the coeefficient is greater than -1 it should output the number
                if (last->data < -1) os << last->data;
            }
        }
        //else if [the current last node is equal to the last node]
        //if the coefficient is greater than 0 and not 1, output the number
        else if (last->data > 0) {
            if (last->data != 1) os << last->data;
        }
        //if the coefficient is less than 0 output the negaive sign
        //if it is less than -1 output the number.
        else if (last->data < 0) {
            os << "-";
            if (last->data != -1) os << last->data;
        }
        //if the coefficient is not 0, output x
        if (last->data != 0) os << "x";
        //if the degrees is greater than 1, and the coefficient is not 0
        //output the caret and the degrees.
        if (degrees > 1 && last->data != 0) os << "^" << degrees;
        //last moves up the previous node.
        last = prevlast;
        //if the currentt last node equals the first node of the coefficents (the constant term)
        if (leftcoeff == last) {
            //if its less than 0, output minus and the number
            if (leftcoeff->data < 0) {
                os << " - " << leftcoeff->data;
            }
            //if its greater than 0, output plus and the number
            else if (leftcoeff->data > 0) {
                os << " + " << leftcoeff->data;
            }
            break;
        }
        //the current previous last is set to the node before the current last. degrees decrements.
        prevlast = listFindPrevNode(leftcoeff, last);
        --degrees;
    }
    return os;
}

//equality operator
bool operator == (const Polynomial& thisPoly, const Polynomial& otherPoly) {
    //if there degrees arent the same return false
    if (thisPoly.degrees != otherPoly.degrees) return false;
    Node* leftcoeff = thisPoly.coefficients;
    Node* rightcoeff = otherPoly.coefficients;
    //while looking at a valid pointer in the lhs linked list
    while (leftcoeff != nullptr) {
        //if at any point the coefficients aren't equal to each other, return false
        if (leftcoeff->data != rightcoeff->data) return false;
        //else move down
        leftcoeff = leftcoeff->next;
        rightcoeff = rightcoeff->next;
    }
    return true;
}

bool operator != (const Polynomial& thisPoly, const Polynomial& otherPoly) {
    return !(thisPoly == otherPoly);
}


