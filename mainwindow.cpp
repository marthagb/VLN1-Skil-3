#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addscientistdialog.h"
#include "addcomputerdialog.h"
#include "addassociationdialog.h"
#include "updatescientist.h"
#include "updatecomputer.h"
#include <QMessageBox>
#include "savescientiststofiledialog.h"
#include "savecomputerstofiledialog.h"
#include "saveassociationstofiledialog.h"
#include "loadscientistsfromfiledialog.h"
#include "loadcomputersfromfile.h"
#include "updatescientist.h"
#include "updatecomputer.h"
#include "scientistsinformationwindowdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainOptions->setCurrentIndex(0);
    ui->searchInputScientists->setPlaceholderText(QString::fromStdString("Enter name"));
    ui->lastYearInputScientist->hide();
    ui->noScientistFoundLabel->hide();
    ui->noComputerFoundLabel->hide();
    ui->noAssociationFoundLabel->hide();

    showScientists(serve.listScientists());
}

MainWindow::~MainWindow()
{
    delete ui;
}

// When add button is pressed then a add window is executed
// in the add window you will add name,gender,YearBorn and if the scientist is alive
// And you have the option to add a picture and fun facts
// if you make a mistake then a pop up window will ask you if you want to try again.
void MainWindow::on_addScientistButton_clicked()
{
    addScientistDialog addScientist;
    addScientist.setModal(true);
    addScientist.exec();

    if (addScientist.getAdd())
    {
        Persons s = addScientist.newScientist();

        if (valid.maxLengthOfScientistName(s.getName()))
        {
            if (valid.birthChecks(s.getBirthYear(), s.getDeathYear()) == 0)
            {
                addNewScientist(s);
                if (addScientist.getBtnImageClicked())
                {
                    serve.addPicToScientist(addScientist.getFile(), s.getName());
                }

                showScientists(serve.listScientists());
            }
            else if (valid.birthChecks(s.getBirthYear(), s.getDeathYear()) == 1)
            {
                int reply = QMessageBox::question(this, "Inconsistent years", "A person can not die before they are born!\nTry again?",
                                                  QMessageBox::Yes | QMessageBox::No);

                if (reply == QMessageBox::Yes)
                {
                    on_addScientistButton_clicked();
                }
                else if (reply == QMessageBox::No)
                {
                    ui->statusBar->showMessage("Add scientist cancelled", 2500);
                }
            }
            else if (valid.birthChecks(s.getBirthYear(), s.getDeathYear()) == 2)
            {
                int reply = QMessageBox::question(this, "Inconsistent years", "That is too old!\nTry again?",
                                                  QMessageBox::Yes | QMessageBox::No);

                if (reply == QMessageBox::Yes)
                {
                    on_addScientistButton_clicked();
                }
                else if (reply == QMessageBox::No)
                {
                    ui->statusBar->showMessage("Add scientist cancelled", 2500);
                }
            }
        }
        else
        {
            int reply = QMessageBox::question(this, "Name not valid", "Invalid input for name!\nTry again?",
                                              QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::Yes)
            {
                on_addScientistButton_clicked();
            }
            else if (reply == QMessageBox::No)
            {
                ui->statusBar->showMessage("Add scientist cancelled", 2500);
            }
        }
    }
}

void MainWindow::addNewScientist(const Persons &p)
{
    serve.addScientist(p);
}

// When you click on the delete button there will pop up a
// new window that asks you if you are sure you want to delete.
void MainWindow::on_deleteScientistButton_clicked()
{
    int reply = QMessageBox::question(this, "Confirm delete", "Delete selected scientist?",
                                      QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        int r = ui->scientistTable->currentRow();
        string n = ui->scientistTable->item(r, 0)->text().toStdString();
        serve.deleteScientist(n);

        showScientists(serve.listScientists());
    }
    else if (reply == QMessageBox::No)
    {
        ui->statusBar->showMessage("Delete scientist cancelled", 2500);
    }

    ui->deleteScientistButton->setEnabled(false);
    ui->updateScientistButton->setEnabled(false);
}

