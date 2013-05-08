TEMPLATE = lib
# Input

LIBS += -lQtDBus
SOURCES += QMpris.cpp
HEADERS+= QMpris.h
DEFINES += QMPRIS

QT += dbus
