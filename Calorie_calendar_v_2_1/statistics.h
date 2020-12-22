#ifndef STATISTICS_H
#define STATISTICS_H

#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QMessageBox>
#include <qcustomplot.h>
#include "database.h"
namespace Ui {
class Statistics;
}

class Statistics : public QDialog
{
    Q_OBJECT

public:
    explicit Statistics(QWidget *parent = nullptr);
    ~Statistics();

private slots:
    void on_Back_button_clicked();

    void on_graph_clicked();

    void on_pushButton_clicked();

private:
    Ui::Statistics *ui;
    DataBase *dbr, *db;
    QCustomPlot *customPlot;    // Объявляем графическое полотно
    QCPGraph *graphic;          // Объявляем график
    QSqlTableModel  *model;
};

#endif // STATISTICS_H
