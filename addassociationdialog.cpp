#include "addassociationdialog.h"
#include "ui_addassociationdialog.h"

addAssociationDialog::addAssociationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addAssociationDialog)
{
    ui->setupUi(this);
    add = false;
}

addAssociationDialog::~addAssociationDialog()
{
    delete ui;
}

//Closes the window when the cancel button is pressed
void addAssociationDialog::on_cancelAddAssociationButton_clicked()
{
    this->close();
}

// Add is true, so the association goes through
void addAssociationDialog::on_addAssociationButton_clicked()
{
    add = true;
    this->close();
}

//takes in two strings (one for scientists and one for computers)
//and adds them together
vector<string> addAssociationDialog::newAssociation()
{
    string sN = ui->scientistList->currentItem()->text().toStdString();
    string cN = ui->computersList->currentItem()->text().toStdString();
    vector<string> a;
    a.push_back(sN);
    a.push_back(cN);

    return a;
}

bool addAssociationDialog::getAdd()
{
    return add;
}

//Lists the scientists
void addAssociationDialog::setScientistList(vector<Persons> S)
{
    for (unsigned int i = 0; i < S.size(); i++)
    {
        ui->scientistList->addItem(new QListWidgetItem(QString::fromStdString(S[i].getName())));
    }
}

//Lists the computers
void addAssociationDialog::setComputerList(vector<Computer> C)
{
    for (unsigned int i = 0; i < C.size(); i++)
    {
        ui->computersList->addItem(new QListWidgetItem(QString::fromStdString(C[i].getComputerName())));
    }
}

//Checks if the size of the vector is 0
// if it is notzero then you can add association
void addAssociationDialog::on_scientistList_clicked()
{
    if (ui->computersList->selectedItems().size() != 0)
    {
        ui->addAssociationButton->setEnabled(true);
    }
}

//Checks if the size of the vector is 0
// if it is notzero then you can add association
void addAssociationDialog::on_computersList_clicked()
{
    if (ui->scientistList->selectedItems().size() != 0)
    {
        ui->addAssociationButton->setEnabled(true);
    }
}
