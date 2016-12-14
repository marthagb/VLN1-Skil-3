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
    explicit saveComputersToFileDialog(QWidget *parent = 0);
    ~saveComputersToFileDialog();

private:
    Ui::saveComputersToFileDialog *ui;
};

#endif // SAVECOMPUTERSTOFILEDIALOG_H
