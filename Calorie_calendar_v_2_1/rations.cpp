#include "rations.h"
#include "ui_rations.h"
#include <QListWidget>
#include <QMenuBar>
#include "info_pers.h"

Rations::Rations(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Rations)
{
    ui->setupUi(this);
    db = new DataBase();
    db->connectToDataBase();

    /* Инициализируем модель для представления данных
       * с заданием названий колонок
       * */
    this->setupModel(RATIONS, QStringList()<< "id" << "Дата" << "Название блюда" <<"Масса"  << "Ккал" << "Белки" << "Жиры" << "Углеводы");

    /* Инициализируем внешний вид таблицы с данными
       * */
    this->createUI();
}

Rations::~Rations()
{
    delete ui;
}

/* Метод для инициализации модеи представления данных
 * */
void Rations::setupModel(const QString &tableName, const QStringList &headers)
{
    /* Производим инициализацию модели представления данных
         * */
    modelDevice = new QSqlTableModel(this);
    modelDevice->setTable(tableName);
    modelDevice->select();
    /* Устанавливаем названия колонок в таблице с сортировкой данных
         * */
    for(int i = 0, j = 0; i < modelDevice->columnCount(); i++, j++){
        modelDevice->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
}

void Rations::createUI()
{
    ui->deviceTableView->setModel(modelDevice);     // Устанавливаем модель на TableView
    ui->deviceTableView->setColumnHidden(0, true);    // Скрываем колонку с id записей
    // Разрешаем выделение строк
    ui->deviceTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одной строки в таблице
    ui->deviceTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    // Устанавливаем размер колонок по содержимому
    ui->deviceTableView->resizeColumnsToContents();
    ui->deviceTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->deviceTableView->horizontalHeader()->setStretchLastSection(true);

    //      connect(ui->deviceTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotEditRecord(QModelIndex)));
    ui->deviceTableView->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->deviceTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotEditRecord()));
    // Подключаем СЛОТ вызова контекстного меню
    connect(ui->deviceTableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));

    QSettings info("pers_info.conf", QSettings::IniFormat);
    info.beginGroup("Info");
    double Kkal=info.value("Kkal", -1).toDouble();
    double Prot=info.value("Prot", -1).toDouble();
    double Fats=info.value("Fats", -1).toDouble();
    double Carb=info.value("Carb", -1).toDouble();
    info.endGroup();
    ui->label->setText("Дневная норма \n Ккал:" + QString::number(Kkal) + " \n Белок: "+ QString::number(Prot) + " \n Жиры: "
                       + QString::number(Fats) + " \n Углеводы: " + QString::number(Carb));
}

/* Метод для активации диалога добавления записей
 * */
void Rations::on_addDeviceButton_clicked()
{
    /* Создаем диалог и подключаем его сигнал завершения работы
     * к слоту обновления вида модели представления данных
     * */
    dialogadddevice *addDeviceDialog = new dialogadddevice();
    connect(addDeviceDialog, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));

    /* Выполняем запуск диалогового окна
     * */
    addDeviceDialog->setWindowTitle(("Добавить блюдо"));
    addDeviceDialog->exec();
}

/* Слот обновления модели представления данных
 * */
void Rations::slotUpdateModels()
{
    modelDevice->select();
    ui->deviceTableView->resizeColumnsToContents();
}

void Rations::slotCustomMenuRequested(QPoint pos)
{
    /* Создаем объект контекстного меню */
    QMenu * menu = new QMenu(this);
    /* Создаём действия для контекстного меню */
    QAction * editDevice = new QAction(("Редактировать"), this);
    QAction * deleteDevice = new QAction(("Удалить"), this);
    /* Подключаем СЛОТы обработчики для действий контекстного меню */
    connect(editDevice, SIGNAL(triggered()), this, SLOT(slotEditRecord()));     // Обработчик вызова диалога редактирования
    connect(deleteDevice, SIGNAL(triggered()), this, SLOT(slotRemoveRecord())); // Обработчик удаления записи
    /* Устанавливаем действия в меню */
    menu->addAction(editDevice);
    menu->addAction(deleteDevice);
    /* Вызываем контекстное меню */
    menu->popup(ui->deviceTableView->viewport()->mapToGlobal(pos));
}

/* Слот для удаления записи из таблицы
 * */
void Rations::slotRemoveRecord()
{
    /* Выясняем, какая из строк была выбрана
     * */
    int row = ui->deviceTableView->selectionModel()->currentIndex().row();
    /* Проверяем, что строка была действительно выбрана
     * */
    if(row >= 0){
        /* Задаём вопрос, стоит ли действительно удалять запись.
         * При положительном ответе удаляем запись
         * */
        if (QMessageBox::warning(this,
                                 ("Удаление записи"),
                                 ("Вы уверены, что хотите удалить эту запись?"),
                                 QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
        {
            /* При отрицательном ответе делаем откат действий
             * и закрываем диалог без удаления записи
             * */
            QSqlDatabase::database().rollback();
            return;
        } else {
            /* В противном случае производим удаление записи.
             * При успешном удалении обновляем таблицу.
             * */
            if(!modelDevice->removeRow(row)){
                QMessageBox::warning(this,("Уведомление"),
                                     ("Не удалось удалить запись\n"
                                      "Возможно она используется другими таблицами\n"
                                      "Проверьте все зависимости и повторите попытку"));
            }
            modelDevice->select();
            ui->deviceTableView->setCurrentIndex(modelDevice->index(-1, -1));
        }
    }
}

/* Метод для активации диалога добавления записей в режиме редактирования
 * с передачей индекса выбранной строки
 * */
void Rations::slotEditRecord()
{
    /* Также создаем диалог и подключаем его сигнал завершения работы
     * к слоту обновления вида модели представления данных, но передаём
     * в качестве параметров строку записи
     * */
    dialogadddevice *addDeviceDialog = new dialogadddevice(ui->deviceTableView->selectionModel()->currentIndex().row());
    connect(addDeviceDialog, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));

    // Выполняем запуск диалогового окна

    addDeviceDialog->setWindowTitle(("Редактировать блюдо"));
    addDeviceDialog->exec();
}

void Rations::on_Back_button_clicked()
{
    db->closeDataBase();
    QWidget::close();

}
