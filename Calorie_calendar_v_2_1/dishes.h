#ifndef DISHES_H
#define DISHES_H

#include <QDialog>

namespace Ui {
class dishes;
}

class dishes : public QDialog
{
    Q_OBJECT

public:
    explicit dishes(QWidget *parent = nullptr);
    ~dishes();

private:
    Ui::dishes *ui;
};

#endif // DISHES_H
