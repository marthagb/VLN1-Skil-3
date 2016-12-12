#include "datalayer.h"

DataLayer::DataLayer()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbName = "VLN1.sqlite";
    db.setDatabaseName(dbName);
}

vector<Persons> DataLayer::getScientistVector()
{
    return scientists;
}

vector<Computer> DataLayer::getComputerVector()
{
    return computers;
}

vector<Association> DataLayer::getAssociationVector()
{
    return associations;
}

//Reads scientists from database
//'orderBy' and 'ascOrDesc' determine how the data is ordered
void DataLayer::readScientists(int orderBy, int ascOrDesc)
{
    vector<Persons> S;

    db.open();

    QSqlQuery query(db);

    if (orderBy == 0)
    {
        if(ascOrDesc == 1)
        {
            query.exec("SELECT Name, Gender, Birthyear, Deathyear FROM Scientists ORDER BY ID");
        }
        else if (ascOrDesc == 2)
        {
            query.exec("SELECT Name, Gender, Birthyear, Deathyear FROM Scientists ORDER BY ID DESC");
        }
    }
    else if (orderBy == 1)
    {
        if (ascOrDesc == 1)
        {
            query.exec("SELECT Name, Gender, Birthyear, Deathyear FROM Scientists ORDER BY Name");
        }
        else if (ascOrDesc == 2)
        {
            query.exec("SELECT Name, Gender, Birthyear, Deathyear FROM Scientists ORDER BY Name DESC");
        }
    }
    else if (orderBy == 2)
    {
        if (ascOrDesc == 1)
        {
            query.exec("SELECT Name, Gender, Birthyear, Deathyear FROM Scientists ORDER BY Gender");
        }
        else if (ascOrDesc == 2)
        {
            query.exec("SELECT Name, Gender, Birthyear, Deathyear FROM Scientists ORDER BY Gender DESC");
        }
    }
    else if (orderBy == 3)
    {
        if (ascOrDesc == 1)
        {
            query.exec("SELECT Name, Gender, Birthyear, Deathyear FROM Scientists ORDER BY Birthyear");
        }
        else if (ascOrDesc == 2)
        {
            query.exec("SELECT Name, Gender, Birthyear, Deathyear FROM Scientists ORDER BY Birthyear DESC");
        }
    }
    else if (orderBy == 4)
    {
        if (ascOrDesc == 1)
        {
            query.exec("SELECT Name, Gender, Birthyear, Deathyear FROM Scientists WHERE Deathyear > 0 ORDER BY Deathyear");
            while(query.next())
            {
                string name = query.value("Name").toString().toStdString();
                string gdr = query.value("Gender").toString().toStdString();
                char g = gdr[0];
                int bY = query.value("Birthyear").toUInt();
                int dY = query.value("Deathyear").toUInt();

                Persons p(name, g, bY, dY);
                S.push_back(p);
            }
            query.exec("SELECT Name, Gender, Birthyear, Deathyear FROM Scientists WHERE Deathyear = 0 ORDER BY ID");
        }
        else if (ascOrDesc == 2)
        {
            query.exec("SELECT Name, Gender, Birthyear, Deathyear FROM Scientists WHERE Deathyear = 0 ORDER BY ID");

            while(query.next())
            {
                string name = query.value("Name").toString().toStdString();
                string gdr = query.value("Gender").toString().toStdString();
                char g = gdr[0];
                int bY = query.value("Birthyear").toUInt();
                int dY = query.value("Deathyear").toUInt();

                Persons p(name, g, bY, dY);
                S.push_back(p);
            }
            query.exec("SELECT Name, Gender, Birthyear, Deathyear FROM Scientists WHERE Deathyear > 0 ORDER BY Deathyear DESC");
        }
    }

    while(query.next())
    {
        string name = query.value("Name").toString().toStdString();
        string gdr = query.value("Gender").toString().toStdString();
        char g = gdr[0];
        int bY = query.value("Birthyear").toUInt();
        int dY = query.value("Deathyear").toUInt();

        Persons p(name, g, bY, dY);
        S.push_back(p);
    }
    db.close();
    scientists = S;
}

