#ifndef SERVICELAYER_H
#define SERVICELAYER_H

#include "datalayer.h"

using namespace std;

class ServiceLayer
{
    DataLayer dl;
public:
    ServiceLayer();

    vector<Persons> listScientists();
    void sortScientists(int orderBy, int ascOrDesc);
    vector<int> searchScientistByName(const string name);
    vector<int> searchScientistByGender(const char gender);
    vector<int> searchScientistByBirthYear(const int year);
    vector<int> searchScientistByYearRange(const int f, const int l);
    bool addScientist(const Persons& p);
    bool addScientistsFromFile(string input);
    void deleteScientist(string n);
    void updateScientist(int variable, string value, string name);
    bool saveScientistsToFile(string input);

    vector<Computer> listComputers();
    void sortComputers(int orderBy, int ascOrDesc);
    vector<int> searchComputerByName(const string name);
    vector<int> searchComputerByYearMade(const int year);
    vector<int> searchComputerByYearRange(const int f, const int l);
    vector<int> searchComputerByType(const string type);
    bool addComputer(const Computer& c);
    bool addComputersFromFile(string input);
    void deleteComputer(string n);
    void updateComputer(int variable, string value, string name);
    bool saveComputersToFile(string input);

    vector<Association> listAssociations();
    void sortAssociations(int orderBy, int ascOrDesc);
    vector<int> searchAssocBySciName(const string sN);
    vector<int> searchAssocByCompName(const string cN);
    vector<int> searchAssocByYear(const int year);
    vector<int> searchAssocByYearRange(const int f, const int l);
    vector<int> searchAssocByCompType(const string type);
    bool addAssociation(const Association& a);
    void deleteAssociation(string sN, string cN);
    bool saveAssociationsToFile(string input);

};

#endif // SERVICELAYER_H
