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

void ScientistsInformationWindowDialog::setName(QString n)
{
    ui->ScientistsNameLabel->setText(n);
}

void ScientistsInformationWindowDialog::setBirthYear(QString bY)
{
    ui->ScientistsYearBornLabel->setText(QString::fromStdString("Born: ")+bY);
}

void ScientistsInformationWindowDialog::setDeathYear(QString dY)
{
    ui->ScientistsYearOfDeathLabel->setText(QString::fromStdString("Died: ")+dY);
}

void ScientistsInformationWindowDialog::setAge(QString a)
{
    ui->ScientistAgeLabel->setText(QString::fromStdString("Age: ")+a);
}

void ScientistsInformationWindowDialog::setFunFact(QString fF)
{
    ui->ScientistsFunFactLabel->setText(QString::fromStdString("Fun fact: ")+fF);
}

//displays the picture and scales it
void ScientistsInformationWindowDialog::ShowPicture()
{
    ui->loadImageLabel->text().clear();
    ui->loadImageLabel->setPixmap(image);
    ui->loadImageLabel->setScaledContents(true);
    ui->loadImageLabel->show();
}
