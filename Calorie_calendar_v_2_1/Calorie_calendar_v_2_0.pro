QT       += core gui sql printsupport


#include <Qtsql>
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CalorieCalendar
TEMPLATE = app
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database.cpp \
    dialogadddevice.cpp \
    dialogaddreport.cpp \
    info_pers.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    rations.cpp \
    reports.cpp \
    statistics.cpp

HEADERS += \
    database.h \
    dialogadddevice.h \
    dialogaddreport.h \
    info_pers.h \
    mainwindow.h \
    qcustomplot.h \
    rations.h \
    reports.h \
    statistics.h

FORMS += \
    dialogadddevice.ui \
    dialogaddreport.ui \
    info_pers.ui \
    mainwindow.ui \
    rations.ui \
    reports.ui \
    statistics.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc
