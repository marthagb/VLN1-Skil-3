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

private:
    Ui::updatescientist *ui;
};

#endif // UPDATESCIENTIST_H
