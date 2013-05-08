TEMPLATE = app
TARGET =
DEPENDPATH += . ../QMprisLib
INCLUDEPATH +=  ../QMprisLib
#LIBS+=  -L../QMpris/QMprisLib/debug # -lQMprisLib
# Input
SOURCES += main.cpp

LIBS += -lQtDBus
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/QMpris-build-desktop-Qt_4_8_1_in_PATH__System__Release/release/ -lQMpris -lQtDBus
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/QMpris-build-desktop-Qt_4_8_1_in_PATH__System__Release/debug/ -lQMpris -lQtDBus
else:symbian: LIBS += -lQMpris -lQtDBus
else:unix: LIBS += -L$$PWD/QMpris-build-desktop-Qt_4_8_1_in_PATH__System__Release/ -lQMpris -lQtDBus

INCLUDEPATH += $$PWD/QMpris-build-desktop-Qt_4_8_1_in_PATH__System__Release
DEPENDPATH += $$PWD/QMpris-build-desktop-Qt_4_8_1_in_PATH__System__Release

QT += dbus
