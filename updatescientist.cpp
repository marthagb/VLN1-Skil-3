#include "updatescientist.h"
#include "ui_updatescientist.h"

updatescientist::updatescientist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::updatescientist)
{
    ui->setupUi(this);
    hasImage = false;
}

updatescientist::~updatescientist()
{
    delete ui;
}

void updatescientist::setName(const std::string s)
{
    ui->updateNameInput->setText(QString::fromStdString(s));
}

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

void updatescientist::setBirthYear(const int bY)
{
    QDate b(bY, 1, 1);
    ui->updateBirthYear->setDate(b);
}

void updatescientist::setDeathYear(const int dY)
{
    QDate d(dY, 1, 1);
    ui->updateDeathYear->setDate(d);
}

void updatescientist::setCheckBox()
{
    ui->aliveCheckBox->setChecked(true);
}

std::string updatescientist::getName()
{
    std::string name = ui->updateNameInput->text().toStdString();

    return name;
}

std::string updatescientist::getGender()
{
    std::string gender = ui->updateGenderBox->currentText().toStdString().substr(0, 1);

    return gender;
}

std::string updatescientist::getBirthYear()
{
    int bY = ui->updateBirthYear->date().year();
    std::string birthYear = std::to_string(bY);

    return birthYear;
}

std::string updatescientist::getDeathYear()
{
    int dY = ui->updateDeathYear->date().year();
    std::string deathYear = std::to_string(dY);

    return deathYear;
}

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

bool updatescientist::getUpdate()
{
    return update;
}

void updatescientist::on_updateScientistButton_clicked()
{
    update = true;
    this->close();
}

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
