cmake_minimum_required(VERSION 3.16)

find_package(Qt6 REQUIRED COMPONENTS Core Quick Gui DBus Svg Multimedia QuickControls2)
qt_standard_project_setup(REQUIRES 6.5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

qt_add_library(customLib STATIC)
qt_add_qml_module(customLib
URI
    Customization
VERSION
    1.0
SOURCES
    theme.cpp
    theme.h
)

