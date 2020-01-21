#-------------------------------------------------
#
# Project created by QtCreator 2019-11-10T11:59:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = scapes
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        AddStmt.cc \
        CmpStmt.cc \
        DeclArrStmt.cc \
        DeclIntStmt.cc \
        EndStmt.cc \
        Factory.cc \
        Identifier.cc \
        JEqStmt.cc \
        JLessStmt.cc \
        JMoreStmt.cc \
        JmpStmt.cc \
        Label.cc \
        MovStmt.cc \
        Operand.cc \
        PrintStmt.cc \
        Program.cc \
        ReadStmt.cc \
        Statement.cc \
        SyntaxException.cc \
        Variable.cc \
        codeeditor.cpp \
        compilecontrol.cpp \
        inputmanager.cpp \
        main.cpp \
        interface.cpp \
        newfilecontrol.cpp \
        openfilecontrol.cpp \
        runcontrol.cpp \
        savefileascontrol.cpp \
        savefilecontrol.cpp \
        terminal.cpp

HEADERS += \
        AddStmt.h \
        CmpStmt.h \
        DeclArrStmt.h \
        DeclIntStmt.h \
        EndStmt.h \
        Factory.h \
        Identifier.h \
        JEqStmt.h \
        JLessStmt.h \
        JMoreStmt.h \
        JmpStmt.h \
        Label.h \
        MovStmt.h \
        Operand.h \
        PrintStmt.h \
        Program.h \
        ReadStmt.h \
        Statement.h \
        SyntaxException.h \
        Variable.h \
        codeeditor.h \
        compilecontrol.h \
        inputmanager.h \
        interface.h \
        newfilecontrol.h \
        openfilecontrol.h \
        runcontrol.h \
        savefileascontrol.h \
        savefilecontrol.h \
        terminal.h

FORMS += \
        interface.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
