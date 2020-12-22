#include "databaserep.h"



DataBaseRep::DataBaseRep(QObject *parent) : QObject(parent)
{

}

DataBaseRep::~DataBaseRep()
{

}

/* Методы для подключения к базе данных
 * */
void DataBaseRep::connectToDataBaseRep()
{
    /* Перед подключением к базе данных производим проверку на её существование.
     * В зависимости от результата производим открытие базы данных или её восстановление
     * */
    if(!QFile("C:/TRPS/Calorie_calendar_v_2_0/" DATABASE_NAME).exists()){
        this->restoreDataBaseRep();
    } else {
        this->openDataBaseRep();
    }
}

/* Методы восстановления базы данных
 * */
bool DataBaseRep::restoreDataBaseRep()
{
    if(this->openDataBaseRep()){
        if(!this->createRepTable()){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}

/* Метод для открытия базы данных
 * */
bool DataBaseRep::openDataBaseRep()
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    dbr = QSqlDatabase::addDatabase("QSQLITE");
    dbr.setHostName(REPORTS_MASS);
    dbr.setDatabaseName("C:/TRPS/Calorie_calendar_v_2_0/" DATABASE_NAME);
    if(dbr.open()){
        return true;
    } else {
        return false;
    }
}

/* Методы закрытия базы данных
 * */
void DataBaseRep::closeDataBaseRep()
{
    dbr.close();
}

/* Метод для создания таблицы в базе данных
 * */
bool DataBaseRep::createRepTable()
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " REPORTS " ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    REPORTS_DATE   " Date    NOT NULL,"
                    REPORTS_MASS   " INTEGER     NOT NULL,"
                    REPORTS_WAIST  " INTEGER    NOT NULL,"
                    REPORTS_CHEST  " INTEGER     NOT NULL,"
                    REPORTS_HISP   " INTEGER     NOT NULL"
                    " )"
                    )){
        qDebug() << "DataBase: error of create " << REPORTS;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

/* Метод для вставки записи в базу данных
 * */
bool DataBaseRep::inserIntoRepTable(const QVariantList &data)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    query.prepare("INSERT INTO " REPORTS " (" REPORTS_DATE ", " REPORTS_MASS ", " REPORTS_WAIST ",  " REPORTS_CHEST ", " REPORTS_HISP ",) "
                                                                                                                                      "VALUES (:Date, :Mass, :Waist, :Chest, :Hips)");
    query.bindValue(":Date",         data[0]);
    query.bindValue(":Mass",         data[1].toString());
    query.bindValue(":Waist",         data[2].toString());
    query.bindValue(":Chest",         data[3].toString());
    query.bindValue(":Hips",         data[4].toString());
    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << REPORTS;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}
