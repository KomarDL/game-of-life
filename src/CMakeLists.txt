cmake_minimum_required(VERSION 3.5)

project(${PROJECT_NAME} LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
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

file(GLOB H_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB UI_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)

set(SOURCES ${CPP_FILES} ${H_FILES} ${UI_FILES})


if(ANDROID)
  add_library(game-of-life SHARED
    ${SOURCES}
  )
else()
  add_executable(game-of-life
    ${SOURCES}
  )
endif()

target_link_libraries(game-of-life PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
