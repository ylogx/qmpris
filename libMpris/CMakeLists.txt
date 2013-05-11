cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

MACRO(MACRO_ENSURE_OUT_OF_SOURCE_BUILD)
    STRING(COMPARE EQUAL "${${PROJECT_NAME}_SOURCE_DIR}"
"${${PROJECT_NAME}_BINARY_DIR}" insource)
    GET_FILENAME_COMPONENT(PARENTDIR ${${PROJECT_NAME}_SOURCE_DIR} PATH)
    STRING(COMPARE EQUAL "${${PROJECT_NAME}_SOURCE_DIR}"
"${PARENTDIR}" insourcesubdir)
    IF(insource OR insourcesubdir)
        MESSAGE(FATAL_ERROR "${PROJECT_NAME} requires an out of source build.")
    ENDIF(insource OR insourcesubdir)
ENDMACRO(MACRO_ENSURE_OUT_OF_SOURCE_BUILD)

PROJECT(qmpris)

SET(BUILD_SHARED_LIBS ON)

FIND_PACKAGE(Qt4 REQUIRED)
SET(QT_USE_QTDBUS TRUE)

SET(qmpris_SOURCES QMpris.cpp)
SET(qmpris_HEADERS QMpris.h )# MediaPlayer2Player.h)
#SET(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/../../build)
#macro_ensure_out_of_source_build("Sound Menu Library requires an out of source build. Please create a separate build directory and run 'cmake path_to_src [options]' there.")
#MACRO_ENSURE_OUT_OF_SOURCE_BUILD()

INCLUDE_DIRECTORIES( ${CMAKE_BINARY_DIR} )
QT4_WRAP_CPP(qmpris_HEADERS_MOC ${qmpris_HEADERS})

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})
#ADD_EXECUTABLE(qmpris ${qmpris_SOURCES}
#    ${qmpris_HEADERS_MOC}
#)
ADD_LIBRARY(qmpris ${qmpris_SOURCES}
    ${qmpris_HEADERS_MOC}
)
TARGET_LINK_LIBRARIES(qmpris ${QT_LIBRARIES})

#target_link_libraries(loadQMpris ${CMAKE_CURRENT_BINARY_DIR}/libMpris/libqmpris.so)#libQMpris)
