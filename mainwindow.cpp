#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addscientistdialog.h"
#include "addcomputerdialog.h"
#include "addassociationdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    addScientistDialog addScientistButton;
    addScientistButton.setModal(true);
    addScientistButton.exec();
}

void MainWindow::on_deleteScientistButton_clicked()
{

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
    addComputerDialog addComputerButton;
    addComputerButton.setModal(true);
    addComputerButton.exec();
}

void MainWindow::on_deleteComputerButton_clicked()
{

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
    addAssociationDialog addAssociationButton;
    addAssociationButton.setModal(true);
    addAssociationButton.exec();
}

void MainWindow::on_deleteAssociationButton_clicked()
{

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
