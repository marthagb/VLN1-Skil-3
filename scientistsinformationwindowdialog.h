#ifndef SCIENTISTSINFORMATIONWINDOWDIALOG_H
#define SCIENTISTSINFORMATIONWINDOWDIALOG_H

#include <QDialog>

namespace Ui {
class ScientistsInformationWindowDialog;
}

class ScientistsInformationWindowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScientistsInformationWindowDialog(QWidget *parent = 0);
    ~ScientistsInformationWindowDialog();

private:
    Ui::ScientistsInformationWindowDialog *ui;
};

#endif // SCIENTISTSINFORMATIONWINDOWDIALOG_H
