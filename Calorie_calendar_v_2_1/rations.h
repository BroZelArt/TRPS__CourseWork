#ifndef RATIONS_H
#define RATIONS_H

#include <QDialog>
#include <QSqlTableModel>
#include "database.h"
#include "dialogadddevice.h"
#include "info_pers.h"
#include <QSettings>

namespace Ui {
class Rations;
}

class Rations : public QDialog
{
    Q_OBJECT

public:
    explicit Rations(QWidget *parent = nullptr);
    ~Rations();

private slots:
    void on_addDeviceButton_clicked();
    void slotUpdateModels();
    //  void slotEditRecord(QModelIndex index);


    void slotEditRecord();
    void slotRemoveRecord();
    void slotCustomMenuRequested(QPoint pos);
    //   void slotRemoveRecord();
    //   void slotCustomMenuRequested(QPoint pos);

    void on_Back_button_clicked();

private:
    Ui::Rations *ui;
    DataBase *db;
    QSqlTableModel *modelDevice;

private:
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();
};

#endif // RATIONS_H
