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

//Loads the file and closes the dialog
void LoadComputersFromFile::on_ButtonLoad_clicked()
{
    file = ui->InputForTextFileName->text().toStdString();
    load = true;
    this->close();
}

//Load cancelled and closes the dialog
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

//If enter is pressed the file will load
void LoadComputersFromFile::on_InputForTextFileName_returnPressed()
{
    on_ButtonLoad_clicked();
}
