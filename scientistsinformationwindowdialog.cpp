#include "scientistsinformationwindowdialog.h"
#include "ui_scientistsinformationwindowdialog.h"

ScientistsInformationWindowDialog::ScientistsInformationWindowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScientistsInformationWindowDialog)
{
    ui->setupUi(this);
}

ScientistsInformationWindowDialog::~ScientistsInformationWindowDialog()
{
    delete ui;
}


