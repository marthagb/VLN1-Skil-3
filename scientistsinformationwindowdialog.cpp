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

void ScientistsInformationWindowDialog::setImage(QPixmap qp)
{
    image = qp;
}

void ScientistsInformationWindowDialog::ShowPicture()
{
    ui->loadImageLabel->text().clear();
    ui->loadImageLabel->setPixmap(image);
    ui->loadImageLabel->setScaledContents(true);
    ui->loadImageLabel->show();
}