//Determines whether the scientist 'p' is in the database
//and adds them if not.
bool DataLayer::addScientist(const Persons& p)
{
    if (scientists.size() == 0)
    {
        readScientists(1,1);
    }
    for (unsigned int i = 0; i < scientists.size(); i++)
    {
        if (scientists[i] == p)
        {
            return false;
        }
    }

    db.open();

    QSqlQuery query(db);

    query.prepare("INSERT INTO Scientists(Name, Gender, Birthyear, Deathyear, Alive) "
                  "VALUES (:Name, :Gender, :Birthyear, :Deathyear, :Alive)");
    query.bindValue(0, QString::fromStdString(p.getName()));
    query.bindValue(1, QVariant(p.getGender()).toChar());
    query.bindValue(2, QVariant(p.getBirthYear()));
    query.bindValue(3, QVariant(p.getDeathYear()));
    if (p.getAlive())
    {
        query.bindValue(4, QString::fromStdString("Yes"));
    }
    else
    {
        query.bindValue(4, QString::fromStdString("No"));
    }

    query.exec();

    db.close();

    scientists.push_back(p);
    return true;
}

//Adds scientists to the database from the file 'input'
bool DataLayer::addScientistsFromFile(string input)
{
    Persons p;
    ifstream in;

    in.open(input);

    if (in.fail())
    {
        in.close();
        return false;
    }
    else
    {
        in.seekg(100);

        while(in >> p)
        {
            //Checks if person is valid, i.e. has a valid name, gender, birthyear and deathyear.
            //An invalid person will not be added.
            Persons compare;
            if (p != compare)
            {
                addScientist(p);
            }
        }
        in.close();

        return true;
    }
}

//Returns a vector containing scientists' IDs from the database.
//A scientist's ID's place in this vector corresponds to their place in the 'scientists' vector,
//if the 'scientists' vector is ordered alphabetically.
vector<int> DataLayer::getScientistIDs()
{
    vector<int> sID;
    db.open();

    QSqlQuery query(db);

    query.exec("SELECT ID FROM Scientists ORDER BY Name");

    while (query.next())
    {
        int id = query.value("ID").toUInt();
        sID.push_back(id);
    }

    db.close();
    return sID;
}

//Returns a vector containing the places in the 'scientists' vector
//of people whose names contain 'name' as a substring.
vector<int> DataLayer::searchScientistByName(const string name)
{
    vector<int> vSN;
    vector<int> sIDs = getScientistIDs();
    db.open();

    QSqlQuery query(db);

    query.exec("SELECT ID FROM Scientists WHERE Name LIKE '%" + QString::fromStdString(name) + "%' ORDER BY Name");

    while (query.next())
    {
        int id = query.value("ID").toUInt();
        for (unsigned int i = 0; i < sIDs.size(); i++)
        {
            if (id == sIDs[i])
            {
                vSN.push_back(i);
                break;
            }
        }
    }

    db.close();
    return vSN;
}

//Returns a vector containing the places in the 'scientists' vector
//of people of the given gender.
vector<int> DataLayer::searchScientistByGender(const char gender)
{
    vector<int> vSG;
    vector<int> sIDs = getScientistIDs();
    db.open();

    QSqlQuery query(db);

    query.exec("SELECT ID FROM Scientists WHERE Gender = '" + QString(QVariant(gender).toChar()) + "' ORDER BY Name");

    while (query.next())
    {
        int id = query.value("ID").toUInt();
        for (unsigned int i = 0; i < sIDs.size(); i++)
        {
            if (id == sIDs[i])
            {
                vSG.push_back(i);
                break;
            }
        }
    }

    db.close();
    return vSG;
}

//Returns a vector containing the places in the 'scientists' vector
//of people born in the given year.
vector<int> DataLayer::searchScientistByBirthYear(const int year)
{
    vector<int> vSBY;
    vector<int> sIDs = getScientistIDs();
    db.open();

    QSqlQuery query(db);

    query.exec("SELECT ID FROM Scientists WHERE birthYear = " + QVariant(year).toString() + " ORDER BY Name");

    while (query.next())
    {
        int id = query.value("ID").toUInt();
        for (unsigned int i = 0; i < sIDs.size(); i++)
        {
            if (id == sIDs[i])
            {
                vSBY.push_back(i);
                break;
            }
        }
    }

    db.close();
    return vSBY;
}

