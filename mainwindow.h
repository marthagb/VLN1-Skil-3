#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "servicelayer.h"
#include "validation.h"
#include <QFileDialog>

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

    void on_addComputerButton_clicked();

    void on_deleteComputerButton_clicked();

    void on_updateComputerButton_clicked();

    void on_saveComputersToFileButton_clicked();

    void on_addComputersFromFileButton_clicked();

    void on_addAssociationButton_clicked();

    void on_deleteAssociationButton_clicked();

    void on_saveAssocToFileButton_clicked();


    void on_mainOptions_currentChanged(int index);

    void on_actionAdd_Scientist_triggered();

    void on_actionAdd_Computer_triggered();

    void on_actionAdd_Association_triggered();

    void on_actionExit_Program_triggered();

    void on_scientistTable_clicked();

    void on_computersTable_clicked();

    void on_associationsTable_clicked();

    void on_searchScientistsByBox_currentTextChanged(const QString &arg1);

    void on_searchComputersByBox_currentTextChanged(const QString &arg1);

    void on_searchAssocByBox_currentTextChanged(const QString &arg1);

    void on_searchInputScientists_returnPressed();

    void on_searchInputComputers_returnPressed();

    void on_searchInputAssociations_returnPressed();

    void on_lastYearInputScientist_returnPressed();

    void on_lastYearInputComputers_returnPressed();

    void on_lastYearInputAssoc_returnPressed();

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

    void searchScientist();
    void searchComputer();
    void searchAssociation();

};

#endif // MAINWINDOW_H
