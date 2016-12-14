#include "savecomputerstofiledialog.h"
#include "ui_savecomputerstofiledialog.h"

saveComputersToFileDialog::saveComputersToFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::saveComputersToFileDialog)
{
    ui->setupUi(this);
}

saveComputersToFileDialog::~saveComputersToFileDialog()
{
    delete ui;
}
