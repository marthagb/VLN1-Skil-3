#ifndef SAVEASSOCIATIONSTOFILEDIALOG_H
#define SAVEASSOCIATIONSTOFILEDIALOG_H

#include <QDialog>

namespace Ui {
class saveAssociationsToFileDialog;
}

class saveAssociationsToFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit saveAssociationsToFileDialog(QWidget *parent = 0);
    ~saveAssociationsToFileDialog();

private:
    Ui::saveAssociationsToFileDialog *ui;
};

#endif // SAVEASSOCIATIONSTOFILEDIALOG_H
