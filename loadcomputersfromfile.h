#ifndef LOADCOMPUTERSFROMFILE_H
#define LOADCOMPUTERSFROMFILE_H

#include <QDialog>

namespace Ui {
class LoadComputersFromFile;
}

class LoadComputersFromFile : public QDialog
{
    Q_OBJECT

public:
    explicit LoadComputersFromFile(QWidget *parent = 0);
    ~LoadComputersFromFile();

private slots:
    void on_ButtonLoad_clicked();

    void on_ButtonCancel_clicked();

private:
    Ui::LoadComputersFromFile *ui;
};

#endif // LOADCOMPUTERSFROMFILE_H
