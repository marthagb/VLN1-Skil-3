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

    bool getLoad();

    std::string getFile();

private slots:
    void on_ButtonLoad_clicked();

    void on_ButtonCancel_clicked();

    void on_InputForTextFileName_returnPressed();

private:
    Ui::LoadComputersFromFile *ui;

    bool load;

    std::string file;
};

#endif // LOADCOMPUTERSFROMFILE_H
