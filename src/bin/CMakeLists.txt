cmake_minimum_required(VERSION 3.16)

if(ANDROID)
          add_subdirectory(client)
          set_property(TARGET audioClient PROPERTY
                    QT_ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
          set_property(TARGET audioClient PROPERTY
                    QT_ANDROID_TARGET_SDK_VERSION 34)
else()
          add_subdirectory(server)
          add_subdirectory(player)
          add_subdirectory(client)
endif()

