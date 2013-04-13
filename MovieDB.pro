#-------------------------------------------------
#
# Project created by QtCreator 2013-03-08T19:25:36
#
#-------------------------------------------------

QT       += core gui\
            xml\
            network\
            sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MovieDB
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        movie.cpp \
    moviefile.cpp \
    qlistdialog.cpp \
    database.cpp \
    querytmdb.cpp \
    moviedisplayinfo.cpp

HEADERS  += mainwindow.h \
            movie.h \
    moviefile.h \
    querytmdb.h \
    qlistdialog.h \
    querytmdb.h \
    database.h \
    moviedisplayinfo.h

FORMS    += \
    moviedisplayinfo.ui