//Returns a vector containing the places in the 'scientists' vector
//of people born in the given year range.
vector<int> DataLayer::searchScientistByYearRange(const int f, const int l)
{
    vector<int> vSBR;
    vector<int> sIDs = getScientistIDs();
    db.open();

    QSqlQuery query(db);

    query.exec("SELECT ID FROM Scientists WHERE birthYear >= " + QVariant(f).toString() + " AND birthYear <= " + QVariant(l).toString() + " ORDER BY Name");

    while (query.next())
    {
        int id = query.value("ID").toUInt();
        for (unsigned int i = 0; i < sIDs.size(); i++)
        {
            if (id == sIDs[i])
            {
                vSBR.push_back(i);
                break;
            }
        }
    }

    db.close();
    return vSBR;
}

//Deletes scientists whose names contain 'n' as a substring.
void DataLayer::deleteScientist(string n)
{
    db.open();

    QSqlQuery query(db);

    query.exec("DELETE FROM Scientists WHERE Name LIKE '%" + QString::fromStdString(n) + "%'");

    db.close();

    readScientists(1,1);
}

//Saves a list of the scientists in the database to the file 'input'.
bool DataLayer::saveScientistsToFile(string input)
{
    if(scientists.size() == 0)
    {
        readScientists(1,1);
    }

   ofstream out;
   out.open(input);

   if(out.fail())
   {
               return false;
   }
    else
   {
       out.width(26);
       out << left << "Name";
       out << "\tGender\tBorn\tDied" << endl;
       out << "_____________________________________________________" << endl;

       for(size_t i = 0; i < scientists.size(); i++)
       {
           out << left << scientists[i].getName();
           out.width(26 - scientists[i].getName().length());
           out << ";" << "\t" << scientists[i].getGender() << "\t" << scientists[i].getBirthYear() << "\t";
           if(scientists[i].getAlive())
           {
               out << "Alive" << endl;
           }
           else
           {
               out << scientists[i].getDeathYear() << endl;
           }
       }
       out << "_____________________________________________________" << endl;

    }
           out.close();
           return true;
}

//Updates the scientist whose name is 'name'
//'variable' determines what field of information is updated
//and 'value' is the new value for that field.
void DataLayer::updateScientist(int variable, string value, string name)
{
    db.open();

    QSqlQuery query(db);


    if (variable == 1)
    {
        query.exec("UPDATE Scientists SET Name = '" + QString::fromStdString(value) + "' WHERE Name = '" + QString::fromStdString(name) + "'");
    }
    else if (variable == 2)
    {
        query.exec("UPDATE Scientists SET Gender = '" + QString::fromStdString(value) + "' WHERE Name = '" + QString::fromStdString(name) + "'");
    }
    else if (variable == 3)
    {
        query.exec("UPDATE Scientists SET Birthyear = '" + QString::fromStdString(value) + "' WHERE Name = '" + QString::fromStdString(name) + "'");
    }
    else if (variable == 4)
    {
        query.exec("UPDATE Scientists SET Deathyear = '" + QString::fromStdString(value) + "' WHERE Name = '" + QString::fromStdString(name) + "'");
    }

    db.close();
}

//Reads computers from database
//'orderBy' and 'ascOrDesc' determine how the data is ordered
void DataLayer::readComputers(int orderBy, int ascOrDesc)
{
    db.open();

    QSqlQuery query(db);

    if (orderBy == 0)
    {
        if (ascOrDesc == 1)
        {
            query.exec("SELECT ComputerName, YearMade, Type, BuiltOrNot FROM Computers ORDER BY ComputerID");
        }
        else if (ascOrDesc == 2)
        {
            query.exec("SELECT ComputerName, YearMade, Type, BuiltOrNot FROM Computers ORDER BY ComputerID DESC");
        }
    }
    else if (orderBy == 1)
    {
        if (ascOrDesc == 1)
        {
            query.exec("SELECT ComputerName, YearMade, Type, BuiltOrNot FROM Computers ORDER BY ComputerName");
        }
        else if (ascOrDesc == 2)
        {
            query.exec("SELECT ComputerName, YearMade, Type, BuiltOrNot FROM Computers ORDER BY ComputerName DESC");
        }
    }
    else if (orderBy == 2)
    {
        if (ascOrDesc == 1)
        {
            query.exec("SELECT ComputerName, YearMade, Type, BuiltOrNot FROM Computers ORDER BY YearMade");
        }
        else if (ascOrDesc == 2)
        {
            query.exec("SELECT ComputerName, YearMade, Type, BuiltOrNot FROM Computers ORDER BY YearMade DESC");
        }
    }
    else if (orderBy == 3)
    {
        if (ascOrDesc == 1)
        {
            query.exec("SELECT ComputerName, YearMade, Type, BuiltOrNot FROM Computers ORDER BY Type");
        }
        else if (ascOrDesc == 2)
        {
            query.exec("SELECT ComputerName, YearMade, Type, BuiltOrNot FROM Computers ORDER BY Type DESC");
        }
    }
    else if (orderBy == 4)
    {
        if (ascOrDesc == 1)
        {
            query.exec("SELECT ComputerName, YearMade, Type, BuiltOrNot FROM Computers ORDER BY BuiltOrNot");
        }
        else if (ascOrDesc == 2)
        {
            query.exec("SELECT ComputerName, YearMade, Type, BuiltOrNot FROM Computers ORDER BY BuiltOrNot DESC");
        }
    }

    vector<Computer> C;
    while(query.next())
    {
        string n = query.value("ComputerName").toString().toStdString();
        int yM = query.value("YearMade").toUInt();
        string t = query.value("Type").toString().toStdString();
        string built = query.value("BuiltOrNot").toString().toStdString();
        bool b = false;
        if (built == "Built")
        {
            b = true;
        }

        Computer c(n, yM, t, b);
        C.push_back(c);
    }
    db.close();
    computers = C;
}

