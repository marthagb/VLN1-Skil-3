#ifndef ADDASSOCIATIONDIALOG_H
#define ADDASSOCIATIONDIALOG_H

#include <QDialog>

namespace Ui {
class addAssociationDialog;
}

class addAssociationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addAssociationDialog(QWidget *parent = 0);
    ~addAssociationDialog();

private slots:
    void on_cancelAddAssociationButton_clicked();

private:
    Ui::addAssociationDialog *ui;
};

#endif // ADDASSOCIATIONDIALOG_H