// when the update button is clicked there will pop up another window
// and you can change information about the selected scientist
// You will then have the option to add a picture and fun facts
// if you input strange information then you will be asked if you want to try again.
void MainWindow::on_updateScientistButton_clicked()
{
    Persons s;
    int r = ui->scientistTable->currentRow();
    string n = ui->scientistTable->item(r,0)->text().toStdString();
    string g = ui->scientistTable->item(r,1)->text().toStdString();
    int bY = ui->scientistTable->item(r,2)->text().toUInt();

    updatescientist updateScientist;
    updateScientist.setModal(true);
    updateScientist.setName(n);
    updateScientist.setGender(g);
    updateScientist.setBirthYear(bY);
    updateScientist.setPic(serve.showPicOfScientists(n));

    if(ui->scientistTable->item(r,3))
    {
        int dY = ui->scientistTable->item(r,3)->text().toUInt();
        updateScientist.setDeathYear(dY);
    }
    else
    {
        updateScientist.setCheckBox();
    }

    updateScientist.exec();

    if(updateScientist.getUpdate())
    {
        string name = updateScientist.getName();            //name update

        if(valid.maxLengthOfScientistName(name))
        {
            serve.updateScientist(1, name, n);
            string gender = updateScientist.getGender();
            serve.updateScientist(2, gender, name);

            string birthYear = updateScientist.getBirthYear();
            int b = atoi(birthYear.c_str());
            string deathYear = updateScientist.getDeathYear();
            int d = atoi(deathYear.c_str());

            if(!updateScientist.getCheckBox())
            {
                if(valid.birthChecks(b, d) == 0)
                {
                    serve.updateScientist(3, birthYear, name);
                    serve.updateScientist(4, deathYear, name);
                    if(updateScientist.getUpdatePictureButton())
                    {
                        serve.addPicToScientist(updateScientist.getFile(), name);
                    }
                }
                else if (valid.birthChecks(b, d) == 1)
                {
                    int reply = QMessageBox::question(this, "Inconsistent years", "A person can not die before they are born!\nTry again?",
                                                                      QMessageBox::Yes | QMessageBox::No);

                    if (reply == QMessageBox::Yes)
                    {
                        on_updateScientistButton_clicked();
                    }
                    else if (reply == QMessageBox::No)
                    {
                        ui->statusBar->showMessage("Update scientist cancelled", 2500);
                    }
                }
                else if (valid.birthChecks(b, d) == 2)
                {
                    int reply = QMessageBox::question(this, "Inconsistent years", "That is too old!\nTry again?",
                                                      QMessageBox::Yes | QMessageBox::No);

                    if (reply == QMessageBox::Yes)
                    {
                        on_updateScientistButton_clicked();
                    }
                    else if (reply == QMessageBox::No)
                    {
                        ui->statusBar->showMessage("Update scientist cancelled", 2500);
                    }
                }
            }
            else if(updateScientist.getCheckBox())
            {
                deathYear = "0";
                serve.updateScientist(4, deathYear, name);
                if(updateScientist.getUpdatePictureButton())
                {
                    serve.addPicToScientist(updateScientist.getFile(), name);
                }

                if(b < 1894)
                {
                    int reply = QMessageBox::question(this, "Inconsistent years", "That is too old!\nTry again?",
                                                      QMessageBox::Yes | QMessageBox::No);

                    if (reply == QMessageBox::Yes)
                    {
                        on_updateScientistButton_clicked();
                    }
                    else if (reply == QMessageBox::No)
                    {
                        ui->statusBar->showMessage("Update scientist cancelled", 2500);
                    }
                }
                else
                {
                    serve.updateScientist(3, birthYear, name);
                }
            }
        }
        else if (!valid.maxLengthOfScientistName(name))
        {
            int reply = QMessageBox::question(this, "Name not valid", "Invalid input for name!\nTry again?",
                                              QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::Yes)
            {
                on_updateScientistButton_clicked();
            }
            else if (reply == QMessageBox::No)
            {
                ui->statusBar->showMessage("Update scientist cancelled", 2500);
            }
        }
    }

    serve.sortScientists(1,1);
    showScientists(serve.listScientists());
    ui->updateScientistButton->setEnabled(false);
    ui->deleteScientistButton->setEnabled(false);
}

// When the add from file button is clicked you will be asked for
// the name of the file you want to load from
// if the file can not be opened then you will get an error message.
void MainWindow::on_addScientistsFromFileButton_clicked()
{
    LoadScientistsFromFileDialog loadScientists;
    loadScientists.setModal(true);
    loadScientists.exec();
    if (loadScientists.getLoad())
    {
        if (!serve.addScientistsFromFile(loadScientists.getFile()))
        {
            int reply = QMessageBox::question(this, "File Error", "Could not load from file\nTry again?",
                                              QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                on_addScientistsFromFileButton_clicked();
            }
        }
        else
        {
            showScientists(serve.listScientists());
        }
    }
}

