#include "updatecomputer.h"
#include "ui_updatecomputer.h"

updateComputer::updateComputer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::updateComputer)
{
    ui->setupUi(this);
}

updateComputer::~updateComputer()
{
    delete ui;
}

void updateComputer::setName(const std::string s)
{
    ui->updateComputerNameLineEdit->setText(QString::fromStdString(s));
}

void updateComputer::setYearMade(const int yM)
{
    QDate m(yM, 1, 1);
    ui->updateYearMadeEdit->setDate(m);
}

void updateComputer::setType(const std::string t)
{
    ui->updateComputerTypeComboBox->setCurrentText(QString::fromStdString(t));
}

void updateComputer::setBuilt(const std::string b)
{
    if(b == "Built")
    {
        ui->updateComputerBuiltComboBox->setCurrentText(QString::fromStdString("Built"));
    }
    else
    {
        ui->updateComputerBuiltComboBox->setCurrentText(QString::fromStdString("Not built"));
    }
}

std::string updateComputer::getName()
{
    std::string name = ui->updateComputerNameLineEdit->text().toStdString();
    return name;
}

std::string updateComputer::getYearMade()
{
    int yM = ui->updateYearMadeEdit->date().year();
    std::string yearMade = std::to_string(yM);
    return yearMade;
}

std::string updateComputer::getType()
{
    std::string type = ui->updateComputerTypeComboBox->currentText().toStdString();
    return type;
}

std::string updateComputer::getBuilt()
{
    std::string built = ui->updateComputerBuiltComboBox->currentText().toStdString();
    return built;
}

bool updateComputer::getUpdate()
{
    return update;
}

void updateComputer::on_updateComputerButton_clicked()
{
    update = true;
    this->close();
}

void updateComputer::on_cancelAddComputerButton_clicked()
{
    update = false;
    this->close();
}
