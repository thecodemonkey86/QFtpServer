#-------------------------------------------------
#
# Project created by QtCreator 2016-12-11T11:12:29
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = QFtpServerLib
TEMPLATE = lib

DEFINES += QFTPSERVERLIB_LIBRARY

SOURCES += \
    dataconnection.cpp \
    ftpcommand.cpp \
    ftpconfig.cpp \
    ftpcontrolconnection.cpp \
    ftplistcommand.cpp \
    ftpretrcommand.cpp \
    ftpserver.cpp \
    ftpstorcommand.cpp \
    sslcertdata.cpp \
    sslserver.cpp

HEADERS +=\
    ftpconfig.h \
        qftpserverlib_global.h \
    dataconnection.h \
    ftpcommand.h \
    ftpcontrolconnection.h \
    ftplistcommand.h \
    ftpretrcommand.h \
    ftpserver.h \
    ftpstorcommand.h \
    sslcertdata.h \
    sslserver.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    certificates.qrc
