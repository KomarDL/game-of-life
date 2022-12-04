cmake_minimum_required(VERSION 3.5)

project(${PROJECT_NAME} LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
# creating output directory architecture in accordance with GNU guidelines
set(BINARY_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BINARY_DIR}/lib")


find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(H_FILES ${CMAKE_CURRENT_SOURCE_DIR}/cell.h
            ${CMAKE_CURRENT_SOURCE_DIR}/gamefield.h
            ${CMAKE_CURRENT_SOURCE_DIR}/gamelogic.h
            ${CMAKE_CURRENT_SOURCE_DIR}/global.h
            ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.h
            ${CMAKE_CURRENT_SOURCE_DIR}/neighborfinder.h)

set(CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/cell.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/gamefield.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/gamelogic.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/neighborfinder.cpp)

set(UI_FILES ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.ui)

set(SOURCES ${CPP_FILES} ${H_FILES} ${UI_FILES})


if(ANDROID)
  add_library(${PROJECT_NAME} SHARED
    ${SOURCES}
  )
else()
  add_executable(${PROJECT_NAME}
    ${SOURCES}
  )
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set_property(TARGET ${PROJECT_NAME}  PROPERTY WIN32_EXECUTABLE true)
endif()


target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
