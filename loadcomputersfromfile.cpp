#include "loadcomputersfromfile.h"
#include "ui_loadcomputersfromfile.h"
#include "servicelayer.h"

LoadComputersFromFile::LoadComputersFromFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadComputersFromFile)
{
    ui->setupUi(this);
    load = false;
}

LoadComputersFromFile::~LoadComputersFromFile()
{
    delete ui;
}

void LoadComputersFromFile::on_ButtonLoad_clicked()
{
    file = ui->InputForTextFileName->text().toStdString();
    load = true;
    this->close();
}

void LoadComputersFromFile::on_ButtonCancel_clicked()
{
    this->close();
}

bool LoadComputersFromFile::getLoad()
{
    return load;
}

string LoadComputersFromFile::getFile()
{
    return file;
}
