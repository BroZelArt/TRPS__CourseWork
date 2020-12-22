#ifndef REPORTS_H
#define REPORTS_H

#include <QDialog>
#include <QSqlTableModel>
#include "database.h"
#include "dialogaddreport.h"
#include <QDate>

namespace Ui {
class reports;
}

class reports : public QDialog
{
    Q_OBJECT

public:
    explicit reports(QWidget *parent = nullptr);
    ~reports();

private slots:
    void on_addReportButton_clicked();
    void slotUpdateModels();
    //  void slotEditRecord(QModelIndex index);


    void slotEditRecord();
    void slotRemoveRecord();
    void slotCustomMenuRequested(QPoint pos);
    //   void slotRemoveRecord();
    //   void slotCustomMenuRequested(QPoint pos);

    void on_Back_button_clicked();

private:
    Ui::reports *ui;
    DataBase *dbr;
    QSqlTableModel *modelRep;

private:
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();
};


#endif // REPORTS_H
