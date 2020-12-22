#ifndef NEW_RATION_H
#define NEW_RATION_H

#include <QDialog>
#include "info_pers.h"

namespace Ui {
class new_ration;
}

class new_ration : public QDialog
{
    Q_OBJECT

public:
    explicit new_ration(QWidget *parent = nullptr);
    ~new_ration();

private slots:
    void on_pushButton_clicked();

    void on_Back_button_clicked();

private:
    Ui::new_ration *ui;
};

#endif // NEW_RATION_H
