#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addscientistdialog.h"
#include "addcomputerdialog.h"
#include "addassociationdialog.h"
#include <QMessageBox>

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
        addNewScientist(addScientist.newScientist());
        showScientists(serve.listScientists());
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

}

void MainWindow::on_addScientistsFromFileButton_clicked()
{

}

void MainWindow::on_saveScientistsToFileButton_clicked()
{

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
        addNewComputer(addComputer.newComputer());
        showComputers(serve.listComputers());
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

}

void MainWindow::on_saveComputersToFileButton_clicked()
{

}

void MainWindow::on_addComputersFromFileButton_clicked()
{

}

void MainWindow::on_addAssociationButton_clicked()
{
    addAssociationDialog addAssociation;
    addAssociation.setModal(true);
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