// when the save to file button is pressed you will be asked for a file name
// it WILL overwrite everything in the file and saves the scientists to the file.
void MainWindow::on_saveScientistsToFileButton_clicked()
{
    saveScientistsToFileDialog sC;
    sC.setModal(true);
    sC.exec();

    if(sC.getSave())
    {
        string input = sC.getInput();
        serve.saveScientistsToFile(input);
    }
}

// When add button is pressed then a add window is executed
// in the add window you will add name,YearMade,Type and if it was built
// if you try to add a computer with invalid input you will be prompted to input again.
void MainWindow::on_addComputerButton_clicked()
{
    addComputerDialog addComputer;
    addComputer.setModal(true);
    addComputer.exec();

    if (addComputer.getAdd())
    {
        Computer c = addComputer.newComputer();

        if (valid.validComputerName(c.getComputerName()))
        {
            addNewComputer(c);

            showComputers(serve.listComputers());
        }
        else
        {
            int reply = QMessageBox::question(this, "Name not valid", "Invalid input for name!\nTry again?",
                                              QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::Yes)
            {
                on_addComputerButton_clicked();
            }
            else if (reply == QMessageBox::No)
            {
                ui->statusBar->showMessage("Add computer cancelled", 2500);
            }
        }
    }
}

void MainWindow::addNewComputer(const Computer &c)
{
    serve.addComputer(c);
}

// When the delete button is pressed you will be asked to confirm
// that you want to delete this computer.
void MainWindow::on_deleteComputerButton_clicked()
{
    int reply = QMessageBox::question(this, "Confirm delete", "Delete selected computer?",
                                      QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        int r = ui->computersTable->currentRow();
        string n =ui->computersTable->item(r, 0)->text().toStdString();
        serve.deleteComputer(n);

        showComputers(serve.listComputers());
    }
    else if (reply == QMessageBox::No)
    {
        ui->statusBar->showMessage("Delete computer cancelled", 2500);
    }

    ui->deleteComputerButton->setEnabled(false);
    ui->updateComputerButton->setEnabled(false);
}

// when the update button is clicked there will pop up another window
// and you can change information about the selected computer
// if input incorrect information you will be asked if you want to try again.
void MainWindow::on_updateComputerButton_clicked()
{
    int r = ui->computersTable->currentRow();
    string n = ui->computersTable->item(r,0)->text().toStdString();
    int yM = ui->computersTable->item(r,1)->text().toUInt();
    string t = ui->computersTable->item(r,2)->text().toStdString();
    string b = ui->computersTable->item(r,3)->text().toStdString();

    updateComputer updatecomputer;
    updatecomputer.setModal(true);
    updatecomputer.setName(n);
    updatecomputer.setYearMade(yM);
    updatecomputer.setType(t);
    updatecomputer.setBuilt(b);
    updatecomputer.exec();

    if(updatecomputer.getUpdate())
    {
        string name = updatecomputer.getName();
        string yearMade = updatecomputer.getYearMade();
        string type = updatecomputer.getType();
        string built = updatecomputer.getBuilt();

        if(valid.validComputerName(name))
        {
            if (yearMade != "0")
            {
                serve.updateComputer(1,name,n);
                serve.updateComputer(2,yearMade,name);
                serve.updateComputer(3,type,name);
                serve.updateComputer(4,built,name);
            }
            else
            {
                int reply = QMessageBox::question(this, "Year not valid", "Invalid input for year!\nTry again?",
                                                  QMessageBox::Yes | QMessageBox::No);

                if (reply == QMessageBox::Yes)
                {
                    on_addComputerButton_clicked();
                }
                else if (reply == QMessageBox::No)
                {
                    ui->statusBar->showMessage("Update computer cancelled", 2500);
                }
            }
        }
        else
        {
            int reply = QMessageBox::question(this, "Name not valid", "Invalid input for name!\nTry again?",
                                              QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::Yes)
            {
                on_addComputerButton_clicked();
            }
            else if (reply == QMessageBox::No)
            {
                ui->statusBar->showMessage("Update computer cancelled", 2500);
            }
        }
    }

    serve.sortComputers(1,1);
    showComputers(serve.listComputers());
    ui->updateComputerButton->setEnabled(false);
    ui->deleteComputerButton->setEnabled(false);
}

