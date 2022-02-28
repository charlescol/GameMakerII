#-------------------------------------------------
#
# Project created by QtCreator 2016-05-25T16:50:23
#
#-------------------------------------------------
QT += widgets
QT       += core gui
CONFIG += c++11
QT       += sql # On rajoute SQL

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameMakerII
TEMPLATE = app


SOURCES += main.cpp\
        EngineClass\Display\mainwindow.cpp \
    EngineClass/Display/grid.cpp \
    EngineClass/Display/tilescene.cpp \
    EngineClass/Display/tilebackgroundpicture.cpp \
    EngineClass/Display/renderscene.cpp \
    EngineClass/Display/movableselection.cpp \
    EngineClass/Display/generationselection.cpp \
    EngineClass/Map/tileentity.cpp \
    EngineClass/Map/mapdisplay.cpp \
    EngineClass/Display/eraser.cpp \
    EngineClass/ScriptEditor/codeeditor.cpp \
    EngineClass/ScriptEditor/filescripttreeview.cpp \
    EngineClass/ScriptEditor/scripthighlighter.cpp \
    EngineClass/ScriptEditor/widgetscripteditor.cpp \
    EngineClass/Map/mapcolisions.cpp \
    EngineClass/Data/daomap.cpp \
    EngineClass/Data/databasehandler.cpp

HEADERS  += EngineClass\Display\mainwindow.h \
    EngineClass/Display/screenResolution.h \
    EngineClass/Display/grid.h \
    EngineClass/Display/tilescene.h \
    EngineClass/Display/tilebackgroundpicture.h \
    EngineClass/Display/renderscene.h \
    EngineClass/Display/movableselection.h \
    EngineClass/Display/generationselection.h \
    EngineClass/Map/tileentity.h \
    EngineClass/Map/mapdisplay.h \
    EngineClass/Display/eraser.h \
    EngineClass/ScriptEditor/codeeditor.h \
    EngineClass/ScriptEditor/filescripttreeview.h \
    EngineClass/ScriptEditor/scripthighlighter.h \
    EngineClass/ScriptEditor/widgetscripteditor.h \
    EngineClass/Map/mapcolisions.h \
    EngineClass/Data/daomap.h \
    EngineClass/Data/databasehandler.h

FORMS    += mainwindow.ui

RESOURCES += \
    MainWindow.qrc
