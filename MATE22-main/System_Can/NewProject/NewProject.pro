QT       += core gui serialport
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Serial_RGB_Qt
TEMPLATE = app


CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Control.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Control.h \
    mainwindow.h

FORMS += \
    mainwindow.ui


INCLUDEPATH += C:\Qt\Qt5.12.11\SFML\include
INCLUDEPATH += C:\Users\pc\Desktop\MATE22-main2\System_Can\NewProject
DEPENDPATH += C:\Qt\Qt5.12.11\SFML\include

LIBS += -LC:\Qt\Qt5.12.11\SFML\lib
LIBS += -LC:\Qt\Qt5.12.11\SFML\bin

CONFIG(debug, debug|release): LIBS+= -lsfml-audio-d  -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

CONFIG(release, debug|release): LIBS+= -lsfml-audio  -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