// when the save to file in the computer tab is pressed
// the computers will be saved to file, it WILL overwrite everything in the file.
void MainWindow::on_saveComputersToFileButton_clicked()
{
    saveComputersToFileDialog saveComp;
    saveComp.setModal(true);
    saveComp.exec();

    if(saveComp.getSave())
    {
        string input = saveComp.getInput();
        serve.saveComputersToFile(input);
    }
}

// when the add from file button is clicked for computers
// it will check if it can open the file if not you will get error message
// otherwise it will read from the file to the database, (you need special format)
void MainWindow::on_addComputersFromFileButton_clicked()
{
    LoadComputersFromFile comp;
    comp.setModal(true);
    comp.exec();
    if (comp.getLoad())
    {
        if (!serve.addComputersFromFile(comp.getFile()))
        {
            int reply = QMessageBox::question(this, "File Error", "Could not load from file\nTry again?",
                                              QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                on_addComputersFromFileButton_clicked();
            }
        }
        else
        {
            showComputers(serve.listComputers());
        }
    }
}

// This will bring up a new window where you can choose
// which computer and what scientist you want to associate
void MainWindow::on_addAssociationButton_clicked()
{
    addAssociationDialog addAssociation;
    addAssociation.setModal(true);
    addAssociation.setScientistList(serve.listScientists());
    addAssociation.setComputerList(serve.listComputers());
    addAssociation.exec();

    if (addAssociation.getAdd())
    {
        addNewAssociation(addAssociation.newAssociation()[0], addAssociation.newAssociation()[1]);

        showAssociations(serve.listAssociations());
    }
}

// This will associate the scientists and computers
// if you enter 'wierd' information you will be prompted to input again
void MainWindow::addNewAssociation(const string sN, const string cN)
{
    serve.sortScientists(1,1);
    Persons s = serve.listScientists()[serve.searchScientistByName(sN)[0]];
    serve.sortComputers(1,1);
    Computer c = serve.listComputers()[serve.searchComputerByName(cN)[0]];

    if (valid.validAssociation(s.getBirthYear(), s.getDeathYear(), c.getYearMade()))
    {
        Association a(s, c);
        serve.addAssociation(a);
    }
    else
    {
        int reply = QMessageBox::question(this, "Inconsistent years", "Scientist was not alive when computer was made\nTry again?",
                                          QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            on_addAssociationButton_clicked();
        }
        else
        {
            ui->statusBar->showMessage("Add association cancelled", 2500);
        }
    }
}

// When the delete button in associations is clicked then
// you will be asked if you are sure you want to delete the association
// if yes then it will be deleted else it will not
void MainWindow::on_deleteAssociationButton_clicked()
{
    int reply = QMessageBox::question(this, "Confirm delete", "Delete selected association?",
                                      QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        int r = ui->associationsTable->currentRow();
        string sN = ui->associationsTable->item(r, 0)->text().toStdString();
        string cN = ui->associationsTable->item(r, 1)->text().toStdString();
        serve.deleteAssociation(sN, cN);

        showAssociations(serve.listAssociations());
    }
    else if (reply == QMessageBox::No)
    {
        ui->statusBar->showMessage("Delete association cancelled", 2500);
    }
}

// This will bring up a new window which asks you to enter the
// filename and it will save it to that name
void MainWindow::on_saveAssocToFileButton_clicked()
{
    saveAssociationsToFileDialog saveAssociations;
    saveAssociations.setModal(true);
    saveAssociations.exec();

    if(saveAssociations.getSave())
    {
        string input = saveAssociations.getInput();
        serve.saveAssociationsToFile(input);
    }
}

