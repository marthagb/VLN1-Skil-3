#include "addcomputerdialog.h"
#include "ui_addcomputerdialog.h"

addComputerDialog::addComputerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addComputerDialog)
{
    ui->setupUi(this);
}

addComputerDialog::~addComputerDialog()
{
    delete ui;
}

void addComputerDialog::on_cancelAddComputerButton_clicked()
{
    add = false;
    this->close();
}

void addComputerDialog::on_addComputerButton_clicked()
{
    add = true;
    this->close();
}

Computer addComputerDialog::newComputer()
{
    string n = ui->computerNameLineEdit->text().toStdString();
    int yM = ui->yearMadeEdit->date().year();
    string t = ui->computerTypeLineEdit->text().toStdString();
    bool b = ui->computerBuiltComboBox->currentText().toStdString() == "Built";
    Computer c(n, yM, t, b);
    return c;
}

bool addComputerDialog::getAdd()
{
    return add;
}
