#include "updatescientist.h"
#include "ui_updatescientist.h"

updatescientist::updatescientist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::updatescientist)
{
    ui->setupUi(this);
    update = false;
    hasImage = false;
}

updatescientist::~updatescientist()
{
    delete ui;
}

//Takes in name of selected scientist and fills
//the name window in the dialog.
void updatescientist::setName(const std::string s)
{
    ui->updateNameInput->setText(QString::fromStdString(s));
}

//Takes in gender of selected scientist and selects
//the gender box in the dialog
void updatescientist::setGender(const std::string g)
{
    if(g == "F")
    {
        ui->updateGenderBox->setCurrentText(QString::fromStdString("Female"));

    }
    else if(g == "M")
    {
        ui->updateGenderBox->setCurrentText(QString::fromStdString("Male"));
    }
}

//Takes in the birth year of selected scientist
//and fills the birth year window in the dialog
void updatescientist::setBirthYear(const int bY)
{
    QDate b(bY, 1, 1);
    ui->updateBirthYear->setDate(b);
}

//Takes in the death year of selected scientist
//and fills the death year window in the dialog
void updatescientist::setDeathYear(const int dY)
{
    QDate d(dY, 1, 1);
    ui->updateDeathYear->setDate(d);
}

//Sets the status of the check box "alive"
void updatescientist::setCheckBox()
{
    ui->aliveCheckBox->setChecked(true);
}

void updatescientist::setFunFact(QString fF)
{
    ui->updateFunFactInput->setText(fF);
}

//Updates the name in the dialog
std::string updatescientist::getName()
{
    std::string name = ui->updateNameInput->text().toStdString();

    return name;
}

//Updates the name in the dialog
std::string updatescientist::getGender()
{
    std::string gender = ui->updateGenderBox->currentText().toStdString().substr(0, 1);

    return gender;
}

//Updates the birth year in the dialog
std::string updatescientist::getBirthYear()
{
    int bY = ui->updateBirthYear->date().year();
    std::string birthYear = std::to_string(bY);

    return birthYear;
}

//Updates the death year in the dialog
std::string updatescientist::getDeathYear()
{
    int dY = ui->updateDeathYear->date().year();
    std::string deathYear = std::to_string(dY);

    return deathYear;
}

//Gets the status of the "alive" check box
bool updatescientist::getCheckBox()
{
    if(ui->aliveCheckBox->isChecked())
    {
        return true;
    }
    else
    {
        return false;
    }
}

QString updatescientist::getFunFact()
{
    QString fF = ui->updateFunFactInput->text();
    return fF;
}

bool updatescientist::getUpdate()
{
    return update;
}

//Updates the scientist
void updatescientist::on_updateScientistButton_clicked()
{
    update = true;
    this->close();
}

//Closes the dialog if cancel is pressed
void updatescientist::on_cancelUpdateScientistButton_clicked()
{
    update = false;
    this->close();
}

QString updatescientist::getFile()
{
    return imageName;
}
bool updatescientist::getUpdatePictureButton()
{
    return hasImage;
}

void updatescientist::setPic(QPixmap qp)
{

    ui->UpdatePictureLabel->setPixmap(qp);
    ui->UpdatePictureLabel->setScaledContents(true);
}

void updatescientist::on_UpdatePictureButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, ("Choose"), "", tr("images(*.png *.jpg *.jpeg *.bmp *.gif)"));

    if(QString::compare(filename, QString()) != 0)
    {
        QImage image;
        bool valid = image.load(filename);

        if(valid)
        {
            image = image.scaledToWidth(ui->UpdatePictureLabel->width(), Qt::SmoothTransformation);
            ui->UpdatePictureLabel->setPixmap(QPixmap::fromImage(image));
            hasImage = true;
            imageName = filename;
        }
        else
        {
            //TODO: error check
        }
    }
}