// Shows the scientists in alphabetical order.
void MainWindow::showScientists(vector<Persons> S)
{
    ui->scientistTable->setSortingEnabled(false);
    ui->scientistTable->clear();
    ui->scientistTable->setRowCount(S.size());
    ui->scientistTable->setHorizontalHeaderItem(0, new QTableWidgetItem(QString::fromStdString("Name")));
    ui->scientistTable->setHorizontalHeaderItem(1, new QTableWidgetItem(QString::fromStdString("Gender")));
    ui->scientistTable->setHorizontalHeaderItem(2, new QTableWidgetItem(QString::fromStdString("Born")));
    ui->scientistTable->setHorizontalHeaderItem(3, new QTableWidgetItem(QString::fromStdString("Died")));
    ui->scientistTable->setHorizontalHeaderItem(4, new QTableWidgetItem(QString::fromStdString("Age")));

    for (unsigned int i = 0; i < S.size(); i++)
    {
        ui->scientistTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(S[i].getName())));
        ui->scientistTable->setItem(i, 1, new QTableWidgetItem(QString(QVariant(S[i].getGender()).toChar())));
        ui->scientistTable->setItem(i, 2, new QTableWidgetItem(QVariant(S[i].getBirthYear()).toString()));

        if (!S[i].getAlive())
        {
            ui->scientistTable->setItem(i, 3, new QTableWidgetItem(QVariant(S[i].getDeathYear()).toString()));
        }

        ui->scientistTable->setItem(i, 4, new QTableWidgetItem(QVariant(S[i].getAge()).toString()));
    }
    ui->scientistTable->setSortingEnabled(true);
}

// shows the computers in alphabetical order
void MainWindow::showComputers(vector<Computer> C)
{
    ui->computersTable->setSortingEnabled(false);
    ui->computersTable->clear();
    ui->computersTable->setRowCount(C.size());
    ui->computersTable->setHorizontalHeaderItem(0, new QTableWidgetItem(QString::fromStdString("Name")));
    ui->computersTable->setHorizontalHeaderItem(1, new QTableWidgetItem(QString::fromStdString("Year Made")));
    ui->computersTable->setHorizontalHeaderItem(2, new QTableWidgetItem(QString::fromStdString("Type")));
    ui->computersTable->setHorizontalHeaderItem(3, new QTableWidgetItem(QString::fromStdString("Built?")));

    for (unsigned int i = 0; i < C.size(); i++)
    {
        ui->computersTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(C[i].getComputerName())));
        ui->computersTable->setItem(i, 1, new QTableWidgetItem(QVariant(C[i].getYearMade()).toString()));
        ui->computersTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(C[i].getType())));

        if (C[i].getBuiltOrNot())
        {
            ui->computersTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString("Built")));
        }
        else
        {
            ui->computersTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString("Not Built")));
        }
    }
    ui->computersTable->setSortingEnabled(true);
}

// shows the associations in alphabetical order
void MainWindow::showAssociations(vector<Association> A)
{
    ui->associationsTable->setSortingEnabled(false);
    ui->associationsTable->clear();
    ui->associationsTable->setRowCount(A.size());
    ui->associationsTable->setHorizontalHeaderItem(0, new QTableWidgetItem(QString::fromStdString("Scientist")));
    ui->associationsTable->setHorizontalHeaderItem(1, new QTableWidgetItem(QString::fromStdString("Computer")));
    ui->associationsTable->setHorizontalHeaderItem(2, new QTableWidgetItem(QString::fromStdString("Year Made")));
    ui->associationsTable->setHorizontalHeaderItem(3, new QTableWidgetItem(QString::fromStdString("Built?")));
    ui->associationsTable->setHorizontalHeaderItem(4, new QTableWidgetItem(QString::fromStdString("Computer Type")));

    for (unsigned int i = 0; i < A.size(); i++)
    {
        ui->associationsTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(A[i].getScientistName())));
        ui->associationsTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(A[i].getComputerName())));
        ui->associationsTable->setItem(i, 2, new QTableWidgetItem(QVariant(A[i].getYearMade()).toString()));

        if (A[i].getBuiltOrNot())
        {
            ui->associationsTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString("Built")));
        }
        else
        {
            ui->associationsTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString("Not Built")));
        }

        ui->associationsTable->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(A[i].getComputerType())));
    }
    ui->associationsTable->setSortingEnabled(true);
}

