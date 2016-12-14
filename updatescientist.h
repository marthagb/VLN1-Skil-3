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

private:
    Ui::updatescientist *ui;
};

#endif // UPDATESCIENTIST_H
