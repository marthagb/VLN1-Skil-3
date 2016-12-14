#include "savescientiststofiledialog.h"
#include "ui_savescientiststofiledialog.h"
#include "servicelayer.h"

saveScientistsToFileDialog::saveScientistsToFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::saveScientistsToFileDialog)
{
    ui->setupUi(this);
}


saveScientistsToFileDialog::~saveScientistsToFileDialog()
{
    delete ui;
}

void saveScientistsToFileDialog::on_saveScientistsToFile_clicked()
{
    ServiceLayer serve;
    if(!serve.saveScientistsToFile(ui->InputForTextFileName->text().toStdString()))
    {
        ui->ErrorLabelSaveScientists->setText("<span style ='color: #ff0000 '> Could not load from file </span>");
    }
    else
    {
        save = true;
        this->close();
    }
}

std::string saveScientistsToFileDialog::getInput()
{
    return ui->InputForTextFileName->text().toStdString();
}

bool saveScientistsToFileDialog::getSave()
{
    return save;
}

void saveScientistsToFileDialog::on_cancelSaveScientistsToFile_clicked()
{
    save = false;
    this->close();
}