// This is connected to the tab order, index 0 is scientists and so on.
// for search and delete and so on.
void MainWindow::on_mainOptions_currentChanged(int index)
{
    if (index == 0)
    {
        ui->searchScientistsByBox->setCurrentText("Name");
        ui->searchInputScientists->setPlaceholderText(QString::fromStdString("Enter name"));
        ui->lastYearInputScientist->hide();
        ui->deleteScientistButton->setEnabled(false);
        ui->updateScientistButton->setEnabled(false);
        showScientists(serve.listScientists());
    }
    else if (index == 1)
    {
        ui->searchComputersByBox->setCurrentText("Name");
        ui->searchInputComputers->setPlaceholderText(QString::fromStdString("Enter name"));
        ui->lastYearInputComputers->hide();
        ui->deleteComputerButton->setEnabled(false);
        ui->updateComputerButton->setEnabled(false);
        showComputers(serve.listComputers());
    }
    else if (index == 2)
    {
        ui->searchAssocByBox->setCurrentText("Scientist Name");
        ui->searchInputAssociations->setPlaceholderText(QString::fromStdString("Enter scientist name"));
        ui->lastYearInputAssoc->hide();
        ui->deleteAssociationButton->setEnabled(false);
        showAssociations(serve.listAssociations());
    }
}

void MainWindow::on_actionAdd_Scientist_triggered()
{
    on_addScientistButton_clicked();
}

void MainWindow::on_actionAdd_Computer_triggered()
{
    on_addComputerButton_clicked();
}

void MainWindow::on_actionAdd_Association_triggered()
{
    on_addAssociationButton_clicked();
}

void MainWindow::on_actionExit_Program_triggered()
{
    close();
}

// This is so you can not update or delete without selecting someone
void MainWindow::on_scientistTable_clicked()
{
    ui->updateScientistButton->setEnabled(true);
    ui->deleteScientistButton->setEnabled(true);
}

// This is so you can not update or delete without selecting a computer
void MainWindow::on_computersTable_clicked()
{
    ui->updateComputerButton->setEnabled(true);
    ui->deleteComputerButton->setEnabled(true);
}

// This is so you can not delete without selecting someone
void MainWindow::on_associationsTable_clicked()
{
    ui->deleteAssociationButton->setEnabled(true);
}

// searches for name/gender/year/yearRange
// it does not matter if we search for upperCase letters or not
// and if nothing is searched then it shows the scientists
void MainWindow::searchScientist()
{
    serve.sortScientists(1,1);
    vector<Persons> people = serve.listScientists();
    vector<Persons> P;
    vector<int> v;

    if (ui->searchScientistsByBox->currentText().toStdString() == "Name")
    {
        string n = ui->searchInputScientists->text().toStdString();
        v = serve.searchScientistByName(n);
    }
    else if (ui->searchScientistsByBox->currentText().toStdString() == "Gender")
    {
        char g = ui->searchInputScientists->text().toStdString()[0];
        if(!isupper(g))
        {
            g = toupper(g);
        }
        v = serve.searchScientistByGender(g);
    }
    else if (ui->searchScientistsByBox->currentText().toStdString() == "Birth Year")
    {
        int y = ui->searchInputScientists->text().toUInt();
        v = serve.searchScientistByBirthYear(y);
    }
    else if (ui->searchScientistsByBox->currentText().toStdString() == "Birth Year Range")
    {
        int f = ui->searchInputScientists->text().toUInt();
        int l = ui->lastYearInputScientist->text().toUInt();
        v = serve.searchScientistByYearRange(f, l);
    }

    for (unsigned int i  = 0; i < v.size(); i++)
    {
        P.push_back(people[v[i]]);
    }

    if (P.size() == 0)
    {
        ui->noScientistFoundLabel->show();
        QTimer::singleShot(3000, ui->noScientistFoundLabel, &QLabel::hide);
        showScientists(serve.listScientists());
    }
    else
    {
        showScientists(P);
    }
}

// searches for name/YearMade/YearRange/Type
// upperCase letter do not matter
void MainWindow::searchComputer()
{
    serve.sortComputers(1,1);
    vector<Computer> computers = serve.listComputers();
    vector<Computer> C;
    vector<int> v;

    if (ui->searchComputersByBox->currentText().toStdString() == "Name")
    {
        string n = ui->searchInputComputers->text().toStdString();
        v = serve.searchComputerByName(n);
    }
    else if (ui->searchComputersByBox->currentText().toStdString() == "Year Made")
    {
        int y = ui->searchInputComputers->text().toUInt();
        v = serve.searchComputerByYearMade(y);
    }
    else if (ui->searchComputersByBox->currentText().toStdString() == "Year Range")
    {
        int f = ui->searchInputComputers->text().toUInt();
        int l = ui->lastYearInputComputers->text().toUInt();
        v = serve.searchComputerByYearRange(f, l);
    }
    else if (ui->searchComputersByBox->currentText().toStdString() == "Type")
    {
        string t = ui->searchInputComputers->text().toStdString();
        v = serve.searchComputerByType(t);
    }

    for (unsigned int i = 0; i < v.size(); i++)
    {
        C.push_back(computers[v[i]]);
    }

    if(C.size() == 0)
    {
        ui->noComputerFoundLabel->show();
        QTimer::singleShot(3000, ui->noComputerFoundLabel, &QLabel::hide);
        showComputers(serve.listComputers());
    }
    else
    {
        showComputers(C);
    }

}

