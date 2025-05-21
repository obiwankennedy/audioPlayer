cmake_minimum_required(VERSION 3.16)

find_package(Qt6 REQUIRED COMPONENTS Core Quick Gui Svg Multimedia QuickControls2)
qt_standard_project_setup(REQUIRES 6.5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(PkgConfig)
pkg_check_modules(TAGLIB REQUIRED IMPORTED_TARGET taglib)
set(CMAKE_AUTORCC ON)

set(source maincontroller.cpp
    albumpictureprovider.cpp
    artcoverimage.cpp
    commandserver.cpp
    devicemodel.cpp
    messagefactory.cpp
    worker/fakenetworkreceiver.cpp
    worker/filereaderhelper.cpp
    )

set(header maincontroller.h
    albumpictureprovider.h
    artcoverimage.h
    commandserver.h
    constants.h
    messagefactory.h
    devicemodel.h
    worker/fakenetworkreceiver.h
    worker/filereaderhelper.h
    )

qt_add_library(core ${header} ${source})

qt_add_qml_module(core
URI
    Controllers
VERSION
    1.0
SOURCES
    maincontroller.h
    maincontroller.cpp
    audiocontroller.h
    audiocontroller.cpp
    filteredmodel.h
    filteredmodel.cpp
    audiofilemodel.h
    audiofilemodel.cpp
    imagedataviewer.h
    imagedataviewer.cpp
)

add_subdirectory(worker)

if(ANDROID)
target_link_libraries(core PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::Gui
    Qt6::Svg
    Qt6::Multimedia
    Qt6::QuickControls2
    customLibplugin
)
else()
target_link_libraries(core PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::Gui
    Qt6::Svg
    Qt6::Multimedia
    Qt6::QuickControls2
    PkgConfig::TAGLIB
    customLibplugin
)
endif()
target_include_directories(core
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
