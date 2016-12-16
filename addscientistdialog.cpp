#include "addscientistdialog.h"
#include "ui_addscientistdialog.h"

addScientistDialog::addScientistDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addScientistDialog)
{
    ui->setupUi(this);
    add = false;
    hasImage = false;
}

addScientistDialog::~addScientistDialog()
{
    delete ui;
}

//When cancel button is pressed the window closes
void addScientistDialog::on_cancelAddScientistButton_clicked()
{
    this->close();
}

//When add button is pressed then add = true and adds the person
void addScientistDialog::on_addScientistButton_clicked()
{
    add = true;
    this->close();
}

//Takes in name,gender,birthYear and deathYear
//and puts it in the Persons vector
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

// When the choose image button is clicked then
// it takes in the image and shows it back to you
// And resizes the picture so it fits well.
void addScientistDialog::on_btn_image_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, ("Choose"), "", tr("images(*.png *.jpg *.jpeg *.bmp *.gif)"));

    if(QString::compare(filename, QString()) != 0)
    {
        QImage image;
        bool valid = image.load(filename);

        if(valid)
        {
            image = image.scaledToWidth(ui->lbl_image->width(), Qt::SmoothTransformation);
            ui->lbl_image->setPixmap(QPixmap::fromImage(image));
            hasImage = true;
            imageName = filename;
        }
        else
        {
            //TODO: error check
        }
    }
}

// Returns the name of the image.
QString addScientistDialog::getFile()
{
    return imageName;
}

//Checks if the user pushed the load image button
bool addScientistDialog::getBtnImageClicked()
{
    return hasImage;
}
