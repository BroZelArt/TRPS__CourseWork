#include "dialogaddreport.h"
#include "ui_dialogaddreport.h"

dialogaddreport::dialogaddreport(int row,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogaddreport)
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

dialogaddreport::~dialogaddreport()
{
    delete ui;
}

/* Метод настройки модели данных и mapper
 * */
void dialogaddreport::setupModel()
{
    /* Инициализируем модель и делаем выборку из неё
     * */
    model = new QSqlTableModel(this);
    model->setTable(REPORTS);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    /* Инициализируем mapper и привязываем
     * поля данных к объектам LineEdit
     * */
    mapper = new QDataWidgetMapper();
    mapper->setModel(model);
    mapper->addMapping(ui->dateEdit, 1);
    mapper->addMapping(ui->rep_mass, 2);
    mapper->addMapping(ui->rep_chest, 3);
    mapper->addMapping(ui->rep_waist, 4);
    mapper->addMapping(ui->rep_hips, 5);
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

/* Метод для установки валидатора на поле ввода IP и MAC адресов
 * */
void dialogaddreport::createUI()
{
    QString intRange = "(?:[0-9]?[0-9]?[0-9])";
    QRegExp intRegex ("^" + intRange + "$");
    QRegExpValidator *intValidator = new QRegExpValidator(intRegex, this);
    ui->rep_waist->setValidator(intValidator);
    ui->rep_chest->setValidator(intValidator);
    ui->rep_hips->setValidator(intValidator);
    ui->rep_mass->setValidator(intValidator);

    QString realRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegExp realRegex ("^" + realRange
                       + "\\." + realRange + "$");
    QRegExpValidator *realValidator = new QRegExpValidator(realRegex, this);
    ui->rep_mass->setValidator(realValidator);

}

void dialogaddreport::on_buttonBox_accepted()
{

    mapper->submit();
    model->submitAll();
    emit signalReady();
    this->close();
   }

void dialogaddreport::accept()
{
    //   this->close();

}

/* Метод изменения состояния активности кнопок пролистывания
 * */
void dialogaddreport::updateButtons(int row)
{
    /* В том случае, если мы достигаем одного из крайних (самый первый или
     * самый последний) из индексов в таблице данных,
     * то мы изменяем состояние соответствующей кнопки на
     * состояние неактивна
     * */
    ui->previousButton->setEnabled(row > 0);
    ui->nextButton->setEnabled(row < model->rowCount() - 1);
}

void dialogaddreport::on_buttonBox_rejected()
{
    this->close();

}
