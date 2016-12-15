#include "loadcomputersfromfile.h"
#include "ui_loadcomputersfromfile.h"
#include "servicelayer.h"

LoadComputersFromFile::LoadComputersFromFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadComputersFromFile)
{
    ui->setupUi(this);
}

LoadComputersFromFile::~LoadComputersFromFile()
{
    delete ui;
}

void LoadComputersFromFile::on_ButtonLoad_clicked()
{
    ServiceLayer serve;

    if (!serve.addScientistsFromFile(ui->InputForTextFileName->text().toStdString()))
    {
        ui->LabelErrorMessage->setText("<span style ='color: #ff0000 '> Could not load from file </span>");
    }
    else
    {
        this->close();
    }
}

void LoadComputersFromFile::on_ButtonCancel_clicked()
{
    this->close();
}
