######################################################################
# Automatically generated by qmake (2.01a) ?? ???. 21 15:11:29 2013
######################################################################

TEMPLATE = app
TARGET = wmloader
DEPENDPATH += .
INCLUDEPATH += .

OBJECTS_DIR = .obj
MOC_DIR = .moc

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
