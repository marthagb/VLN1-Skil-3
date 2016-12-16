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

    void setScientistList(vector<Persons> S);

    void setComputerList(vector<Computer> C);

private slots:
    void on_cancelAddAssociationButton_clicked();

    void on_addAssociationButton_clicked();

    void on_addAssociationDialog_rejected();

    void on_scientistList_clicked();

    void on_computersList_clicked();

private:
    Ui::addAssociationDialog *ui;

    bool add;
};

#endif // ADDASSOCIATIONDIALOG_H
