#ifndef DATABASESTAT_H
#define DATABASESTAT_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

/* Директивы имен таблицы, полей таблицы и базы данных */
#define DATABASE_HOSTNAME   "ExampleDataBase"
#define DATABASE_NAME       "DataBase.db"

#define REPORTS                  "ReportTable"
#define REPORTS_DATE             "Date"
#define REPORTS_MASS             "Mass"
#define REPORTS_WAIST            "Waist"
#define REPORTS_CHEST            "Chest"
#define REPORTS_HISP             "Hips"


class DataBaseRep : public QObject
{
    Q_OBJECT

public:
    explicit DataBaseRep(QObject *parent = 0);
    ~DataBaseRep();

    /* Методы для непосредственной работы с классом
     * Подключение к базе данных и вставка записей в таблицу
     * */
    void connectToDataBaseRep();
    bool inserIntoRepTable(const QVariantList &data);

private:
    // Сам объект базы данных, с которым будет производиться работа
    QSqlDatabase    dbr;

private:
    /* Внутренние методы для работы с базой данных
     * */
    bool openDataBaseRep();
    bool restoreDataBaseRep();
    void closeDataBaseRep();
    bool createRepTable();
};

#endif // DATABASESTAT_H
