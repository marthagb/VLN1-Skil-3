#ifndef SCIENTISTSINFORMATIONWINDOWDIALOG_H
#define SCIENTISTSINFORMATIONWINDOWDIALOG_H
#include <QDialog>
#include <QFileDialog>


namespace Ui {
class ScientistsInformationWindowDialog;
}

class ScientistsInformationWindowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScientistsInformationWindowDialog(QWidget *parent = 0);
    ~ScientistsInformationWindowDialog();

    void setImage(QPixmap qp);

    void setName(QString n);

    void setBirthYear(QString bY);

    void setDeathYear(QString dY);

    void setAge(QString a);

    void setFunFact(QString fF);

    void ShowPicture();

private:
    Ui::ScientistsInformationWindowDialog *ui;
    QPixmap image;

};

#endif // SCIENTISTSINFORMATIONWINDOWDIALOG_H
