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
