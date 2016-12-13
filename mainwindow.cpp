#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addscientistdialog.h"
#include "addcomputerdialog.h"
#include "addassociationdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addScientistButton_clicked()
{
    addScientistDialog addScientistButton;
    addScientistButton.setModal(true);
    addScientistButton.exec();
}

void MainWindow::on_deleteScientistButton_clicked()
{

}

void MainWindow::on_updateScientistButton_clicked()
{

}

void MainWindow::on_addScientistsFromFileButton_clicked()
{

}

void MainWindow::on_saveScientistsToFileButton_clicked()
{

}

void MainWindow::on_ascendingRadioButton_clicked()
{

}

void MainWindow::on_descendingRadioButton_clicked()
{

}

void MainWindow::on_addComputerButton_clicked()
{

}

void MainWindow::on_deleteComputerButton_clicked()
{

}

void MainWindow::on_updateComputerButton_clicked()
{

}

void MainWindow::on_saveComputersToFileButton_clicked()
{

}

void MainWindow::on_addComputersFromFileButton_clicked()
{

}

void MainWindow::on_addAssociationButton_clicked()
{

}

void MainWindow::on_deleteAssociationButton_clicked()
{

}

void MainWindow::on_updateAssociationButton_clicked()
{

}

void MainWindow::on_saveAssocToFileButton_clicked()
{
    addComputerDialog addComputerButton;
    addComputerButton.setModal(true);
    addComputerButton.exec();

}

void MainWindow::on_pushButton_clicked()
{
    addComputerDialog addComputerButton;
    addComputerButton.setModal(true);
    addComputerButton.exec();
}
