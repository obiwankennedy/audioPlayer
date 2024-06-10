cmake_minimum_required(VERSION 3.16)

project(audioPlayer VERSION 1.0 LANGUAGES CXX)


find_package(Qt6 REQUIRED COMPONENTS Core Quick Gui DBus Svg Multimedia QuickControls2)
qt_standard_project_setup(REQUIRES 6.5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(PkgConfig)
pkg_check_modules(TAGLIB REQUIRED IMPORTED_TARGET taglib)
set(CMAKE_AUTORCC ON)

set(source main.cpp maincontroller.cpp
    albumpictureprovider.cpp
    artcoverimage.cpp
    commandserver.cpp
    devicemodel.cpp
    worker/fakenetworkreceiver.cpp
    worker/filereaderhelper.cpp
    )

set(header maincontroller.h
    albumpictureprovider.h
    artcoverimage.h
    commandserver.h
    devicemodel.h
    worker/fakenetworkreceiver.h
    worker/filereaderhelper.h
    )

qt_add_executable(audioPlayer ${header} ${source} resources.qrc)

qt_add_qml_module(audioPlayer
URI
    Views
VERSION
    1.0
QML_FILES
    resources/qml/AudioPlayer.qml
    resources/qml/EditMenu.qml
    resources/qml/FileMenu.qml
    resources/qml/ImageButton.qml
    resources/qml/Main.qml
SOURCES
    maincontroller.h
    maincontroller.cpp
    audiocontroller.h
    audiocontroller.cpp
    filteredmodel.h
    filteredmodel.cpp
    audiofilemodel.h
    audiofilemodel.cpp
)

qt_add_library(customLib STATIC)
qt_add_qml_module(customLib
URI
    Customization
VERSION
    1.0
SOURCES
    worker/theme.cpp
    worker/theme.h
)

target_link_libraries(audioPlayer PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::Gui
    Qt6::DBus
    Qt6::Svg
    Qt6::Multimedia
    Qt6::QuickControls2
    PkgConfig::TAGLIB
    customLibplugin
)
