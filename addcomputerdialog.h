#ifndef ADDCOMPUTERDIALOG_H
#define ADDCOMPUTERDIALOG_H

#include <QDialog>

namespace Ui {
class addComputerDialog;
}

class addComputerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addComputerDialog(QWidget *parent = 0);
    ~addComputerDialog();

private slots:
    void on_cancelComputerAddButton_clicked();

    void on_cancelAddComputerButton_clicked();

private:
    Ui::addComputerDialog *ui;
};

#endif // ADDCOMPUTERDIALOG_H
