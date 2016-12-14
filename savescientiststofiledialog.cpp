#include "savescientiststofiledialog.h"
#include "ui_savescientiststofiledialog.h"

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
    save = true;
    this->close();
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