//Determines whether the computer 'c' is in the database
//and adds it if not.
bool DataLayer::addComputer(const Computer& c)
{
    if (computers.size() == 0)
    {
        readComputers(1,1);
    }
    for (unsigned int i = 0; i < computers.size(); i++)
    {
        if (computers[i] == c)
        {
            return false;
        }
    }

    db.open();

    QSqlQuery query(db);

    query.prepare("INSERT INTO Computers(ComputerName, YearMade, Type, BuiltOrNot) "
                          "VALUES (:ComputerName, :YearMade, :Type, :BuiltOrNot)");
    query.bindValue(0, QString::fromStdString(c.getComputerName()));
    query.bindValue(1, QVariant(c.getYearMade()));
    query.bindValue(2, QString::fromStdString(c.getType()));
    if (c.getBuiltOrNot())
    {
        query.bindValue(3, QString::fromStdString("Built"));
    }
    else
    {
        query.bindValue(3, QString::fromStdString("Not Built"));
    }
    query.exec();

    db.close();

    computers.push_back(c);
    return true;
}

//Adds computers to the database from the file 'input'
bool DataLayer::addComputersFromFile(string input)
{
    Computer c;
    ifstream in;

    in.open(input);

    if (in.fail())
    {
        in.close();
        return false;
    }
    else
    {
        in.seekg(150);

        while(in >> c)
        {
            //Checks if person is valid, i.e. has a valid name, gender, birthyear and deathyear.
            //An invalid person will not be added.
            Computer compare;
            if (c != compare)
            {
                addComputer(c);
            }
        }
        in.close();

        return true;
    }
}

//Returns a vector containing computers' IDs from the database.
//A computer's ID's place in this vector corresponds to its place in the 'computers' vector,
//if the 'computers' vector is ordered alphabetically.
vector<int> DataLayer::getComputerIDs()
{
    vector<int> cID;
    db.open();

    QSqlQuery query(db);

    query.exec("SELECT ComputerID FROM Computers ORDER BY ComputerName");

    while (query.next())
    {
        int id = query.value("ComputerID").toUInt();
        cID.push_back(id);
    }

    db.close();
    return cID;
}

//Returns a vector containing the places in the 'computers' vector
//of computers with names that contain 'name' as a substring.
vector<int> DataLayer::searchComputerByName(const string name)
{
    vector<int> vCBN;
    vector<int> cIDs = getComputerIDs();
    db.open();

    QSqlQuery query(db);

    query.exec("SELECT ComputerID FROM Computers WHERE ComputerName LIKE '%" + QString::fromStdString(name) + "%' ORDER BY ComputerName");

    while (query.next())
    {
        int id = query.value("ComputerID").toUInt();
        for (unsigned int i = 0; i < cIDs.size(); i++)
        {
            if (id == cIDs[i])
            {
                vCBN.push_back(i);
                break;
            }
        }
    }

    db.close();
    return vCBN;
}

