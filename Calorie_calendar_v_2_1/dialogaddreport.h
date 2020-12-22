#ifndef DIALOGADDREPORT_H
#define DIALOGADDREPORT_H

#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QMessageBox>
#include <QCalendarWidget>

#include <database.h>

namespace Ui {
class dialogaddreport;
}

class dialogaddreport : public QDialog
{
    Q_OBJECT

public:
    explicit dialogaddreport(int row= -1, QWidget *parent = nullptr);
    ~dialogaddreport();

signals:
    void signalReady();

private slots:
    void on_buttonBox_accepted();
    void updateButtons(int row);

    void on_buttonBox_rejected();

private:
    Ui::dialogaddreport         *ui;
    QSqlTableModel              *model;
    QDataWidgetMapper           *mapper;

private:
    void setupModel();
    void createUI();
    void accept();
 //   bool OK;
};

#endif // DIALOGADDREPORT_H
