QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

RC_ICONS=D:/OneDrive/studia/BD/bd/logo.ico
RESOURCES=zasoby.qrc
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dodawanie_biletow.cpp \
    main.cpp \
    mainwindow.cpp \
    okno_barman.cpp \
    okno_kasjer.cpp \
    okno_kierownik.cpp \
    okno_logowania.cpp \
    okno_manager.cpp \
    okno_technik.cpp

HEADERS += \
    dodawanie_biletow.h \
    mainwindow.h \
    okno_barman.h \
    okno_kasjer.h \
    okno_kierownik.h \
    okno_logowania.h \
    okno_manager.h \
    okno_technik.h

FORMS += \
    dodawanie_biletow.ui \
    mainwindow.ui \
    okno_barman.ui \
    okno_kasjer.ui \
    okno_kierownik.ui \
    okno_logowania.ui \
    okno_manager.ui \
    okno_technik.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    bd.pro.user

RESOURCES += \
    zasoby.qrc