//Returns a vector of places in the 'computers' vector
//of computers made in the given year.
vector<int> DataLayer::searchComputerByYearMade(const int year)
{
    vector<int> vCYM;
    vector<int> cIDs = getComputerIDs();
    db.open();

    QSqlQuery query(db);

    query.exec("SELECT ComputerID FROM Computers WHERE YearMade = " + QVariant(year).toString() + " ORDER BY ComputerName");

    while (query.next())
    {
        int id = query.value("ComputerID").toUInt();
        for (unsigned int i = 0; i < cIDs.size(); i++)
        {
            if (id == cIDs[i])
            {
                vCYM.push_back(i);
                break;
            }
        }
    }

    db.close();
    return vCYM;
}

//Returns a vector of places in the 'computers' vector
//of computers made in the given year range.
vector<int> DataLayer::searchComputerByYearRange(const int f, const int l)
{
    vector<int> vCYR;
    vector<int> cIDs = getComputerIDs();
    db.open();

    QSqlQuery query(db);

    query.exec("SELECT ComputerID FROM Computers WHERE YearMade >= " + QVariant(f).toString() + " AND YearMade <= " + QVariant(l).toString() + " ORDER BY ComputerName");

    while (query.next())
    {
        int id = query.value("ComputerID").toUInt();
        for (unsigned int i = 0; i < cIDs.size(); i++)
        {
            if (id == cIDs[i])
            {
                vCYR.push_back(i);
                break;
            }
        }
    }

    db.close();
    return vCYR;
}

//Returns a vector of places in the 'computers' vector
//of computers of types that have 'type' as a substring.
vector<int> DataLayer::searchComputerByType(const string type)
{
    vector<int> vCBT;
    vector<int> cIDs = getComputerIDs();
    db.open();

    QSqlQuery query(db);

    query.exec("SELECT ComputerID FROM Computers WHERE Type LIKE '%" + QString::fromStdString(type) + "%' ORDER BY ComputerName");

    while (query.next())
    {
        int id = query.value("ComputerID").toUInt();
        for (unsigned int i = 0; i < cIDs.size(); i++)
        {
            if (id == cIDs[i])
            {
                vCBT.push_back(i);
                break;
            }
        }
    }

    db.close();
    return vCBT;
}

//Deletes computers with names that contain 'n' as a substring.
void DataLayer::deleteComputer(string n)
{
    db.open();

    QSqlQuery query(db);

    query.exec("DELETE FROM Computers WHERE ComputerName LIKE '%" + QString::fromStdString(n) + "%'");

    db.close();

    readComputers(1,1);
}

//Saves a list of the computers in the database to the file 'input'.
bool DataLayer::saveComputersToFile(string input)
{
    if(computers.size() == 0)
    {
        readComputers(1,1);
    }

   ofstream out;
   out.open(input);

   if(out.fail())
   {
         return false;
   }
    else
   {
       out.width(20);
       out << left << "Name";
       out << "\tYear\t";
       out.width(30);
       out << "Computer Type\t" << "Built?" << endl;
       out << "___________________________________________________________________________________" << endl;
       out << endl;
       for(size_t i = 0; i < computers.size(); i++)
       {
            out << left << computers[i].getComputerName();
            out.width(20 - computers[i].getComputerName().length());
            out << ";" << "\t" << computers[i].getYearMade() << "\t" ;
            out << left << computers[i].getType();
            out.width(25 - computers[i].getType().length());
            out << ";" << "\t" ;
            if(computers[i].getBuiltOrNot())
            {
                out << "Built;" << endl;
            }
            else
            {
                out << "Not built;" << endl;
            }

       }
       out << "___________________________________________________________________________________" << endl;

    }
           out.close();
           return true;
}

//Updates the computer of the name 'name'
//'variable' determines what field of information is updated
//and 'value' is the new value for that field.
void DataLayer::updateComputer(int variable, string value, string name)
{
    db.open();

    QSqlQuery query(db);

    if (variable == 1)
    {
        query.exec("UPDATE Computers SET ComputerName = '" + QString::fromStdString(value) + "' WHERE ComputerName = '" + QString::fromStdString(name) + "'");
    }
    else if (variable == 2)
    {
        query.exec("UPDATE Computers SET YearMade = '" + QString::fromStdString(value) + "'WHERE ComputerName = '" + QString::fromStdString(name) + "'");
    }
    else if (variable == 3)
    {
        query.exec("UPDATE Computers SET Type = '" + QString::fromStdString(value) + "' WHERE ComputerName = '" + QString::fromStdString(name) + "'");
    }
    else if (variable == 4)
    {
        query.exec("UPDATE Computers SET BuiltOrNot = '" + QString::fromStdString(value) + "' WHERE ComputerName = '" + QString::fromStdString(name) + "'");
    }

    db.close();
}

