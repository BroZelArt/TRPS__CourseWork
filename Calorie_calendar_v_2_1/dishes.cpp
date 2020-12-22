#include "dishes.h"
#include "ui_dishes.h"

dishes::dishes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dishes)
{
    ui->setupUi(this);
}

dishes::~dishes()
{
    delete ui;
}
