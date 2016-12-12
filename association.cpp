#include "association.h"

Association::Association()
{

}

Association::Association(Persons p, Computer c)
{
    scientist = p;
    computer = c;
}

string Association::getScientistName() const
{
    return scientist.getName();
}

string Association::getComputerName() const
{
    return computer.getComputerName();
}

int Association::getYearMade() const
{
    return computer.getYearMade();
}

bool Association::getBuiltOrNot() const
{
    return computer.getBuiltOrNot();
}

string Association::getComputerType() const
{
    return computer.getType();
}

void Association::operator = (const Association a)
{
    scientist = a.scientist;
    computer = a.computer;
}

//Overloads the == and != operators.
//Two associations are equal if and only if their scientists are equal
//and their computers are equal.
bool Association::operator == (const Association a)
{
    return scientist == a.scientist && computer == a.computer;
}

bool Association::operator != (const Association a)
{
    return scientist != a.scientist || computer != a.computer;
}

//Overloads the << (output) operator
//Writes the scientist's name, the name of the computer,
//the year the computer was made and whether it was built or not
ostream& operator << (ostream& out, const Association& a)
{
    out.width(26);
    out << left << a.getScientistName() << "\t";
    out.width(25);
    out << left << a.getComputerName() << "\t";
    out.width(10);
    out << a.getYearMade() << "\t";
    out.width(15);

    if (a.getBuiltOrNot())
    {
        out << "Built" << "\t";
    }
    else
    {
        out << "Not Built" << "\t";
    }
    out << a.getComputerType() << endl;

    return out;
}
