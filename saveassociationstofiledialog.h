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
    std::string getInput();
    bool getSave();

    explicit saveAssociationsToFileDialog(QWidget *parent = 0);
    ~saveAssociationsToFileDialog();

private slots:
    void on_SaveAssociationsToFile_clicked();

    void on_cancelSaveAssociationsToFile_clicked();

private:
    bool save;
    Ui::saveAssociationsToFileDialog *ui;
};

#endif // SAVEASSOCIATIONSTOFILEDIALOG_H
