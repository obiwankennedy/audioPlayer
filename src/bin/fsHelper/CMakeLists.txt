cmake_minimum_required(VERSION 3.16)

project(fsHelper VERSION 1.0 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

set(src main.cpp mainwindow.ui mainwindow.h mainwindow.cpp)


qt_add_executable(fsHelper ${src}
    mainwindow.h mainwindow.cpp mainwindow.ui
    sizedfilesystemmodel.h sizedfilesystemmodel.cpp)

target_link_libraries(fsHelper PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)
