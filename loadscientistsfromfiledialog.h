#ifndef LOADSCIENTISTSFROMFILEDIALOG_H
#define LOADSCIENTISTSFROMFILEDIALOG_H

#include <QDialog>

namespace Ui {
class LoadScientistsFromFileDialog;
}

class LoadScientistsFromFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoadScientistsFromFileDialog(QWidget *parent = 0);
    ~LoadScientistsFromFileDialog();

    bool getLoad();

    std::string getFile();

private slots:
    void on_ButtonLoad_clicked();

    void on_ButtonCancel_clicked();

    void on_InputForTextFileName_returnPressed();

private:
    Ui::LoadScientistsFromFileDialog *ui;

    bool load;

    std::string file;
};

#endif // LOADSCIENTISTSFROMFILEDIALOG_H
