#include "addcomputerdialog.h"
#include "ui_addcomputerdialog.h"

addComputerDialog::addComputerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addComputerDialog)
{
    ui->setupUi(this);
    add = false;
}

addComputerDialog::~addComputerDialog()
{
    delete ui;
}

//Closes the window when the cancel button is pressed
void addComputerDialog::on_cancelAddComputerButton_clicked()
{
    this->close();
}

//Add becomes true, so a person is added.
void addComputerDialog::on_addComputerButton_clicked()
{
    add = true;
    this->close();
}

//Takes in Computer name, yearMade, type and if it was built
//and returns it to the vector.
Computer addComputerDialog::newComputer()
{
    string n = ui->computerNameLineEdit->text().toStdString();
    int yM = ui->yearMadeEdit->date().year();
    string t = ui->computerTypeComboBox->currentText().toStdString();
    bool b = ui->computerBuiltComboBox->currentText().toStdString() == "Built";
    Computer c(n, yM, t, b);

    return c;
}

bool addComputerDialog::getAdd()
{
    return add;
}