// searches for scientist name/computer name/year made/ year range
// and computer type
void MainWindow::searchAssociation()
{
    serve.sortAssociations(0,1);
    vector<Association> assocs = serve.listAssociations();
    vector<Association> A;
    vector<int> v;

    if (ui->searchAssocByBox->currentText().toStdString() == "Scientist Name")
    {
        string sN = ui->searchInputAssociations->text().toStdString();
        v = serve.searchAssocBySciName(sN);
    }
    else if (ui->searchAssocByBox->currentText().toStdString() == "Computer Name")
    {
        string cN = ui->searchInputAssociations->text().toStdString();
        v = serve.searchAssocByCompName(cN);
    }
    else if (ui->searchAssocByBox->currentText().toStdString() == "Year Made")
    {
        int y = ui->searchInputAssociations->text().toUInt();
        v = serve.searchAssocByYear(y);
    }
    else if (ui->searchAssocByBox->currentText().toStdString() == "Year Range")
    {
        int f = ui->searchInputAssociations->text().toUInt();
        int l = ui->lastYearInputAssoc->text().toUInt();
        v = serve.searchAssocByYearRange(f, l);
    }
    else if (ui->searchAssocByBox->currentText().toStdString() == "Computer Type")
    {
        string t = ui->searchInputAssociations->text().toStdString();
        v = serve.searchAssocByCompType(t);
    }

    for (unsigned int i = 0; i < v.size(); i++)
    {
        A.push_back(assocs[v[i]]);
    }

    if(A.size() == 0)
    {
        ui->noAssociationFoundLabel->show();
        QTimer::singleShot(3000, ui->noAssociationFoundLabel, &QLabel::hide);
        showAssociations(serve.listAssociations());
    }
    else
    {
        showAssociations(A);
    }
}

// Shows the Enter name/ gender/ birthYear/ BirthYearRange in light gray in the search boxes
// and you can write over them without have-ing to erase them
void MainWindow::on_searchScientistsByBox_currentTextChanged(const QString &arg1)
{
    if (arg1.toStdString() == "Name")
    {
        ui->lastYearInputScientist->hide();
        ui->searchInputScientists->setPlaceholderText(QString::fromStdString("Enter name"));
        ui->searchInputScientists->setGeometry(11, 40, 380, 22);
    }
    else if (arg1.toStdString() == "Gender")
    {
        ui->lastYearInputScientist->hide();
        ui->searchInputScientists->setPlaceholderText(QString::fromStdString("Enter gender"));
        ui->searchInputScientists->setGeometry(11, 40, 100, 22);
    }
    else if (arg1.toStdString() == "Birth Year")
    {
        ui->lastYearInputScientist->hide();
        ui->searchInputScientists->setPlaceholderText(QString::fromStdString("Enter year"));
        ui->searchInputScientists->setGeometry(11, 40, 100, 22);
    }
    else if (arg1.toStdString() == "Birth Year Range")
    {
        ui->lastYearInputScientist->show();
        ui->searchInputScientists->setPlaceholderText(QString::fromStdString("Enter first year"));
        ui->lastYearInputScientist->setPlaceholderText(QString::fromStdString("Enter last year"));
        ui->searchInputScientists->setGeometry(11, 40, 100, 22);
    }
}

