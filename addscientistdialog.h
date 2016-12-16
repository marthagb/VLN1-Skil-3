#ifndef ADDSCIENTISTDIALOG_H
#define ADDSCIENTISTDIALOG_H

#include <QDialog>
#include "persons.h"
#include <QFileDialog>
#include "datalayer.h"

namespace Ui {
class addScientistDialog;
}

class addScientistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addScientistDialog(QWidget *parent = 0);
    ~addScientistDialog();

    Persons newScientist();

    bool getAdd();

private slots:
    void on_cancelAddScientistButton_clicked();

    void on_addScientistButton_clicked();

    void on_btn_image_clicked();

private:
    Ui::addScientistDialog *ui;

    bool add;
};

#endif // ADDSCIENTISTDIALOG_H
