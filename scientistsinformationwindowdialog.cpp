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

void ScientistsInformationWindowDialog::setImage(QByteArray arr)
{
    image = arr;
}

void ScientistsInformationWindowDialog::ShowPicture()
{
    QPixmap outPixmap;
    outPixmap.loadFromData(image);
    ui->loadImageLabel->setPixmap(outPixmap);
    ui->loadImageLabel->show();
}
