#-------------------------------------------------
#
# Project created by QtCreator 2019-03-29T09:11:29
#
#-------------------------------------------------

QT       += core gui concurrent multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = Virus2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS LOG4QT_VERSION_MAJOR=1 LOG4QT_VERSION_MINOR=5 LOG4QT_VERSION_PATCH=1 LOG4QT_VERSION_STR=\"1.5.1\"

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    virusscreen.cpp \
    cell.cpp \
    startscreen.cpp \
    helpscreen.cpp

HEADERS += \
    mainwindow.h \
    virusscreen.h \
    cell.h \
    startscreen.h \
    helpscreen.h

#FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    font.qrc \
    icon.qrc \
    sounds.qrc

unix|win32: LIBS += -llog4qt
