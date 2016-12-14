#include "updatescientist.h"
#include "ui_updatescientist.h"

updatescientist::updatescientist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::updatescientist)
{
    ui->setupUi(this);
}

updatescientist::~updatescientist()
{
    delete ui;
}

void updatescientist::setName(const std::string s)
{
    ui->updateNameInput->setText(QString::fromStdString(s));
}

void updatescientist::setGender(const std::string g)
{
    if(g == "F")
    {
        ui->updateGenderBox->setCurrentText(QString::fromStdString("Female"));

    }
    else if(g == "M")
    {
        ui->updateGenderBox->setCurrentText(QString::fromStdString("Male"));
    }
}

void updatescientist::setBirthYear(const int bY)
{
    QDate b(bY, 1, 1);
    ui->updateBirthYear->setDate(b);
}

void updatescientist::setDeathYear(const int dY)
{
    QDate d(dY, 1, 1);
    ui->updateDeathYear->setDate(d);
}
