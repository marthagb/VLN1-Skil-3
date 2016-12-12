#include "computer.h"
#include <iomanip>

using namespace std;

//Default constructor.
//If a computer is ever read in as this it will be skipped.
//(see addComputersFromFile in DataLayer)
Computer::Computer()
{
    computerName = "Computer X";
    yearMade = 1980;
    type = "type Y";
    builtOrNot = false;
}

Computer::Computer(string n, int yM, string t, bool b)
{
    computerName = n;
    yearMade = yM;
    type = t;
    builtOrNot = b;
}

string Computer::getComputerName() const
{
    return computerName;
}

int Computer::getYearMade() const
{
    return yearMade;
}

string Computer::getType() const
{
    return type;
}

bool Computer::getBuiltOrNot() const
{
    return builtOrNot;
}

//Overloads the = operator
void Computer::operator = (const Computer& c)
{
    computerName = c.computerName;
    yearMade = c.yearMade;
    type = c.type;
    builtOrNot = c.builtOrNot;
}

//Overloads the == and != operators.
//Two computers are equal if and only if each
//parameter is equal.
bool Computer::operator == (const Computer& c)
{
    return computerName == c.computerName && yearMade == c.yearMade && type == c.type && builtOrNot == c.builtOrNot;
}

bool Computer::operator != (const Computer& c)
{
    return computerName != c.computerName || yearMade != c.yearMade || type != c.type || builtOrNot != c.builtOrNot;
}

//Overloads the << (output) operator.
//Writes out the name, year made and type.
//Writes "Built" if the computer was built
//and "Not Built" otherwise
ostream& operator << (ostream& out, const Computer& c)
{
    out.width(28);
    out << left << c.getComputerName() << "\t" << c.getYearMade() << "\t\t";
    out.width(25);
    out << left << c.getType()  << "\t";

    if (!c.getBuiltOrNot())
    {
        out << "Not Built" << endl;
    }
    else
    {
        out << "Built" << endl;
    }
    return out;
}

//Overloads the >> (input) operator.
//Reads the name which we know ends at a semicolon (;)
//Then reads the year made and type, which also ends at a semicolon.
//Reads either "Built" or "Not built". This too is expected to be followed by a semicolon.
istream& operator >> (istream& in, Computer& c)
{
    string n = " ", yM = " ", t = " ", b = " ";
    int year = 0;
    Computer def;

    in >> ws;
    getline(in, n, ';');
    in >> yM;
    in >> ws;
    getline(in, t, ';');
    in >> ws;
    getline(in, b, ';');

    if (c.valid.validYear(yM, year))        //checks for a valid year.
    {
        if (b == "Built" || b == "built")
        {
            c.computerName = n;
            c.yearMade = year;
            c.type = t;
            c.builtOrNot = true;
        }
        else if (b == "Not built" || b == "not built")
        {
            c.computerName = n;
            c.yearMade = year;
            c.type = t;
            c.builtOrNot = false;
        }
        //Each of these, if it fails the validity checks, will make c a computer equal to a computer made with
        //the default constructor, which, when being loaded, will be skipped.
        else c = def;
    }
    else c = def;

    return in;
}
