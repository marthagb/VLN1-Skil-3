#ifndef ASSOCIATION_H
#define ASSOCIATION_H

#include <string>
#include "persons.h"
#include "computer.h"


class Association
{
    Persons scientist;
    Computer computer;
public:
    Association();
    Association(Persons p, Computer c);
    string getScientistName() const;
    string getComputerName() const;
    int getYearMade() const;
    bool getBuiltOrNot() const;
    string getComputerType() const;

    void operator = (const Association a);
    bool operator == (const Association a);
    bool operator != (const Association a);

    friend ostream& operator << (ostream& out, const Association& a);
};

#endif // ASSOCIATION_H
