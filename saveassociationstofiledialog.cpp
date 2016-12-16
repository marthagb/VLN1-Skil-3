#include "saveassociationstofiledialog.h"
#include "ui_saveassociationstofiledialog.h"
#include "servicelayer.h"

saveAssociationsToFileDialog::saveAssociationsToFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::saveAssociationsToFileDialog)
{
    ui->setupUi(this);
}

saveAssociationsToFileDialog::~saveAssociationsToFileDialog()
{
    delete ui;
}

//Saves the selected data to file and closes the dialog
void saveAssociationsToFileDialog::on_SaveAssociationsToFile_clicked()
{
    ServiceLayer serve;

    if(!serve.saveScientistsToFile(ui->InputForTextFileNameAssociations->text().toStdString()))
    {
        ui->labelassociations->setText("<span style ='color: #ff0000 '> Could not load from file </span>");
    }
    else
    {
        save = true;
        this->close();
    }
}

//Save to file cancelled and dialog closed
void saveAssociationsToFileDialog::on_cancelSaveAssociationsToFile_clicked()
{
    save = false;
    this->close();
}

std::string saveAssociationsToFileDialog::getInput()
{
    return ui->InputForTextFileNameAssociations->text().toStdString();
}

bool saveAssociationsToFileDialog::getSave()
{
    return save;
}

