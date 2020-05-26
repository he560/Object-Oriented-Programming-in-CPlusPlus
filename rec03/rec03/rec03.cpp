//Hellen Ekpo
//2/14/2020
//Recitiation 3

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


//
// Task 1: The Account struct. Call it AccountS
//
struct AccountS {
    string name;
    int accNum;
};

//
// Task 2: The Account class. Call it AccountC
//
class Client {
    friend ostream& operator << (ostream& os, const Client& theClient) {
        os << "Client name: " << theClient.name <<  "\nClient account number: "
        << theClient.accNum << "\nClient social security: " << theClient.ssn << endl;
        return os;
    }
public:
    Client(const string& name, int accNum, int ssn) : name(name), accNum(accNum), ssn(ssn) {}
    const string& getName() const{
        return name;
    }
    int getAccNum() const{
        return accNum;
    }
private:
    string name;
    int accNum;
    int ssn;
};


class AccountC {
    friend ostream& operator << (ostream& os, const AccountC& theAccount) {
        os << theAccount.client <<
        "Transactions: \n";
        for(const Transaction& transac : theAccount.transactions) {
            os << transac << endl;
        }
        os << "\nBalance: " << theAccount.balance;
        return os;
    }
public:
    AccountC(const string& name, int accNum, int ssn) :  client(name, accNum, ssn) {}
    int getaccNum() const{
        return client.getAccNum();
    }
    const string& getName() const{
        return client.getName();
    }
    //the first const prevents the string from being manipulated once you return it. The second const prevents the function from modifying the
    //the value.
    void deposit(int val) {
        balance += val;
        Transaction transac("deposit", val);
        transactions.push_back(transac);
        
    }
    void withdraw(int val) {
        if ((balance - val) < 0) {
            cerr << "Cannot make this withdrawal, " << client.getName() << endl;
        }
        else {
            balance -= val;
            Transaction transac("withdraw", val);
            transactions.push_back(transac);
        }
    }
private:
    class Transaction {
        friend ostream& operator << (ostream& os, const Transaction& theTransaction) {
            os << theTransaction.transType << ": " << theTransaction.transAmount;
            return os;
        }
    public:
        Transaction (const string& transAction, int amount) : transType(transAction), transAmount(amount) {}
    private:
        string transType;
        int transAmount;
        
    };
    Client client;
    int accNum;
    vector<Transaction> transactions;
    int balance = 0;
};



// 2.b: AccountC output operator, not a friend.

//ostream& operator<< (ostream& os, const AccountC& theAccount) {
//    os << theAccount.getName() << " " << theAccount.getaccNum();
//    return os;
//}
// 2.2: AccountC output operator, reimplemented as a friend.
//
// Task 3
//
// Transaction class definition


// Account class definition


//
// Task 4
//
// Transaction class definition with embedded Account class



