cmake_minimum_required(VERSION 3.16)

project(audioPlayer VERSION 1.0 LANGUAGES CXX)


find_package(Qt6 REQUIRED COMPONENTS Core Quick Gui DBus Svg Multimedia QuickControls2)
qt_standard_project_setup(REQUIRES 6.5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(PkgConfig)
pkg_check_modules(TAGLIB REQUIRED IMPORTED_TARGET taglib)


set(CMAKE_AUTORCC ON)


add_subdirectory(src)
