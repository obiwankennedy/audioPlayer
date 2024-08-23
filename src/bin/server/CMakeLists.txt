cmake_minimum_required(VERSION 3.16)

find_package(Qt6 REQUIRED COMPONENTS Core DBus Quick Network Svg Multimedia WebSockets)
qt_standard_project_setup(REQUIRES 6.5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(PkgConfig)
pkg_check_modules(TAGLIB REQUIRED IMPORTED_TARGET taglib)
set(CMAKE_AUTORCC ON)

set(source main.cpp
    )

set(header
    )

qt_add_executable(audioServer ${header} ${source}
    servermanager.h servermanager.cpp
    websocketdecoder.h websocketdecoder.cpp)

target_link_libraries(audioServer PRIVATE
    Qt6::Core
    Qt6::Network
    Qt6::WebSockets
    Qt6::DBus
    Qt6::Svg
    Qt6::Multimedia
    Qt6::Quick
    PkgConfig::TAGLIB
    core
)