//Reads associations from database
//'orderBy' and 'ascOrDesc' determine how the data is ordered
void DataLayer::readAssociations(int orderBy, int ascOrDesc)
{
    readScientists(1,1);
    readComputers(1,1);
    db.open();
    QSqlQuery query(db);

    if (orderBy == 0)
    {
        if (ascOrDesc == 1)
        {
            query.exec("SELECT s.Name, c.ComputerName "
                             "FROM Scientists s "
                             "INNER JOIN Associations a ON s.ID = a.ScientistID "
                             "INNER JOIN Computers c ON a.ComputerID = c.ComputerID "
                             "ORDER BY a.ConnectionID");
        }
        else if (ascOrDesc == 2)
        {
            query.exec("SELECT s.Name, c.ComputerName "
                             "FROM Scientists s "
                             "INNER JOIN Associations a ON s.ID = a.ScientistID "
                             "INNER JOIN Computers c ON a.ComputerID = c.ComputerID "
                             "ORDER BY a.ConnectionID DESC");
        }
    }
    else if (orderBy == 1)
    {
        if (ascOrDesc == 1)
        {
            query.exec("SELECT s.Name, c.ComputerName "
                             "FROM Scientists s "
                             "INNER JOIN Associations a ON s.ID = a.ScientistID "
                             "INNER JOIN Computers c ON a.ComputerID = c.ComputerID "
                             "ORDER BY s.Name");
        }
        else if (ascOrDesc == 2)
        {
            query.exec("SELECT s.Name, c.ComputerName "
                             "FROM Scientists s "
                             "INNER JOIN Associations a ON s.ID = a.ScientistID "
                             "INNER JOIN Computers c ON a.ComputerID = c.ComputerID "
                             "ORDER BY s.Name DESC");
        }
    }
    else if (orderBy == 2)
    {
        if (ascOrDesc == 1)
        {
            query.exec("SELECT s.Name, c.ComputerName "
                             "FROM Scientists s "
                             "INNER JOIN Associations a ON s.ID = a.ScientistID "
                             "INNER JOIN Computers c ON a.ComputerID = c.ComputerID "
                             "ORDER BY c.ComputerName");
        }
        else if (ascOrDesc == 2)
        {
            query.exec("SELECT s.Name, c.ComputerName "
                             "FROM Scientists s "
                             "INNER JOIN Associations a ON s.ID = a.ScientistID "
                             "INNER JOIN Computers c ON a.ComputerID = c.ComputerID "
                             "ORDER BY c.ComputerName DESC");
        }
    }
    else if (orderBy == 3)
    {
        if (ascOrDesc == 1)
        {
            query.exec("SELECT s.Name, c.ComputerName "
                             "FROM Scientists s "
                             "INNER JOIN Associations a ON s.ID = a.ScientistID "
                             "INNER JOIN Computers c ON a.ComputerID = c.ComputerID "
                             "ORDER BY c.YearMade");
        }
        else if (ascOrDesc == 2)
        {
            query.exec("SELECT s.Name, c.ComputerName "
                             "FROM Scientists s "
                             "INNER JOIN Associations a ON s.ID = a.ScientistID "
                             "INNER JOIN Computers c ON a.ComputerID = c.ComputerID "
                             "ORDER BY c.YearMade DESC");
        }
    }
    else if (orderBy == 4)
    {
        if (ascOrDesc == 1)
        {
            query.exec("SELECT s.Name, c.ComputerName "
                             "FROM Scientists s "
                             "INNER JOIN Associations a ON s.ID = a.ScientistID "
                             "INNER JOIN Computers c ON a.ComputerID = c.ComputerID "
                             "ORDER BY c.BuiltOrNot");
        }
        else if (ascOrDesc == 2)
        {
            query.exec("SELECT s.Name, c.ComputerName "
                             "FROM Scientists s "
                             "INNER JOIN Associations a ON s.ID = a.ScientistID "
                             "INNER JOIN Computers c ON a.ComputerID = c.ComputerID "
                             "ORDER BY c.BuiltOrNot DESC");
        }
    }
    else if (orderBy == 5)
    {
        if (ascOrDesc == 1)
        {
            query.exec("SELECT s.Name, c.ComputerName "
                             "FROM Scientists s "
                             "INNER JOIN Associations a ON s.ID = a.ScientistID "
                             "INNER JOIN Computers c ON a.ComputerID = c.ComputerID "
                             "ORDER BY c.Type");
        }
        else if (ascOrDesc == 2)
        {
            query.exec("SELECT s.Name, c.ComputerName "
                             "FROM Scientists s "
                             "INNER JOIN Associations a ON s.ID = a.ScientistID "
                             "INNER JOIN Computers c ON a.ComputerID = c.ComputerID "
                             "ORDER BY c.Type DESC");
        }
    }

    vector<string> sN;
    vector<string> cN;
    while(query.next())
    {
        sN.push_back(query.value("Name").toString().toStdString());
        cN.push_back(query.value("ComputerName").toString().toStdString());
    }
    db.close();
    vector<Association> A;
    for (unsigned int i = 0; i < sN.size(); i++)
    {
        Persons s = getScientistVector()[searchScientistByName(sN[i])[0]];
        Computer c = getComputerVector()[searchComputerByName(cN[i])[0]];
        Association a(s, c);
        A.push_back(a);
    }
    associations = A;
}

