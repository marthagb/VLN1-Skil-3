#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "servicelayer.h"
#include "validation.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addScientistButton_clicked();

    void on_deleteScientistButton_clicked();

    void on_updateScientistButton_clicked();

    void on_addScientistsFromFileButton_clicked();

    void on_saveScientistsToFileButton_clicked();

    void on_ascendingRadioButton_clicked();

    void on_descendingRadioButton_clicked();

    void on_addComputerButton_clicked();

    void on_deleteComputerButton_clicked();

    void on_updateComputerButton_clicked();

    void on_saveComputersToFileButton_clicked();

    void on_addComputersFromFileButton_clicked();

    void on_addAssociationButton_clicked();

    void on_deleteAssociationButton_clicked();

    void on_updateAssociationButton_clicked();

    void on_saveAssocToFileButton_clicked();

    void on_pushButton_clicked();


    void on_mainOptions_currentChanged(int index);

    void on_actionAdd_Scientist_triggered();

    void on_actionAdd_Computer_triggered();

    void on_actionAdd_Association_triggered();

    void on_actionExit_Program_triggered();

    void on_scientistTable_clicked();

    void on_computersTable_clicked();

    void on_associationsTable_clicked();

private:
    Ui::MainWindow *ui;

    ServiceLayer serve;
    validation valid;

    void showScientists(vector<Persons> S);
    void showComputers(vector<Computer> C);
    void showAssociations(vector<Association> A);
    void addNewScientist(const Persons& p);
    void addNewComputer(const Computer& c);
    void addNewAssociation(const string sN, const string cN);

};

#endif // MAINWINDOW_H
