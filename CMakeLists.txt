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

PROJECT(loadQMpris)
FIND_PACKAGE(Qt4 REQUIRED)

SET(QT_USE_QTDBUS TRUE)

#SET(CMAKE_OUTPUT_DIR ../build)
SET(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/../build)

#MACRO_ENSURE_OUT_OF_SOURCE_BUILD()
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
#TARGET_LINK_LIBRARIES(loadQMpris ${CMAKE_CURRENT_LIST_DIR}/libMpris/libQMpris.so)
target_link_libraries(loadQMpris ${QT_QTDBUS_LIBRARY})

#add my library
include_directories("${CMAKE_CURRENT_LIST_DIR}/libMpris")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/libMpris")
link_directories("${CMAKE_CURRENT_LIST_DIR}/libMpris")
#add_executable(libQMpris ${CMAKE_CURRENT_LIST_DIR}/libMpris/QMpris.cpp)
#add_library(libQMpris SHARED ${CMAKE_CURRENT_LIST_DIR}/libMpris/QMpris.cpp)
#target_link_libraries(loadQMpris ${CMAKE_CURRENT_LIST_DIR}/libMpris)#libQMpris)

#SET_TARGET_PROPERTIES(libQMpris PROPERTIES ENABLE_EXPORTS TRUE)
#target_link_libraries(loadQMpris libQMpris)

#target_link_libraries(loadQMpris ${CMAKE_CURRENT_BINARY_DIR}/liblibQMpris.so)#libQMpris)
#target_link_libraries(loadQMpris ${CMAKE_CURRENT_BINARY_DIR}/libMpris/libqmpris.so)#libQMpris)
target_link_libraries(loadQMpris qmpris)#libQMpris)
