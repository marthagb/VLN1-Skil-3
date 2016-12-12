#ifndef DATALAYER_H
#define DATALAYER_H

#include <vector>
#include <string>
#include <fstream>
#include <QtSql>
#include "persons.h"
#include "computer.h"
#include "association.h"

using namespace std;

class DataLayer
{
    QSqlDatabase db;
    vector<Persons> scientists;
    vector<Computer> computers;
    vector<Association> associations;

    vector<int> getScientistIDs();
    vector<int> getComputerIDs();
    vector<int> getAssociationIDs();

public:
    DataLayer();

   vector<Persons> getScientistVector();
   vector<Computer> getComputerVector();
   vector<Association> getAssociationVector();

   void readScientists(int orderBy, int ascOrDesc);
   vector<int> searchScientistByName(const string n);
   vector<int> searchScientistByGender(const char g);
   vector<int> searchScientistByBirthYear(const int year);
   vector<int> searchScientistByYearRange(const int f, const int l);
   bool addScientist(const Persons& p);
   bool addScientistsFromFile(string input);
   void deleteScientist(string n);
   bool saveScientistsToFile(string input);
   void updateScientist(int variable, string value, string name);

   void readComputers(int orderBy, int ascOrDesc);
   vector<int> searchComputerByName(const string n);
   vector<int> searchComputerByYearMade(const int year);
   vector<int> searchComputerByYearRange(const int f, const int l);
   vector<int> searchComputerByType(const string type);
   bool addComputer(const Computer& c);
   bool addComputersFromFile(string input);
   void deleteComputer(string n);
   bool saveComputersToFile(string input);
   void updateComputer(int variable, string value, string name);

   void readAssociations(int orderBy, int ascOrDesc);
   vector<int> searchAssocBySciName(const string sN);
   vector<int> searchAssocByCompName(const string cN);
   vector<int> searchAssocByYear(const int year);
   vector<int> searchAssocByYearRange(const int f, const int l);
   vector<int> searchAssocByCompType(const string type);
   bool addAssociation(const Association& a);
   void deleteAssociation(string sN, string cN);
   bool saveAssociationsToFile(string input);

};

#endif // DATALAYER_H
