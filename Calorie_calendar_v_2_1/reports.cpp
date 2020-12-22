#include "reports.h"
#include "ui_reports.h"

#include <QListWidget>
#include <QMenuBar>

#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDate>
#include <QSettings>


reports::reports(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reports)
{
    ui->setupUi(this);
    dbr = new DataBase();
    dbr->connectToDataBaseRep();

    /* Инициализируем модель для представления данных
     * с заданием названий колонок
     * */
    this->setupModel(REPORTS, QStringList()<< "id"  << "Дата" <<"Масса"  << "Обхват груди" << "Обхват талии" << "Обхват бёдер");

    /* Инициализируем внешний вид таблицы с данными
     * */
    this->createUI();

}

reports::~reports()
{
    delete ui;
}
/* Метод для инициализации модеи представления данных
 * */
void reports::setupModel(const QString &tableName, const QStringList &headers)
{
    /* Производим инициализацию модели представления данных
         * */
    modelRep = new QSqlTableModel(this);
    modelRep->setTable(tableName);
    modelRep->select();
    /* Устанавливаем названия колонок в таблице с сортировкой данных
         * */
    for(int i = 0, j = 0; i < modelRep->columnCount(); i++, j++){
        modelRep->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
}

void reports::createUI()
{
    ui->reportTableView->setModel(modelRep);     // Устанавливаем модель на TableView
    ui->reportTableView->setColumnHidden(0, true);    // Скрываем колонку с id записей
    // Разрешаем выделение строк
    ui->reportTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    ui->reportTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    // Устанавливаем размер колонок по содержимому
    ui->reportTableView->resizeColumnsToContents();
    ui->reportTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->reportTableView->horizontalHeader()->setStretchLastSection(true);

    //      connect(ui->deviceTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotEditRecord(QModelIndex)));
    ui->reportTableView->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->reportTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotEditRecord()));
    // Подключаем СЛОТ вызова контекстного меню
    connect(ui->reportTableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));
}

/* Метод для активации диалога добавления записей
 * */
void reports::on_addReportButton_clicked()
{
    /* Создаем диалог и подключаем его сигнал завершения работы
     * к слоту обновления вида модели представления данных
     * */
    dialogaddreport *addDeviceDialog = new dialogaddreport();
    connect(addDeviceDialog, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));

    /* Выполняем запуск диалогового окна
     * */
    addDeviceDialog->setWindowTitle(("Добавить отчёт"));
    addDeviceDialog->exec();
}

/* Слот обновления модели представления данных
 * */
void reports::slotUpdateModels()
{
    modelRep->select();
    ui->reportTableView->resizeColumnsToContents();
}

void reports::slotCustomMenuRequested(QPoint pos)
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
    menu->popup(ui->reportTableView->viewport()->mapToGlobal(pos));
}

/* Слот для удаления записи из таблицы
 * */
void reports::slotRemoveRecord()
{
    /* Выясняем, какая из строк была выбрана
     * */
    int row = ui->reportTableView->selectionModel()->currentIndex().row();
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
            if(!modelRep->removeRow(row)){
                QMessageBox::warning(this,("Уведомление"),
                                     ("Не удалось удалить запись\n"
                                      "Возможно она используется другими таблицами\n"
                                      "Проверьте все зависимости и повторите попытку"));
            }
            modelRep->select();
            ui->reportTableView->setCurrentIndex(modelRep->index(-1, -1));
        }
    }
}

/* Метод для активации диалога добавления записей в режиме редактирования
 * с передачей индекса выбранной строки
 * */
void reports::slotEditRecord()
{
    /* Также создаем диалог и подключаем его сигнал завершения работы
     * к слоту обновления вида модели представления данных, но передаём
     * в качестве параметров строку записи
     * */
    dialogaddreport *addReportDialog = new dialogaddreport(ui->reportTableView->selectionModel()->currentIndex().row());
    connect(addReportDialog, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));

    /* Выполняем запуск диалогового окна
        * */
    addReportDialog->setWindowTitle(("Редактировать отчёт"));
    addReportDialog->exec();
}

void reports::on_Back_button_clicked()
{
    dbr->closeDataBaseRep();
    QWidget::close();

}
