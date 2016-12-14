#include "savescientiststofiledialog.h"
#include "ui_savescientiststofiledialog.h"

saveScientistsToFileDialog::saveScientistsToFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::saveScientistsToFileDialog)
{
    ui->setupUi(this);
}

saveScientistsToFileDialog::~saveScientistsToFileDialog()
{
    delete ui;
}
