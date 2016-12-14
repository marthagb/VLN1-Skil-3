#include "saveassociationstofiledialog.h"
#include "ui_saveassociationstofiledialog.h"

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

void saveAssociationsToFileDialog::on_SaveAssociationsToFile_clicked()
{
    save = true;
    this->close();
}

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

