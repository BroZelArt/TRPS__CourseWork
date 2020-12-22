#include "new_ration.h"
#include "ui_new_ration.h"
#include "info_pers.h"
#include <QMessageBox>

new_ration::new_ration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_ration)
{
    ui->setupUi(this);
}

new_ration::~new_ration()
{
    delete ui;
}

void new_ration::on_pushButton_clicked()
{
    //Ввод переменных
    QString Rat_name = ui->rat_name->text();
    double Rat_mass = ui->rat_mass->text().toDouble();
    double Rat_kal = ui->rat_cal->text().toDouble();
    double Rat_prot = ui->rat_prot->text().toDouble();
    double Rat_fats = ui->rat_fats->text().toDouble();
    double Rat_carb = ui->rat_carb->text().toDouble();

    if ((Rat_name=="")||(Rat_prot=0)||(Rat_fats=0)||(Rat_kal=0)||(Rat_carb=0)||(Rat_mass==0))
        QMessageBox::warning(this, "Предупреждение", "проверьте корректность введённой информации");
    else
    {

        ui->done->setText(", блюдо " + Rat_name + " с массой " + QString::number(Rat_mass) + " добавлено!");
    }
}

void new_ration::on_Back_button_clicked()
{
    QWidget::close();
}
