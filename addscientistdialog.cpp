#include "addscientistdialog.h"
#include "ui_addscientistdialog.h"
#include "datalayer.h"

addScientistDialog::addScientistDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addScientistDialog)
{
    ui->setupUi(this);
    add = false;
}

addScientistDialog::~addScientistDialog()
{
    delete ui;
}

void addScientistDialog::on_cancelAddScientistButton_clicked()
{
    this->close();
}

void addScientistDialog::on_addScientistButton_clicked()
{
    add = true;
    this->close();
}

Persons addScientistDialog::newScientist()
{
    string n = ui->nameInput->text().toStdString();
    char g = ui->genderBox->currentText().toStdString()[0];
    int bY = ui->birthYearEdit->date().year();
    int dY = 0;

    if (!ui->diedCheckBox->isChecked())
    {
        dY = ui->deathYearEdit->date().year();
    }

    Persons p(n, g, bY, dY);

    return p;
}

bool addScientistDialog::getAdd()
{
    return add;
}

void addScientistDialog::on_btn_image_clicked()
{
    DataLayer dl;
    QString filename = QFileDialog::getOpenFileName(this, ("Choose"), "", tr("images(*.png *.jpg *.jpeg *.bmp *.gif)"));

    if(QString::compare(filename, QString()) != 0)
    {
        QImage image;
        bool valid = image.load(filename);

        if(valid)
        {
            image = image.scaledToWidth(ui->lbl_image->width(), Qt::SmoothTransformation);
            ui->lbl_image->setPixmap(QPixmap::fromImage(image));
            dl.addPicToScientists(filename);


        }
        else
        {

            //TODO: error check
        }
    }
}
