#ifndef SAVECOMPUTERSTOFILEDIALOG_H
#define SAVECOMPUTERSTOFILEDIALOG_H

#include <QDialog>

namespace Ui {
class saveComputersToFileDialog;
}

class saveComputersToFileDialog : public QDialog
{
    Q_OBJECT

public:
    std::string getInput();
    bool getSave();

    explicit saveComputersToFileDialog(QWidget *parent = 0);
    ~saveComputersToFileDialog();

private slots:
    void on_SaveComputersToFile_clicked();

    void on_cancelSaveComputersToFile_clicked();

private:
    Ui::saveComputersToFileDialog *ui;
    bool save;
};

#endif // SAVECOMPUTERSTOFILEDIALOG_H
