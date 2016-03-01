#-------------------------------------------------
#
# Project created by QtCreator 2015-09-16T10:05:21
#
#-------------------------------------------------

QT       += core gui
QT       += network serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=gnu++11

TARGET = service-robot
TEMPLATE = app
#包含win32的库
#LIBS += -lws2_32
linux
{
LIBS    += -L/usr/local/lib/ -lavcodec -lavformat -lavdevice -lavfilter -lavutil -lpostproc -lswresample -lswscale
LIBS    += -L/usr/local/lib/ -lSDL -lx264

LIBS    += -L/opt/ffmpeg-arm/lib/ -lavcodec -lavformat -lavdevice -lavfilter -lavutil -lpostproc -lswresample -lswscale
LIBS    += -L/opt/x264-arm/lib -lx264
LIBS    += -L/opt/SDL-arm/lib/ -lSDL

INCLUDEPATH +=/usr/local/include
}

SOURCES += main.cpp\
        mainwindow.cpp \
    keyboard/keyboard.cpp \
    net/usb_wifi.cpp \
    videoplayer/videoplayer.cpp \
    serialport/serialport.cpp \
    net/ipinfotable.cpp \
    SSDB/ssdb_client.cpp \
    SSDB/buffer.c \
    global.cpp \
    net/downloader.cpp \
    net/netspeed.cpp \
    keyinput.cpp \
    SSDB/ssdb_client_.cpp \
    screenemotion/screenemotion.cpp

HEADERS  += mainwindow.h \
    keyboard/keyboard.h \
    net/usb_wifi.h \
    videoplayer/video.h \
    videoplayer/videoplayer.h \
    serialport/serialport.h \
    global.h \
    net/ipinfotable.h \
    SSDB/buffer.h \
    SSDB/ssdb_client.h \
    net/downloader.h \
    net/netspeed.h \
    keyinput.h \
    SSDB/ssdb_client_.h \
    screenemotion/screenemotion.h

FORMS    += mainwindow.ui \
    keyboard/keyboard.ui

RESOURCES += \
    res.qrc