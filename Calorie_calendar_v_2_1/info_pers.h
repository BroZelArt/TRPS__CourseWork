#ifndef INFO_PERS_H
#define INFO_PERS_H
#include <QSettings>
#include <QTextEdit>
#include <QDialog>

namespace Ui {
class info_pers;
}

class info_pers : public QDialog
{
    Q_OBJECT

public:
    explicit info_pers(QWidget *parent = nullptr);
    ~info_pers();
    double Prot=0;
    double Fats=0;
    double Carb=0;
    double Kkal=0;
    int Height=0;
    double Mass=0;
private slots:
    void on_confirm_clicked();

    void on_Back_button_clicked();

private:
    Ui::info_pers *ui;

    int Age=0;
    QString Pers_name;
 //   bool info_introd=0;
    double Phis_act=0;
};


#endif // INFO_PERS_H
