#ifndef ADDCOMPUTERDIALOG_H
#define ADDCOMPUTERDIALOG_H

#include <QDialog>
#include "computer.h"

namespace Ui {
class addComputerDialog;
}

class addComputerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addComputerDialog(QWidget *parent = 0);
    ~addComputerDialog();

    Computer newComputer();

    bool getAdd();

private slots:

    void on_cancelAddComputerButton_clicked();

    void on_addComputerButton_clicked();

    void on_addComputerDialog_rejected();

private:
    Ui::addComputerDialog *ui;

    bool add;
};

#endif // ADDCOMPUTERDIALOG_H
