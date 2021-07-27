cmake_minimum_required(VERSION 3.5)

project(${PROJECT_NAME} LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
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


find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)

file(GLOB H_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB QRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)

set(SOURCES ${CPP_FILES} ${H_FILES} ${QRC_FILES})


if(ANDROID)
  add_library(game-of-life SHARED
    ${SOURCES}
  )
else()
  add_executable(game-of-life
    ${SOURCES}
  )
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set_property(TARGET ${PROJECT_NAME}  PROPERTY WIN32_EXECUTABLE true)
endif()


target_compile_definitions(game-of-life
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
  
target_link_libraries(game-of-life
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)
  
if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(game-of-life)
endif()
