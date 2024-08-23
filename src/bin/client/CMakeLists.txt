cmake_minimum_required(VERSION 3.16)

find_package(Qt6 REQUIRED COMPONENTS Core DBus Quick Network Svg Multimedia WebSockets)
qt_standard_project_setup(REQUIRES 6.5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTORCC ON)

set(source main.cpp
    )

set(header
    )

qt_add_executable(audioClient ${header} ${source})

qt_add_qml_module(audioClient
URI
    Views
VERSION
    1.0
QML_FILES
    Main.qml
    SOURCES ClientController.h ClientController.cpp
)

target_link_libraries(audioClient PRIVATE
    Qt6::Core
    Qt6::Network
    Qt6::WebSockets
    Qt6::DBus
    Qt6::Svg
    Qt6::Multimedia
    Qt6::Quick
    core
)
