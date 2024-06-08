cmake_minimum_required(VERSION 3.5)

project(lab_04_2cabins VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        config.hpp
        button/base_button.cpp
        button/base_button.hpp
        button/floor_button/floor_button.cpp
        button/floor_button/floor_button.hpp
        button/elevator_button/elevator_button.cpp
        button/elevator_button/elevator_button.hpp
        controller/controller.cpp
        controller/controller.hpp
        cabin_new/cabin.cpp
        cabin_new/cabin.h
        doors_new/doors.cpp
        doors_new/doors.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(lab_04_2cabins
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        elevator_system/elevator_system.hpp elevator_system/elevator_system.cpp
        controller/controller.hpp controller/controller.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET lab_04_2cabins APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(lab_04_2cabins SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(lab_04_2cabins
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(lab_04_2cabins PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.lab_04_2cabins)
endif()
set_target_properties(lab_04_2cabins PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS lab_04_2cabins
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(lab_04_2cabins)
endif()
