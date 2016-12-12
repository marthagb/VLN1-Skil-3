#include "mainwindow.h"
#include "ui_mainwindow.h"

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
