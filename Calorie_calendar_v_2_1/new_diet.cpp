#include "new_diet.h"
#include "ui_new_dish.h"
#include <QMessageBox>

new_dish::new_dish(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_dish)
{
    ui->setupUi(this);
}

new_dish::~new_dish()
{
    delete ui;
}

void new_dish::on_pushButton_clicked()
{
    //Ввод переменных
    QString Dish_name = ui->dish_name->text();
    double Dish_mass = ui->dish_mass->text().toDouble();
    double Dish_kal = ui->dish_cal->text().toDouble();
    double Dish_prot = ui->dish_prot->text().toDouble();
    double Dish_fats = ui->dish_fats->text().toDouble();
    double Dish_carb = ui->dish_carb->text().toDouble();

    if ((Dish_name=="")||(Dish_prot=0)||(Dish_fats=0)||(Dish_kal=0)||(Dish_carb=0))
       QMessageBox::warning(this, "Предупреждение", "проверьте корректность введённой информации");
    else
    {
  ui->done->setText("Блюдо " + Dish_name + " массой " + Dish_mass + "добавлено!");
    }
}
