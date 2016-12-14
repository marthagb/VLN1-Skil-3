#include "loadscientistsfromfiledialog.h"
#include "ui_loadscientistsfromfiledialog.h"

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
    load = true;
    this->close();
}

void LoadScientistsFromFileDialog::on_ButtonCancel_clicked()
{
    load = false;
    this->close();
}

std::string LoadScientistsFromFileDialog::getInput()
{
    return ui->InputForTextFileName->text().toStdString();
}

bool LoadScientistsFromFileDialog::getLoad()
{
    return load;
}
