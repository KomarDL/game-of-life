cmake_minimum_required(VERSION 3.16)

project(game-of-life VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Qml Quick Widgets)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(game-of-life
    main.cpp
    global.h
    cell.h
)

target_link_libraries(game-of-life PRIVATE
    Qt6::Core
    Qt6::Qml
    Qt6::Quick
    Qt6::Widgets
)

qt_add_qml_module(game-of-life
    URI
        game.of.life
    QML_FILES
        Main.qml
    SOURCES
        gamemodel.h gamemodel.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(game-of-life PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appgame-of-life
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)


include(GNUInstallDirs)
install(TARGETS game-of-life
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
