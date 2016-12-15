#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>

using namespace std;

class validation
{

public:
    validation();

    bool validName(const string& s);
    int birthChecks(int birthYear, int deathYear);
    bool genderCheck(char& gender);
    bool validYear(const string& s, int& year);
    bool validComputerName (const string& n);
    bool validComputerType(const string& s);
    bool maxLengthOfScientistName(const string& s);
    bool validAssociation(const int bY, const int dY, const int yM);
};


#endif // VALIDATION_H
