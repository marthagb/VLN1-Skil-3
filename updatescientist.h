#ifndef UPDATESCIENTIST_H
#define UPDATESCIENTIST_H

#include <QDialog>

namespace Ui {
class updatescientist;
}

class updatescientist : public QDialog
{
    Q_OBJECT

public:
    explicit updatescientist(QWidget *parent = 0);
    ~updatescientist();

    void setName(const std::string s);
    void setGender(const std::string g);
    void setBirthYear(const int bY);
    void setDeathYear(const int dY);
    void setCheckBox();

    std::string getName();
    std::string getGender();
    std::string getBirthYear();
    std::string getDeathYear();

    bool getCheckBox();
    bool getUpdate();

private slots:
    void on_updateScientistButton_clicked();

    void on_cancelUpdateScientistButton_clicked();

private:
    Ui::updatescientist *ui;

    bool update;
};

#endif // UPDATESCIENTIST_H
