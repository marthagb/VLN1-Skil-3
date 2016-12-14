#include "loadcomputersfromfile.h"
#include "ui_loadcomputersfromfile.h"

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
    load = true;
    this->close();
}

void LoadComputersFromFile::on_ButtonCancel_clicked()
{
    load = false;
    this->close();
}

std::string LoadComputersFromFile::getInput()
{
    return ui->InputForTextFileName->text().toStdString();
}

bool LoadComputersFromFile::getLoad()
{
    return load;
}
