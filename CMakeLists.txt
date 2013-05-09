cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

PROJECT(loadQMpris)

FIND_PACKAGE(Qt4 REQUIRED)

SET(QT_USE_QTDBUS TRUE)

SET(loadQMpris_SOURCES main.cpp mainwindow.cpp)
SET(loadQMpris_HEADERS mainwindow.h)
SET(loadQMpris_FORMS mainwindow.ui)

QT4_WRAP_CPP(loadQMpris_HEADERS_MOC ${loadQMpris_HEADERS})
QT4_WRAP_UI(loadQMpris_FORMS_HEADERS ${loadQMpris_FORMS})

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

ADD_EXECUTABLE(loadQMpris ${loadQMpris_SOURCES} 
    ${loadQMpris_HEADERS_MOC}
    ${loadQMpris_FORMS_HEADERS} )
TARGET_LINK_LIBRARIES(loadQMpris ${QT_LIBRARIES})
TARGET_LINK_LIBRARIES(loadQMpris ${CMAKE_CURRENT_LIST_DIR}/libMpris/libQMpris.so)
target_link_libraries(loadQMpris ${QT_QTDBUS_LIBRARY})
