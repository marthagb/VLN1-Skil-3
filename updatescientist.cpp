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
