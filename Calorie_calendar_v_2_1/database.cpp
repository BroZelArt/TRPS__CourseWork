#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{

}

/* Методы для подключения к базе данных
 * */
void DataBase::connectToDataBase()
{
    /* Перед подключением к базе данных производим проверку на её существование.
     * В зависимости от результата производим открытие базы данных или её восстановление
     * */
    if(!QFile("C:/TRPS/Calorie_calendar_v_2_0/" DATABASE_NAME).exists()){
        this->restoreDataBase();
    } else {
        this->openDataBase();
    }
}

/* Методы восстановления базы данных
 * */
bool DataBase::restoreDataBase()
{
    if(this->openDataBase()){
        if(!this->createTables()){
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
bool DataBase::openDataBase()
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName("C:/TRPS/Calorie_calendar_v_2_0/" DATABASE_NAME);
    if(db.open()){
        return true;
    } else {
        return false;
    }
}

/* Методы закрытия базы данных
 * */
void DataBase::closeDataBase()
{
    db.close();
}

/* Метод для создания таблицы в базе данных
 * */
bool DataBase::createTables()
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
    QSqlQuery query;
    QSqlQuery query1;
    if((!query.exec( "CREATE TABLE " RATIONS " ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    RATIONS_DATE   " INTEGER    NOT NULL,"
                    RATIONS_NAME   " VARCHAR(255)    NOT NULL,"
                    RATIONS_MASS   " REAL     NOT NULL,"
                    RATIONS_CCAL   " REAL     NOT NULL,"
                    RATIONS_PROT   " REAL     NOT NULL,"
                    RATIONS_FATS   " REAL     NOT NULL,"
                    RATIONS_CARB   " REAL     NOT NULL"
                    " ) "
                    )) || (
       (!query1.exec( "CREATE TABLE " REPORTS " ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            REPORTS_DATE   " INTEGER    NOT NULL,"
                            REPORTS_MASS   " INTEGER     NOT NULL,"
                            REPORTS_CHEST  " INTEGER     NOT NULL,"
                            REPORTS_WAIST  " INTEGER    NOT NULL,"
                            REPORTS_HISP   " INTEGER     NOT NULL"
                            " )")))){
        qDebug() << "DataBase: error of create " << RATIONS;
        qDebug() << query.lastError().text();
        qDebug() << query1.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

/* Метод для вставки записи в базу данных
 * */
bool DataBase::inserIntoDeviceTable(const QVariantList &data)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    query.prepare("INSERT INTO " RATIONS " (" RATIONS_DATE ", " RATIONS_NAME ", " RATIONS_MASS ",  " RATIONS_CCAL ", " RATIONS_PROT ", " RATIONS_FATS ", " RATIONS_CARB ",) "
    "VALUES (:Date,:Name, :Mass, :Ccal, :Prot, :Fats, :Carb )");
    query.bindValue(":Date",         data[0]);
    query.bindValue(":Name",         data[0].toString());
    query.bindValue(":Mass",         data[1].toString());
    query.bindValue(":Ccal",         data[2].toString());
    query.bindValue(":Prot",         data[3].toString());
    query.bindValue(":Fats",         data[4].toString());
    query.bindValue(":Carb",         data[5].toString());
    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << RATIONS;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}



/* Методы для подключения к базе данных
 * */
void DataBase::connectToDataBaseRep()
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
bool DataBase::restoreDataBaseRep()
{
    if(this->openDataBaseRep()){
        if(!this->createTables()){
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
bool DataBase::openDataBaseRep()
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    dbr = QSqlDatabase::addDatabase("QSQLITE");
    dbr.setHostName(DATABASE_HOSTNAME);
    dbr.setDatabaseName("C:/TRPS/Calorie_calendar_v_2_0/" DATABASE_NAME);
    if(dbr.open()){
        return true;
    } else {
        return false;
    }
}

/* Методы закрытия базы данных
 * */
void DataBase::closeDataBaseRep()
{
    dbr.close();
}

/* Метод для создания таблицы в базе данных
 * */


/* Метод для вставки записи в базу данных
 * */
bool DataBase::inserIntoRepTable(const QVariantList &data)
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

