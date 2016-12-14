#include "savecomputerstofiledialog.h"
#include "ui_savecomputerstofiledialog.h"



saveComputersToFileDialog::saveComputersToFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::saveComputersToFileDialog)
{
    ui->setupUi(this);
}

bool saveComputersToFileDialog::getSave()
{
    return save;
}

saveComputersToFileDialog::~saveComputersToFileDialog()
{
    delete ui;
}

void saveComputersToFileDialog::on_SaveComputersToFile_clicked()
{
    save = true;
    this->close();
}

void saveComputersToFileDialog::on_cancelSaveComputersToFile_clicked()
{
    save = false;
    this->close();
}
std::string saveComputersToFileDialog::getInput()
{
    return ui->InputForTextFileNameComputer->text().toStdString();
}