// Shows the Enter name/ year/ birthYearRange/Type in light gray in the search boxes
// and you can write over them without have-ing to erase them
void MainWindow::on_searchComputersByBox_currentTextChanged(const QString &arg1)
{
    if (arg1.toStdString() == "Name")
    {
        ui->lastYearInputComputers->hide();
        ui->searchInputComputers->setPlaceholderText(QString::fromStdString("Enter name"));
        ui->searchInputComputers->setGeometry(11, 40, 380, 22);
    }
    else if (arg1.toStdString() == "Year Made")
    {
        ui->lastYearInputComputers->hide();
        ui->searchInputComputers->setPlaceholderText(QString::fromStdString("Enter year"));
        ui->searchInputComputers->setGeometry(11, 40, 100, 22);
    }
    else if (arg1.toStdString() == "Year Range")
    {
        ui->lastYearInputComputers->show();
        ui->searchInputComputers->setPlaceholderText(QString::fromStdString("Enter first year"));
        ui->lastYearInputComputers->setText(QString::fromStdString("Enter last year"));
        ui->searchInputComputers->setGeometry(11, 40, 100, 22);
    }
    else if (arg1.toStdString() == "Type")
    {
        ui->lastYearInputComputers->hide();
        ui->searchInputComputers->setPlaceholderText(QString::fromStdString("Enter type"));
        ui->searchInputComputers->setGeometry(11, 40, 380, 22);
    }
}

// Shows the Enter name/ year/ YearRange/ ComputerType
// Type in light gray in the search boxes
// and you can write over them without have-ing to erase them
void MainWindow::on_searchAssocByBox_currentTextChanged(const QString &arg1)
{
    if (arg1.toStdString() == "Scientist Name")
    {
        ui->lastYearInputAssoc->hide();
        ui->searchInputAssociations->setPlaceholderText(QString::fromStdString("Enter scientist name"));
        ui->searchInputAssociations->setGeometry(11, 40, 380, 22);
    }
    else if (arg1.toStdString() == "Computer Name")
    {
        ui->lastYearInputAssoc->hide();
        ui->searchInputAssociations->setPlaceholderText(QString::fromStdString("Enter computer name"));
        ui->searchInputAssociations->setGeometry(11, 40, 380, 22);
    }
    else if (arg1.toStdString() == "Year Made")
    {
        ui->lastYearInputAssoc->hide();
        ui->searchInputAssociations->setPlaceholderText(QString::fromStdString("Enter year"));
        ui->searchInputAssociations->setGeometry(11, 40, 100, 22);
    }
    else if (arg1.toStdString() == "Year Range")
    {
        ui->lastYearInputAssoc->show();
        ui->searchInputAssociations->setPlaceholderText(QString::fromStdString("Enter first year"));
        ui->lastYearInputAssoc->setPlaceholderText(QString::fromStdString("Enter last year"));
        ui->searchInputAssociations->setGeometry(11, 40, 100, 22);
    }
    else if (arg1.toStdString() == "Computer Type")
    {
        ui->lastYearInputAssoc->hide();
        ui->searchInputAssociations->setPlaceholderText(QString::fromStdString("Enter type"));
        ui->searchInputAssociations->setGeometry(11, 40, 380, 22);
    }
}

void MainWindow::on_searchInputScientists_returnPressed()
{
    searchScientist();
    ui->searchInputScientists->clear();
}

void MainWindow::on_searchInputComputers_returnPressed()
{
    searchComputer();
    ui->searchInputComputers->clear();
}

void MainWindow::on_searchInputAssociations_returnPressed()
{
    searchAssociation();
    ui->searchInputAssociations->clear();
}

void MainWindow::on_lastYearInputScientist_returnPressed()
{
    searchScientist();
    ui->searchInputScientists->clear();
    ui->lastYearInputScientist->clear();
}

void MainWindow::on_lastYearInputComputers_returnPressed()
{
    searchComputer();
    ui->searchInputComputers->clear();
    ui->lastYearInputComputers->clear();
}

void MainWindow::on_lastYearInputAssoc_returnPressed()
{
    searchAssociation();
    ui->searchInputAssociations->clear();
    ui->lastYearInputAssoc->clear();
}

// when a scientist row is double clicked then it will
// show more information about them with a picture if it exists
void MainWindow::on_scientistTable_doubleClicked()
{
    int r = ui->scientistTable->currentRow();
    QString n = ui->scientistTable->item(r, 0)->text();
    QString bY = ui->scientistTable->item(r, 2)->text();
    QString dY = ui->scientistTable->item(r, 3)->text();
    QString a = ui->scientistTable->item(r, 4)->text();
    QPixmap qp = serve.showPicOfScientists(n.toStdString());
    ScientistsInformationWindowDialog sID;
    sID.setModal(true);
    sID.setImage(qp);
    sID.setName(n);
    sID.setBirthYear(bY);
    sID.setDeathYear(dY);
    sID.setAge(a);
    sID.ShowPicture();
    sID.exec();

}
