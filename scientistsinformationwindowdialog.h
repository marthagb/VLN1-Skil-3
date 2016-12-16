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

    void setImage(QByteArray arr);

private:
    Ui::ScientistsInformationWindowDialog *ui;
    QByteArray image;

    void ShowPicture();
};

#endif // SCIENTISTSINFORMATIONWINDOWDIALOG_H
