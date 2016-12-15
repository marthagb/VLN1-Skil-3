#ifndef UPDATECOMPUTER_H
#define UPDATECOMPUTER_H

#include <QDialog>

namespace Ui {
class updateComputer;
}

class updateComputer : public QDialog
{
    Q_OBJECT

public:
    explicit updateComputer(QWidget *parent = 0);
    ~updateComputer();

    void setName(const std::string s);
    void setYearMade(const int yM);
    void setType(const std::string t);
    void setBuilt(const std::string b);

    std::string getName();
    std::string getYearMade();
    std::string getType();
    std::string getBuilt();

    bool getUpdate();

private slots:
    void on_updateComputerButton_clicked();

    void on_cancelAddComputerButton_clicked();

private:
    Ui::updateComputer *ui;

    bool update;
};

#endif // UPDATECOMPUTER_H
