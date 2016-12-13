#ifndef ADDASSOCIATIONDIALOG_H
#define ADDASSOCIATIONDIALOG_H

#include <QDialog>
#include "association.h"

namespace Ui {
class addAssociationDialog;
}

class addAssociationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addAssociationDialog(QWidget *parent = 0);
    ~addAssociationDialog();

    vector<string> newAssociation();

    bool getAdd();

private slots:
    void on_cancelAddAssociationButton_clicked();

    void on_addAssociationButton_clicked();

private:
    Ui::addAssociationDialog *ui;

    bool add;
};

#endif // ADDASSOCIATIONDIALOG_H
