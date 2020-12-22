#ifndef NEW_DISH_H
#define NEW_DISH_H

#include <QDialog>

namespace Ui {
class new_dish;
}

class new_dish : public QDialog
{
    Q_OBJECT

public:
    explicit new_dish(QWidget *parent = nullptr);
    ~new_dish();

private slots:
    void on_pushButton_clicked();

private:
    Ui::new_dish *ui;
};

#endif // NEW_DISH_H
