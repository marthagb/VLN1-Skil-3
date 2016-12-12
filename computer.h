#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>
#include <iostream>
#include "validation.h"

using namespace std;

class Computer
{
    string computerName;
    int yearMade;
    string type;
    bool builtOrNot;
    validation valid;

public:
    Computer();
    Computer(string n, int yM, string t, bool b);
    string getComputerName() const;
    int getYearMade() const;
    string getType() const;
    bool getBuiltOrNot() const;

    void operator = (const Computer& c);
    bool operator == (const Computer& c);
    bool operator != (const Computer& C);

    friend ostream& operator << (ostream& out, const Computer& c);
    friend istream& operator >> (istream& in, Computer& c);
};

#endif // COMPUTER_H