int main() {
//
//    //
//    // Task 1: account as struct
//    //
//    //      1a. Fill vector of account structs from file
//
//    cout << "Task1a:\n";
//    cout << "Filling vector of struct objects, define a local struct instance "
//         << " and set fields explicitly:\n";
//    vector<AccountS> accountsS;
//    ifstream accStream;
//    accStream.open("accounts.txt");
//    if (!accStream) {
//        cerr << "Couldn't open file!\n";
//        exit(1);
//    }
//
//    while(accStream) {
//        string name;
//        int accNum = 0;
//        accStream >> name >> accNum;
//        AccountS account;
//        account.name = name;
//        account.accNum = accNum;
//        if (accNum) accountsS.push_back(account);
//    }
//    accStream.close();
//    for (const AccountS&acc : accountsS) {
//        cout << acc.name << " " << acc.accNum << endl;
//    }
//
//    //      1b
//    cout << "Task1b:\n";
//    cout << "Filling vector of struct objects, using {} initialization:\n";
//    accountsS.clear();
//    accStream.open("accounts.txt");
//    if (!accStream) {
//        cerr << "Couldn't open file!\n";
//        exit(1);
//    }
//    while(accStream) {
//        string name;
//        int accNum = 0;
//        accStream >> name >> accNum;
//        AccountS account{name, accNum};
//        if (accNum) accountsS.push_back(account);
//    }
//    accStream.close();
//    accStream.clear();
//    for (const AccountS&acc : accountsS) {
//        cout << acc.name << " " << acc.accNum << endl;
//    }
//
//    //==================================
//    //
//    // Task 2: account as class
//    //
//
//    //      2a
//    cout << "==============\n";
//    cout << "\nTask2a:";
//    cout << "\nFilling vector of class objects, using local class object:\n";
    vector<AccountC> accountsC;
//    accStream.open("accounts.txt");
//    if (!accStream) {
//        cerr << "Couldn't open file!\n";
//        exit(1);
//    }
//    while(accStream) {
//        string name;
//        int accNum = 0;
//        accStream >> name >> accNum;
//        AccountC account(name, accNum);
//        if (accNum) accountsC.push_back(account);
//    }
//    accStream.close();
//    for (const AccountC&acc : accountsC) {
//        cout << acc.getName() << " " << acc.getaccNum() << endl;
//    }
//    cout << "---\n";
//    cout << "\nTask2b:\n";
//    cout << "output using output operator with getters\n";
//    for (const AccountC&acc : accountsC) {
//        cout << acc << endl;
//    }
//
//    cout << "\nTask2c:\n";
//    cout << "output using output operator as friend without getters\n";
//    // Note code here will be same as above.
//    for (const AccountC&acc : accountsC) {
//        cout << acc << endl;
//    }
//
//    cout << "\nTask2d:\n";
//    cout << "Filling vector of class objects, using temporary class object:\n";
//    accountsC.clear();
//    accStream.open("accounts.txt");
//    if (!accStream) {
//        cerr << "Couldn't open file!\n";
//        exit(1);
//    }
//    while(accStream) {
//        string name;
//        int accNum = 0;
//        accStream >> name >> accNum;
//        if (accNum) accountsC.push_back(AccountC(name, accNum));
//    }
//    accStream.close();
//    for (const AccountC&acc : accountsC) {
//        cout << acc << endl;
//    }
//
//    cout << "\nTask2e:\n";
//    cout << "\nFilling vector of class objects, using emplace_back:\n";
//    accountsC.clear();
//    accStream.open("accounts.txt");
//    if (!accStream) {
//        cerr << "Couldn't open file!\n";
//        exit(1);
//    }
//    while(accStream) {
//        string name;
//        int accNum = 0;
//        accStream >> name >> accNum;
//        if (accNum) accountsC.emplace_back(name, accNum);
//    }
//    accStream.close();
//    for (const AccountC&acc : accountsC) {
//        cout << acc << endl;
//    }
//    accountsC.clear();
//
    // Task 3
    cout << "==============\n";
    cout << "\nTask 3:\n\nAccounts and Transaction:\n";
    ifstream transStream;

    transStream.open("transactions.txt");
    if (!transStream) {
        cerr << "Couldn't open file!\n";
        exit(1);
    }
    string command;
    while(transStream >> command) {
        if (command == "Account") {
            string name;
            int accNum;
            transStream >> name >> accNum;
            AccountC account(name, accNum, 4567);
            accountsC.push_back(account);
        }
        else {
            int accNum, amount;
            transStream >> accNum >> amount;
            for(AccountC& acc : accountsC) {
                if (acc.getaccNum() == accNum) {
                    if (command == "Deposit") {
                        acc.deposit(amount);
                    }
                    else {
                        acc.withdraw(amount);
                    }
                    break;
                }
            }
        }
    }
    transStream.close();
    for(const AccountC& acc : accountsC) {
        cout << acc << endl;
    }
//
//    // Task 4
//    cout << "==============\n";
//    cout << "\nTask 4:\n\nAccounts and Transaction:\n"
//         << "Account class is nested inside Transaction class.\n";
//
}

