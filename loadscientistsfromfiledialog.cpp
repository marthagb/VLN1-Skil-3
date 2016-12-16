#include "loadscientistsfromfiledialog.h"
#include "ui_loadscientistsfromfiledialog.h"

using namespace std;

LoadScientistsFromFileDialog::LoadScientistsFromFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadScientistsFromFileDialog)
{
    ui->setupUi(this);
    load = false;
}

LoadScientistsFromFileDialog::~LoadScientistsFromFileDialog()
{
    delete ui;
}

void LoadScientistsFromFileDialog::on_ButtonLoad_clicked()
{
    file = ui->InputForTextFileName->text().toStdString();
    load = true;
    this->close();
}

void LoadScientistsFromFileDialog::on_ButtonCancel_clicked()
{
    this->close();
}

bool LoadScientistsFromFileDialog::getLoad()
{
    return load;
}

string LoadScientistsFromFileDialog::getFile()
{
    return file;
}
