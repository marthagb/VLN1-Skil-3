#ifndef SAVESCIENTISTSTOFILEDIALOG_H
#define SAVESCIENTISTSTOFILEDIALOG_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class saveScientistsToFileDialog;
}

class saveScientistsToFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit saveScientistsToFileDialog(QWidget *parent = 0);
    ~saveScientistsToFileDialog();

    std::string getInput();
    bool getSave();

private slots:
    void on_saveScientistsToFile_clicked();

    void on_cancelSaveScientistsToFile_clicked();

  //  void on_saveToFileLabel_linkActivated(const QString &link);

private:
    Ui::saveScientistsToFileDialog *ui;
    bool save;
};

#endif // SAVESCIENTISTSTOFILEDIALOG_H
