#include "savecomputerstofiledialog.h"
#include "ui_savecomputerstofiledialog.h"
#include "servicelayer.h"


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

//Saves selected data to file and closes the dialog
void saveComputersToFileDialog::on_SaveComputersToFile_clicked()
{
    ServiceLayer serve;

    if(!serve.saveComputersToFile(ui->InputForTextFileNameComputer->text().toStdString()))
    {
        ui->ErrorLabelSaveComputer->setText("<span style ='color: #ff0000 '> Could not save to file </span>");
    }
    else
    {
        save = true;
        this->close();
    }
}

//Save to file cancelled and dialog closed
void saveComputersToFileDialog::on_cancelSaveComputersToFile_clicked()
{
    save = false;
    this->close();
}

std::string saveComputersToFileDialog::getInput()
{
    return ui->InputForTextFileNameComputer->text().toStdString();
}
