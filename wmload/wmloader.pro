######################################################################
# Automatically generated by qmake (2.01a) ?? ???. 21 15:11:29 2013
######################################################################

TEMPLATE = app
TARGET = wmloader
DEPENDPATH += .
INCLUDEPATH += .

CONFIG += debug

QT -= gui
QT += xml sql

LIBS += -lpq

# Input
HEADERS += DbFiller.h XmlObject.h XmlReader.h
SOURCES += main.cpp \
    XmlReader.cpp \
    XmlObject.cpp \
    DbFiller.cpp
