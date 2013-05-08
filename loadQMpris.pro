TEMPLATE = app
TARGET =
DEPENDPATH += . ../QMprisLib
INCLUDEPATH +=  ../QMprisLib
#LIBS+=  -L../QMpris/QMprisLib/debug # -lQMprisLib
# Input
SOURCES += main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../QMpris-build-desktop-Qt_4_8_1_in_PATH__System__Release/release/ -lQMpris
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../QMpris-build-desktop-Qt_4_8_1_in_PATH__System__Release/debug/ -lQMpris
else:symbian: LIBS += -lQMpris
else:unix: LIBS += -L$$PWD/../QMpris-build-desktop-Qt_4_8_1_in_PATH__System__Release/ -lQMpris

INCLUDEPATH += $$PWD/../QMpris-build-desktop-Qt_4_8_1_in_PATH__System__Release
DEPENDPATH += $$PWD/../QMpris-build-desktop-Qt_4_8_1_in_PATH__System__Release
