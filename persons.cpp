#include "persons.h"

time_t t = time(NULL);
tm* TimePtr = localtime(&t);
const int CURRENT_YEAR = TimePtr->tm_year + 1900;


//Default Constructor.
//If a person is ever read in as this, it will be skipped.
//(see readFromFile() and readFromOtherFile(string input) in datalayer.cpp)
Persons::Persons()
{
    name = "John Doe";
    gender = 'M';
    birthYear = 1980;
    deathYear = 0;
    alive = true;
    age = CURRENT_YEAR - birthYear;
}

//Constructor.
//If deathyear == 0, the person will be alive.
//If the person is alive, age is set to their current age.
//Otherwise, age is set to their age when they died.
Persons::Persons(string n, char g, int bY, int dY)
{
    name = n;
    gender = g;
    birthYear = bY;
    deathYear = dY;

    if (dY == 0)
    {
        alive = true;
        age = CURRENT_YEAR - birthYear;
    }
    else
    {
        alive = false;
        age = deathYear - birthYear;
    }
}

string Persons::getName() const
{
    return name;
}

int Persons::getBirthYear() const
{
    return birthYear;
}

int Persons::getDeathYear() const
{
    return deathYear;
}

char Persons::getGender() const
{
    return gender;
}

bool Persons::getAlive() const
{
    return alive;
}

int Persons::getAge() const
{
    return age;
}

//Overloads the = operator.
void Persons::operator = (const Persons& p)
{
    name = p.name;
    gender = p.gender;
    birthYear = p.birthYear;
    deathYear = p.deathYear;
    alive = p.alive;
    age = p.age;
}

//Overloads the == and != operators.
//Two persons are equal if and only if each
//parameter is equal.
bool Persons::operator == (const Persons& p)
{
    return name == p.name && gender == p.gender && birthYear == p.birthYear && deathYear == p.deathYear;
}

bool Persons::operator != (const Persons& p)
{
    return name != p.name || gender != p.gender || birthYear != p.birthYear || deathYear != p.deathYear;
}

//Overloads the << (output) operator.
//writes out the name, gender, and birthyear.
//Writes out the deathyear or, if the person is alive
//writes "Alive".
ostream& operator << (ostream& out, const Persons& p)
{
    out.width(26);
    out << left << p.getName() << "\t" << p.getGender() << "\t" << p.getBirthYear()  << "\t";

    if (!p.getAlive())
    {
        out << p.getDeathYear() << "\t";
    }
    else
    {
        out << "Alive " << "\t";
    }
    out << p.getAge() << endl;

    return out;
}

//Overloads the >> (input) operator.
//Reads the name which we know ends at a semicolon (;)
//Then reads the gender and birthyear.
//Reads either "Alive" or the deathyear.
istream& operator >> (istream& in, Persons& p)
{
    string n = " ", gdr = " ", b = " ", d = " ";
    char g = ' ';
    int bY = 0, dY =0;
    Persons def;

    in >> ws;
    getline(in, n, ';'); //The Name is read in, and we stop at the ';'.
    in >> gdr >> b >> d; //The Gender, birthYear, and either deathYear or "Alive" are read in.

    if (p.valid.validName(n))
    {
        if (gdr.length() == 1) //checks the length of the gender
        {
            g = gdr.at(0);
            if (p.valid.genderCheck(g)) //Makes sure that the gender is valid.
            {
                if (p.valid.validYear(b, bY)) //checks for a valid birth year.
                {
                    if ((d == "Alive" || d == "alive") && p.valid.birthChecks(bY, dY) == 0) //Checks whether the person is alive, and whether their age is consistent with human life expectancy.
                    {
                        p.name = n;
                        p.gender = g;
                        p.birthYear = bY;
                        p.alive = true;
                        p.deathYear = 0;
                    }
                    else if(p.valid.validYear(d, dY) && p.valid.birthChecks(bY, dY) == 0) //Checks whether the death year is valid, and whether it's consistent with the birth year.
                    {
                        p.name = n;
                        p.gender = g;
                        p.birthYear = bY;
                        p.deathYear = dY;
                        p.alive = false;
                    }
                    //Each of these, if it fails the validity checks, will make p a person equal to a person with
                    //the default constructor, which, when being loaded, will be skipped.
                    else p = def;
                }
                else p = def;
            }
            else p = def;
        }
        else p = def;
    }
    else p = def;

    return in;
}
