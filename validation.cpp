#include "validation.h"
#include <ctime>
#include <cstdlib>

using namespace std;

const int MAX = 25;
const int MIN = 3;

//Default Constructor
validation::validation()
{

}

//Checks for a valid name (no numbers allowed etc.)
bool validation::validName(const string& s)
{
    //Checks if 's' is empty or contains characters other than letters and spaces
    string::const_iterator it = s.begin();

    while (it != s.end() && (isalpha(*it) || *it == ' '))
    {
        it++;
    }

    return !s.empty() && it == s.end();
}

//Errorchecks for whether certain years entered by the user are valid.
//Checks for a maximum age.
int validation::birthChecks(int birthYear, int deathYear)
{
    time_t t = time(NULL);
    tm* TimePtr = localtime(&t);
    int currentYear = TimePtr->tm_year + 1900;

    if(deathYear < birthYear && deathYear != 0)
    {
        return 1;
    }
    if((deathYear - birthYear) > 122 || ((currentYear - birthYear) > 122 && deathYear == 0))
    {
        return 2;
    }

    return 0;
}

//makes sure the Gender is either male or female.
bool validation::genderCheck(char& gender)                                                       //komið í console
{
    if (gender == 'm' || gender == 'M' || gender == 'f' || gender == 'F')
    {
        if(gender == 'm')
        {
            gender = 'M';
        }
        if(gender == 'f')
        {
            gender = 'F';
        }

        return true;
    }
    else
    {
        return false;
    }
}

//checks whether a certain entered string is a year
//and whether it's a valid year (AKA not in the future).
bool validation::validYear(const string& s, int& year)
{
    string::const_iterator it = s.begin();
    //Checks if the string 's' is a number

    while (it != s.end() && isdigit(*it))
    {
        it++;
    }

    if (s.empty() || it != s.end())
    {
        return false;
    }

    //Checks if 'year' is positive and lower than current year
    year = atoi(s.c_str());
    time_t t = time(NULL);
    tm* TimePtr = localtime(&t);
    int currentYear = TimePtr->tm_year + 1900;

    return year >= 0 && year <= currentYear;
}

//Makes sure the computer name isn't too short or too long.
bool validation::validComputerName (const string& n)
{
    string::const_iterator it = n.begin();
    int numbersInRow = 0;
    int counter = 0;
    while (it != n.end())
    {
        it++;

        if (isdigit(*it))
        {
            counter++;
        }

        if (counter > numbersInRow)
        {
            numbersInRow = counter;
        }

        if (!(isdigit(*it)))
        {
            counter = 0;
        }
    }

    if (numbersInRow > 4)
    {
        return false;
    }

    return n.size() >= MIN && n.size() <= MAX;
}

//checks through the validName function whether the type is good, and that it's not too long.
bool validation::validComputerType(const string& s)
{
    return validName(s) && s.size() <= MAX;
}

//Makes sure the scientists name isn't too long.
bool validation::maxLengthOfScientistName(const string& s)
{
    return validName(s) && s.size() <= 50;
}

bool validation::validAssociation(const int bY, const int dY, const int yM)
{
    return yM > bY && (yM <= dY || dY == 0);
}
