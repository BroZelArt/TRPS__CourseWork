#include "info_pers.h"
#include "ui_info_pers.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

info_pers::info_pers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::info_pers)

{
    QTextEdit edit;
    ui->setupUi(this);

    QSettings info("pers_info.conf", QSettings::IniFormat);
    info.beginGroup("Info");
    Pers_name=info.value("Name", -1).toString();
    Age=info.value("Age", -1).toInt();
    Height=info.value("Height", -1).toInt();
    Mass=info.value("Mass", -1).toReal();
    info.endGroup();
    ui->age->setText(QString::number(Age));
    ui->name->setText(Pers_name);
    ui->height->setText(QString::number(Height));
    ui->mass->setText(QString::number(Mass));
}

info_pers::~info_pers()
{
    delete ui;
}


void info_pers::on_confirm_clicked()
{
    //Создание переменных и присвоение им значений
    bool OK;
    Pers_name = ui->name->text();
    Height = ui->height->text().toInt(&OK, 10);
    Age = ui->age->text().toInt(&OK, 10);
    Mass = ui->mass->text().toDouble();

    Phis_act=0;
    if(ui->phisical_act->currentText() =="Отсутствие физических нагрузок, сидячая работа, минимум движения")
        Phis_act=1.2;
    else if(ui->phisical_act->currentText() =="Легкие тренировки или прогулки, небольшая дневная активность в течение дня")
        Phis_act=1.375;
    else if(ui->phisical_act->currentText() =="Тренировки 4-5 раз в неделю, хорошая активность в течение дня")
        Phis_act=1.46;
    else if(ui->phisical_act->currentText() =="Интенсивные тренировки 5-6 раз в неделю, хорошая активность в течение дня")
        Phis_act=1.55;
    else if(ui->phisical_act->currentText() =="Ежедневные тренировки, высокая дневная активность")
        Phis_act=1.64;
    else if(ui->phisical_act->currentText() =="Ежедневные ультра-интенсивные тренировки и высокая дневная активность")
        Phis_act=1.72;
    else if(ui->phisical_act->currentText() =="Спортсмен в период соревновательной активности")
        Phis_act=1.9;


    //Проверка корректности информации
    if((ui->mass->text() == "") || (Mass<2) ||(Age <1) || (Height <13)|| (ui->age->text() == "") || (ui->height->text() == "") || (Pers_name == "")) {
        QMessageBox::warning(this, "Предупреждение", "проверьте корректность введённой информации");
        ui->result->setText("Вы ввели не все данные");
    } else
    {

        // Высчитывание нормы Ккалорий и БЖУ по формуле Маффина-Джеора
        if(ui->sex->currentText() =="Мужчина")
            Kkal = (5 + 10*Mass + 6.25*Height - 5*Age)*Phis_act;
        else
            Kkal = (-161 + 10*Mass + 6.25*Height - 5*Age)*Phis_act;

        Prot=Kkal*0.3/4;
        Fats=Kkal*0.3/9;
        Carb=Kkal*0.4/4;

        ui->result->setText( Pers_name + ", по итогам рссчётов ваша дневная норма калорий,\nбелков, жиров, углеводов такова:\n" +
                             "Ккал: " + QString::number(Kkal) + "; \n" + "Белки: " + QString::number(Prot) + "; \n" +
                             "Жиры: " + QString::number(Fats) + "; \n" + "Углеводы: " + QString::number(Carb) + ";");




    QSettings info("pers_info.conf", QSettings::IniFormat);
    info.beginGroup("Info");
    info.setValue("Kkal", Kkal);
    info.setValue("Prot", Prot);
    info.setValue("Fats", Fats);
    info.setValue("Carb", Carb);
    info.setValue("Name", Pers_name);
    info.setValue("Mass", Mass);
    info.setValue("Age", Age);
    info.setValue("Height",Height);
    info.endGroup();
    }
    // QWidget::close();
}


void info_pers::on_Back_button_clicked()
{
    QWidget::close();
}
