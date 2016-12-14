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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainOptions->setCurrentIndex(0);
    showScientists(serve.listScientists());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}

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

            }
        }
    }
}

void MainWindow::addNewScientist(const Persons &p)
{
    serve.addScientist(p);
}

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

    }
}

void MainWindow::on_updateScientistButton_clicked()
{
    int r = ui->scientistTable->currentRow();
    string n = ui->scientistTable->item(r,0)->text().toStdString();
    string g = ui->scientistTable->item(r,1)->text().toStdString();
    int bY = ui->scientistTable->item(r,2)->text().toUInt();

    updatescientist updateScientist;
    updateScientist.setModal(true);
    updateScientist.setName(n);
    updateScientist.setGender(g);
    updateScientist.setBirthYear(bY);

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
        string name = updateScientist.getName();            //name update--
        if(valid.validName(name))
        {
        serve.updateScientist(1, name, n);

        string gender = updateScientist.getGender();        //gender update
        serve.updateScientist(2,gender,n);
        string birthYear = updateScientist.getBirthYear();  //birthYear update
        serve.updateScientist(3,birthYear,n);
        if(!updateScientist.getCheckBox())
        {
            string deathYear = updateScientist.getDeathYear();  //deathYear update
            serve.updateScientist(4,deathYear,n);
        }
        else
        {
            string dY = " ";
            serve.updateScientist(4,dY,n);
        }

    serve.sortScientists(1,1);
    showScientists(serve.listScientists());
    ui->updateScientistButton->setEnabled(false);
}
        }
}

void MainWindow::on_addScientistsFromFileButton_clicked()
{
    LoadScientistsFromFileDialog loadScientists;
    loadScientists.setModal(true);
    loadScientists.exec();

    if(loadScientists.getLoad())
    {
        string input = loadScientists.getInput();
        if (!(serve.addScientistsFromFile(input)))
        {
            //errormessage
        }
    }
    showScientists(serve.listScientists());
}

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

void MainWindow::on_ascendingRadioButton_clicked()
{

}

void MainWindow::on_descendingRadioButton_clicked()
{

}

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

            }
        }
    }
}

void MainWindow::addNewComputer(const Computer &c)
{
    serve.addComputer(c);
}

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

    }
}

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
        serve.updateComputer(1,name,n);
        string yearMade = updatecomputer.getYearMade();
        serve.updateComputer(2,yearMade,n);
        string type = updatecomputer.getType();
        serve.updateComputer(3,type,n);
        string built = updatecomputer.getBuilt();
        serve.updateComputer(4,built,n);
    }

    serve.sortComputers(1,1);
    showComputers(serve.listComputers());
    ui->updateComputerButton->setEnabled(false);
}

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

void MainWindow::on_addComputersFromFileButton_clicked()
{
    LoadComputersFromFile comp;
    comp.setModal(true);
    comp.exec();

    if(comp.getLoad())
    {
        string input = comp.getInput();
        if (!(serve.addComputersFromFile(input)))
        {
            //Errormessage
        }
    }
    showComputers(serve.listComputers());
}

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

void MainWindow::addNewAssociation(const string sN, const string cN)
{
    serve.sortScientists(1,1);
    Persons s = serve.listScientists()[serve.searchScientistByName(sN)[0]];
    serve.sortComputers(1,1);
    Computer c = serve.listComputers()[serve.searchComputerByName(cN)[0]];
    Association a(s, c);
    serve.addAssociation(a);
}

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

    }
}

void MainWindow::on_updateAssociationButton_clicked()
{

}

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

void MainWindow::showScientists(vector<Persons> S)
{
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
}

void MainWindow::showComputers(vector<Computer> C)
{
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
}

void MainWindow::showAssociations(vector<Association> A)
{
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
}

void MainWindow::on_mainOptions_currentChanged(int index)
{
    if (index == 0)
    {
        showScientists(serve.listScientists());
    }
    else if (index == 1)
    {
        showComputers(serve.listComputers());
    }
    else if (index == 2)
    {
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

void MainWindow::on_scientistTable_clicked()
{
    ui->updateScientistButton->setEnabled(true);
    ui->deleteScientistButton->setEnabled(true);
}

void MainWindow::on_computersTable_clicked()
{
    ui->updateComputerButton->setEnabled(true);
    ui->deleteComputerButton->setEnabled(true);
}

void MainWindow::on_associationsTable_clicked()
{
    ui->updateAssociationButton->setEnabled(true);
    ui->deleteAssociationButton->setEnabled(true);
}
