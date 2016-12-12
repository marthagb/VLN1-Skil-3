#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
