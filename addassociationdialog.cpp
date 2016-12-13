#include "addassociationdialog.h"
#include "ui_addassociationdialog.h"

addAssociationDialog::addAssociationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addAssociationDialog)
{
    ui->setupUi(this);
}

addAssociationDialog::~addAssociationDialog()
{
    delete ui;
}

void addAssociationDialog::on_cancelAddAssociationButton_clicked()
{
    add = false;
    this->close();
}

void addAssociationDialog::on_addAssociationButton_clicked()
{
    add = true;
    this->close();
}

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
