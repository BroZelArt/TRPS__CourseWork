#include "statistics.h"
#include "ui_statistics.h"

Statistics::Statistics(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Statistics)
{
    ui->setupUi(this);
    dbr = new DataBase();
    dbr->connectToDataBaseRep();
}

Statistics::~Statistics()
{
    delete ui;
}

void Statistics::on_Back_button_clicked()
{
    QWidget::close();
}

void Statistics::on_graph_clicked()
{

    // НЕОБХОДИМА ДОРАБОТКА!

/*    ui->widget->clearGraphs();//Если нужно, но очищаем все графики
    model = new QSqlTableModel(this);
    model->setTable(REPORTS);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
 */
    bool OK;
    int datestart = ui->dateEditStart->text().toInt(&OK, 10);
    QString datefin = ui->dateEditFin->date().toString();
    QSqlQuery query;
    QString str = QString("SELECT " REPORTS_DATE " , " REPORTS_MASS ", " REPORTS_WAIST ", " REPORTS_CHEST ", " REPORTS_HISP " FROM " REPORTS "  WHERE ( "
                          REPORTS_DATE " >= DATEPART('%1') AND " REPORTS_DATE " <= DATEPART('%2') )").arg(ui->dateEditStart->text(),ui->dateEditFin->text());
 //   QString str = QString("SELECT * FROM " REPORTS );


        query.prepare(str);
        query.exec();
 //   query.next();
    QVector<double> x(20), Dy(20), My(20), Wy(20), Cy(20), Hy(20);

    INT i =0;
    while (query.next()) {
        x[i]=query.value(0).toInt();
        Dy[i]=query.value(1).toInt();
        My[i]=query.value(2).toInt();
        Wy[i]=query.value(3).toInt();
        Cy[i]=query.value(4).toInt();
        Hy[i]=query.value(5).toInt();
        i++;
    }
    i--;
    if (i!=-1){
    double a = x[0]; //Начало интервала, где рисуем график по оси Ox
    double b = x[i]; //Конец интервала, где рисуем график по оси Ox



    //Добавляем один график в widget
    ui->widget->addGraph();
    //Говорим, что отрисовать нужно график по нашим двум массивам x и y
    ui->widget->graph(0)->setData(Dy, My);

    //Подписываем оси Ox и Oy
    ui->widget->xAxis->setLabel("Дата");
    ui->widget->yAxis->setLabel("Значения");
//тут тоже надо делать мин макс
    //Установим область, которая будет показываться на графике
    ui->widget->xAxis->setRange(0,120 );//Для оси Ox

    //Для показа границ по оси Oy сложнее, так как надо по правильному
    //вычислить минимальное и максимальное значение в векторах
    double minY = My[0], maxY = My[0];
    for (int j=1; j<=i; j++)
    {
        if (My[j]<minY) minY = My[j];
        if (My[j]>maxY) maxY = My[j];
    }
    ui->widget->yAxis->setRange(minY, maxY);//Для оси Oy

    //И перерисуем график на нашем widget
    ui->widget->replot();

    }
    else{
        QMessageBox::warning(this, "Предупреждение", "За данный период статистики нет");

    }
}

void Statistics::on_pushButton_clicked()
{
    bool OK;
     int datestart = ui->dateEditStart->text().toInt(&OK, 10);
}
