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

//Takes in name of selected computer and fills
//the name window in the dialog.
void updateComputer::setName(const std::string s)
{
    ui->updateComputerNameLineEdit->setText(QString::fromStdString(s));
}

//Takes in year made of selected computer and fills
//the approriate window in the dialog.
void updateComputer::setYearMade(const int yM)
{
    QDate m(yM, 1, 1);
    ui->updateYearMadeEdit->setDate(m);
}

//Takes in the type of selected computer and fills
//the approriate box in the dialog.
void updateComputer::setType(const std::string t)
{
    ui->updateComputerTypeComboBox->setCurrentText(QString::fromStdString(t));
}

//Takes in built status of selected computer and fills
//the approriate box in the dialog.
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

//Updates the name in the dialog
std::string updateComputer::getName()
{
    std::string name = ui->updateComputerNameLineEdit->text().toStdString();

    return name;
}

//Updates year made in the dialog
std::string updateComputer::getYearMade()
{
    int yM = ui->updateYearMadeEdit->date().year();
    std::string yearMade = std::to_string(yM);

    return yearMade;
}

//Updates the type in the dialog
std::string updateComputer::getType()
{
    std::string type = ui->updateComputerTypeComboBox->currentText().toStdString();

    return type;
}

//Updates built status in the dialog
std::string updateComputer::getBuilt()
{
    std::string built = ui->updateComputerBuiltComboBox->currentText().toStdString();

    return built;
}

bool updateComputer::getUpdate()
{
    return update;
}

//Updates the computer and closes the dialog
void updateComputer::on_updateComputerButton_clicked()
{
    update = true;
    this->close();
}

//Update cancelled and closes the dialog
void updateComputer::on_cancelAddComputerButton_clicked()
{
    update = false;
    this->close();
}
