#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "info_pers.h"
#include "new_ration.h"
#include "reports.h"
#include "rations.h"
#include "statistics.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_to_pers_info_clicked()
{
    info_pers info_pers_window;
    info_pers_window.setModal(true);
    info_pers_window.exec();
}



void MainWindow::on_to_reports_clicked()
{
    reports reports_window;
    reports_window.setModal(true);
    reports_window.exec();
}


void MainWindow::on_pushButton_clicked()
{
    Rations rations_window;
    rations_window.setModal(true);
    rations_window.exec();
}

void MainWindow::on_to_statistics_clicked()
{
    Statistics statistics_window;
    statistics_window.setModal(true);
    statistics_window.exec();
}
