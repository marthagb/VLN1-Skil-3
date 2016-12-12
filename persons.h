#ifndef PERSONS_H
#define PERSONS_H

#include <iostream>
#include <iomanip>
#include "validation.h"

using namespace std;

class Persons
{
    string name;
    int birthYear;
    int deathYear;
    char gender;
    bool alive;
    int age;
    validation valid;

public:
    Persons();
    Persons(string n, char g, int bY, int dY); //Constructor which takes in Name, gender, birthyear and deathyear (with 0 for living persons).

    string getName() const;
    int getBirthYear() const;
    int getDeathYear() const;
    char getGender() const;
    bool getAlive() const;
    int getAge() const;

    void operator = (const Persons& p);
    bool operator == (const Persons& p);
    bool operator != (const Persons& p);

    friend ostream& operator << (ostream& out, const Persons& p);
    friend istream& operator >> (istream& in, Persons& p);
};

#endif // PERSONS_H
