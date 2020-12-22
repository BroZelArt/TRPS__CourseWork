#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <ctime>

/* Директивы имен таблицы, полей таблицы и базы данных */
#define DATABASE_HOSTNAME   "DataBaseCalorCalend"
#define DATABASE_NAME       "DataBase.db"

#define RATIONS                  "RationsTable"
#define RATIONS_DATE             "Date"
#define RATIONS_NAME             "Name"
#define RATIONS_MASS             "Mass"
#define RATIONS_CCAL             "Ccal"
#define RATIONS_PROT             "Prot"
#define RATIONS_FATS             "Fats"
#define RATIONS_CARB             "Carb"


#define REPORTS                  "ReportTable"
#define REPORTS_DATE             "Date"
#define REPORTS_MASS             "Mass"
#define REPORTS_WAIST            "Waist"
#define REPORTS_CHEST            "Chest"
#define REPORTS_HISP             "Hips"



class DataBase : public QObject
{
    Q_OBJECT

public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    /* Методы для непосредственной работы с классом
     * Подключение к базе данных и вставка записей в таблицу
     * */
    void connectToDataBase();
    bool inserIntoDeviceTable(const QVariantList &data);

    void connectToDataBaseRep();
    bool inserIntoRepTable(const QVariantList &data);

     void closeDataBase();
       void closeDataBaseRep();

private:
    // Сам объект базы данных, с которым будет производиться работа
    QSqlDatabase    db;

    QSqlDatabase    dbr;

private:
    /* Внутренние методы для работы с базой данных
     * */
    bool openDataBase();
    bool restoreDataBase();
//    void closeDataBase();
    bool createTables();

    bool openDataBaseRep();
    bool restoreDataBaseRep();
//    void closeDataBaseRep();
};

#endif // DATABASE_H