//Determines whether the association 'a' is in the database
//and adds it if not.
bool DataLayer::addAssociation(const Association& a)
{
    if (associations.size() == 0)
    {
        readAssociations(1,1);
    }
    for (unsigned int i = 0; i < associations.size(); i++)
    {
        if (associations[i] == a)
        {
            return false;
        }
    }
    int sID = 0, cID = 0;
    db.open();
    QSqlQuery query1(db);

    query1.exec("SELECT ID FROM Scientists "
                           "WHERE Name LIKE '" + QString::fromStdString(a.getScientistName()) + "'");
    while (query1.next())
    {
        sID = query1.value("ID").toUInt();
    }

    QSqlQuery query2(db);

    query2.exec("SELECT ComputerID FROM Computers "
                           "WHERE ComputerName LIKE '" + QString::fromStdString(a.getComputerName()) + "'");
    while (query2.next())
    {
        cID = query2.value("ComputerID").toUInt();
    }

    QSqlQuery query3(db);

    query3.exec("INSERT INTO Associations(ScientistID, ComputerID) "
                           "VALUES (" + QVariant(sID).toString() + ", " + QVariant(cID).toString() + ")");

    db.close();

    associations.push_back(a);
    return true;
}

//Returns a vector containing association's IDs from the database.
//An association's ID's place in this vector corresponds to its place in the 'associations' vector,
//if the 'associations' vector is ordered by ID.
vector<int> DataLayer::getAssociationIDs()
{
    vector<int> aID;
    db.open();

    QSqlQuery query(db);

    query.exec("SELECT ConnectionID FROM Associations ORDER BY ConnectionID");
    while (query.next())
    {
        int id = query.value("ConnectionID").toUInt();
        aID.push_back(id);
    }

    db.close();
    return aID;
}


//Returns a vector of places in the 'associations' vector
//of associations with scientists whose names contain 'sN' as a substring.
vector<int> DataLayer::searchAssocBySciName(const string sN)
{
    vector<int> vASN;
    vector<int> aID = getAssociationIDs();
    db.open();

    QSqlQuery query(db);

    query.exec("SELECT a.ConnectionID FROM Associations a "
               "INNER JOIN Scientists s ON a.ScientistID = s.ID "
               "WHERE s.Name LIKE '%" + QString::fromStdString(sN) + "%' ORDER BY a.ConnectionID");

    while (query.next())
    {
        int id = query.value("ConnectionID").toUInt();
        for (unsigned int i = 0; i < aID.size(); i++)
        {
            if (id == aID[i])
            {
                vASN.push_back(i);
                break;
            }
        }
    }

    db.close();
    return vASN;
}

//Returns a vector of places in the 'associations' vector
//of associations with computers with names that contain 'cN' as a substring.
vector<int> DataLayer::searchAssocByCompName(const string cN)
{
    vector<int> vACN;
    vector<int> aID = getAssociationIDs();
    db.open();

    QSqlQuery query(db);

    query.exec("SELECT a.ConnectionID FROM Associations a "
               "INNER JOIN Computers c ON a.ComputerID = c.ComputerID "
               "WHERE c.ComputerName LIKE '%" + QString::fromStdString(cN) + "%' ORDER BY a.ConnectionID");

    while (query.next())
    {
        int id = query.value("ConnectionID").toUInt();
        for (unsigned int i = 0; i < aID.size(); i++)
        {
            if (id == aID[i])
            {
                vACN.push_back(i);
                break;
            }
        }
    }

    db.close();
    return vACN;
}

