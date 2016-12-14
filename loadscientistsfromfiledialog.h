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


private slots:
    void on_ButtonLoad_clicked();

    void on_ButtonCancel_clicked();

private:
    Ui::LoadScientistsFromFileDialog *ui;
};

#endif // LOADSCIENTISTSFROMFILEDIALOG_H
