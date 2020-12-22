#ifndef DIALOGADDDEVICE_H
#define DIALOGADDDEVICE_H

#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QMessageBox>

#include <database.h>

namespace Ui {
class dialogadddevice;
}

class dialogadddevice : public QDialog
{
    Q_OBJECT

public:
    explicit dialogadddevice(int row= -1, QWidget *parent = nullptr);
    ~dialogadddevice();

signals:
    void signalReady();

private slots:
    void on_buttonBox_accepted();
    void updateButtons(int row);

    void on_buttonBox_rejected();

private:
    Ui::dialogadddevice         *ui;
    QSqlTableModel              *model;
    QDataWidgetMapper           *mapper;

private:
    void setupModel();
    void createUI();
    void accept();
};

#endif // DIALOGADDDEVICE_H