//Returns a vector of places in the 'associations' vector
//of associations with computers made in the given year.
vector<int> DataLayer::searchAssocByYear(const int year)
{
    vector<int> vAY;
    vector<int> aID = getAssociationIDs();
    db.open();

    QSqlQuery query(db);

    query.exec("SELECT a.ConnectionID FROM Associations a "
               "INNER JOIN Computers c ON a.ComputerID = c.ComputerID "
               "WHERE c.YearMade = " + QVariant(year).toString() + " ORDER BY a.ConnectionID");

    while (query.next())
    {
        int id = query.value("ConnectionID").toUInt();
        for (unsigned int i = 0; i < aID.size(); i++)
        {
            if (id == aID[i])
            {
                vAY.push_back(i);
                break;
            }
        }
    }

    db.close();
    return vAY;
}

//Returns a vector of places in the 'associations' vector
//of associations with computers made in the given year range.
vector<int> DataLayer::searchAssocByYearRange(const int f, const int l)
{
    vector<int> vAYR;
    vector<int> aID = getAssociationIDs();
    db.open();

    QSqlQuery query(db);

    query.exec("SELECT a.ConnectionID FROM Associations a "
               "INNER JOIN Computers c ON a.ComputerID = c.ComputerID "
               "WHERE c.YearMade >= " + QVariant(f).toString() + " AND c.YearMade <= " + QVariant(l).toString() + " ORDER BY a.ConnectionID");

    while (query.next())
    {
        int id = query.value("ConnectionID").toUInt();
        for (unsigned int i = 0; i < aID.size(); i++)
        {
            if (id == aID[i])
            {
                vAYR.push_back(i);
                break;
            }
        }
    }

    db.close();
    return vAYR;
}

//Returns a vector of places in the 'associations' vector
//of associations with computers of types that have 'type' as a substring.
vector<int> DataLayer::searchAssocByCompType(const string type)
{
    vector<int> vACT;
    vector<int> aID = getAssociationIDs();
    db.open();

    QSqlQuery query(db);

    query.exec("SELECT a.ConnectionID FROM Associations a "
               "INNER JOIN Computers c ON a.ComputerID = c.ComputerID "
               "WHERE c.Type LIKE '%" + QString::fromStdString(type) + "%' ORDER BY a.ConnectionID");

    while (query.next())
    {
        int id = query.value("ConnectionID").toUInt();
        for (unsigned int i = 0; i < aID.size(); i++)
        {
            if (id == aID[i])
            {
                vACT.push_back(i);
                break;
            }
        }
    }

    db.close();
    return vACT;
}

//Deletes the association of the scientist 'sN' and the computer 'cN'.
void DataLayer::deleteAssociation(string sN, string cN)
{
    int sID = 0, cID = 0;
    db.open();
    QSqlQuery query1(db);

    query1.exec("SELECT ID FROM Scientists "
                "WHERE Name LIKE '" + QString::fromStdString(sN) + "'");
    while (query1.next())
    {
        sID = query1.value("ID").toUInt();
    }

    QSqlQuery query2(db);

    query2.exec("SELECT ComputerID FROM Computers "
                "WHERE ComputerName LIKE '" + QString::fromStdString(cN) + "'");
    while (query2.next())
    {
        cID = query2.value("ComputerID").toUInt();
    }

    QSqlQuery query3(db);

    query3.exec("DELETE FROM Associations WHERE ScientistID = " + QVariant(sID).toString() + " AND ComputerID = " + QVariant(cID).toString());

    db.close();

    readAssociations(1,1);
}

//Saves a list of the associations in the database to the file 'input'.
bool DataLayer::saveAssociationsToFile(string input)
{
    if(associations.size() == 0)
    {
        readAssociations(1,1);
    }

    ofstream out;
    out.open(input);

    if(out.fail())
    {
        return false;
    }
    else
    {
        out.width(26);
        out << left << "Scientist\t";
        out.width(16);
        out << left << "Computer\t";
        out << "Year Made\t";
        out.width(15);
        out << "Built?\t" << "Computer Type" << endl;
        out << "______________________________________________________________________________________________________________________" << endl;

        out << endl;
        for(size_t i = 0; i < associations.size(); i++)
        {
            out << associations[i];
        }

        out << "______________________________________________________________________________________________________________________" << endl;

    }
    out.close();
    return true;
}
