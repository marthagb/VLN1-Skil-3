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
    this->close();
}

void addAssociationDialog::on_addAssociationButton_clicked()
{

}
