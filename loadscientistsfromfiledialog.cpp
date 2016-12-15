#include "loadscientistsfromfiledialog.h"
#include "ui_loadscientistsfromfiledialog.h"
#include "servicelayer.h"

using namespace std;

LoadScientistsFromFileDialog::LoadScientistsFromFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadScientistsFromFileDialog)
{
    ui->setupUi(this);
}

LoadScientistsFromFileDialog::~LoadScientistsFromFileDialog()
{
    delete ui;
}

void LoadScientistsFromFileDialog::on_ButtonLoad_clicked()
{
    ServiceLayer serve;

    if (!serve.addScientistsFromFile(ui->InputForTextFileName->text().toStdString()))
    {
        ui->LabelErrorMessage->setText("<span style ='color: #ff0000 '> Could not load from file </span>");
    }
    else
    {
        this->close();
    }
}

void LoadScientistsFromFileDialog::on_ButtonCancel_clicked()
{
    this->close();
}
