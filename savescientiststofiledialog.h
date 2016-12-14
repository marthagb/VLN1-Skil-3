#ifndef SAVESCIENTISTSTOFILEDIALOG_H
#define SAVESCIENTISTSTOFILEDIALOG_H

#include <QDialog>

namespace Ui {
class saveScientistsToFileDialog;
}

class saveScientistsToFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit saveScientistsToFileDialog(QWidget *parent = 0);
    ~saveScientistsToFileDialog();

private:
    Ui::saveScientistsToFileDialog *ui;
};

#endif // SAVESCIENTISTSTOFILEDIALOG_H
