#include "dialogadddevice.h"
#include "ui_dialogadddevice.h"
#include <QRegExpValidator>
dialogadddevice::dialogadddevice(int row, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogadddevice)
{
    ui->setupUi(this);
    /* Метода для инициализации модели,
         * из которой будут транслироваться данные
         * */
    setupModel();
    QDate date = QDate::currentDate();
    ui->dateEdit->setDate(date);
    /* Если строка не задана, то есть равна -1,
         * тогда диалог работает по принципу создания новой записи.
         * А именно, в модель вставляется новая строка и работа ведётся с ней.
         * */
    if(row == -1){
        model->insertRow(model->rowCount(QModelIndex()));
        mapper->toLast();
        /* В противном случае диалог настраивается на заданную запись
         * */
    } else {
        mapper->setCurrentModelIndex(model->index(row,0));
    }

    createUI();
}

dialogadddevice::~dialogadddevice()
{
    delete ui;
}

/* Метод настройки модели данных и mapper
 * */
void dialogadddevice::setupModel()
{
    /* Инициализируем модель и делаем выборку из неё
     * */
    model = new QSqlTableModel(this);
    model->setTable(RATIONS);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    /* Инициализируем mapper и привязываем
     * поля данных к объектам LineEdit
     * */
    //QDate intdate = ui->dateEdit->date("dd:MM:YYYY");
    mapper = new QDataWidgetMapper();
    mapper->setModel(model);
    mapper->addMapping(ui->dateEdit, 1);
    mapper->addMapping(ui->rat_name, 2);
    mapper->addMapping(ui->rat_mass, 3);
    mapper->addMapping(ui->rat_ccal, 4);
    mapper->addMapping(ui->rat_prot, 5);
    mapper->addMapping(ui->rat_fats, 6);
    mapper->addMapping(ui->rat_carb, 7);
    /* Ручное подтверждение изменения данных
     * через mapper
     * */
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    /* Подключаем коннекты от кнопок пролистывания
     * к прилистыванию модели данных в mapper
     * */
    connect(ui->previousButton, SIGNAL(clicked()), mapper, SLOT(toPrevious()));
    connect(ui->nextButton, SIGNAL(clicked()), mapper, SLOT(toNext()));
    /* При изменении индекса в mapper изменяем состояние кнопок
     * */
    connect(mapper, SIGNAL(currentIndexChanged(int)), this, SLOT(updateButtons(int)));
}

/* Метод для установки валидатора на поля
 * */
void dialogadddevice::createUI()
{
    QString intRange = "(?:[0-9]?[0-9]?[0-9]?[0-9]?[0-9])";
    QRegExp intRegex ("^" + intRange + "$");
    QRegExpValidator *intValidator = new QRegExpValidator(intRegex, this);

    QString realRange = "(?:[0-9]?[0-9]?[0-9]?[0-9]?[0-9]|[0-9][0-9])";
    QRegExp realRegex ("^" + realRange
                       + "\\." + realRange + "$");
    QRegExpValidator *realValidator = new QRegExpValidator(realRegex, this);
    ui->rat_ccal->setValidator(realValidator);
    ui->rat_carb->setValidator(realValidator);
    ui->rat_fats->setValidator(realValidator);
    ui->rat_prot->setValidator(realValidator);
    ui->rat_mass->setValidator(realValidator);

}

void dialogadddevice::on_buttonBox_accepted()
{

    mapper->submit();
    model->submitAll();
    emit signalReady();
    this->close();

}

void dialogadddevice::accept()
{


}

/* Метод изменения состояния активности кнопок пролистывания
 * */
void dialogadddevice::updateButtons(int row)
{
    /* В том случае, если мы достигаем одного из крайних (самый первый или
     * самый последний) из индексов в таблице данных,
     * то мы изменяем состояние соответствующей кнопки на
     * состояние неактивна
     * */
    ui->previousButton->setEnabled(row > 0);
    ui->nextButton->setEnabled(row < model->rowCount() - 1);
}

void dialogadddevice::on_buttonBox_rejected()
{
    this->close();

}
