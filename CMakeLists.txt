cmake_minimum_required(VERSION 3.5)

project(customPlayer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



#设置本地头文件路径，注意：子目录中的头文件通过target_include_directories 添加到${PROJECT_NAME}中
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/
                    ${CMAKE_CURRENT_SOURCE_DIR}/${CUSTOM_LOG_INCLUDE_DIR}/
)

if(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
    message("current platform : Linux")
    set(FFMPEG_PATH "/home/xh/share/learn_test/installFFmpeg")
    set(SDL2_INCLUDE_PATH "/usr/include/SDL2")
    set(SDL2_LIB_PATH "/usr/lib/x86_64-linux-gnu")
    set(CMAKE_CXX_FLAGS -pthread)
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
    message("current platform : Windows")
    set(FFMPEG_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ffmpeg-6.1.1-full_build-shared")
    set(SDL2_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/SDL2/include")
    set(SDL2_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/SDL2/lib/x64")
else()
    message("current platform : unkonw ")
endif()


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwind.cpp
        mainwind.h
        mainwind.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ctrlbar.h ctrlbar.cpp ctrlbar.ui
        displaywind.h displaywind.cpp displaywind.ui
        playlistwind.h playlistwind.cpp playlistwind.ui
        titlebar.h titlebar.cpp titlebar.ui
        icon.qrc
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(${PROJECT_NAME}
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
                            "${CMAKE_CURRENT_SOURCE_DIR}/."
                            "${SDL2_INCLUDE_PATH}"
                            "${FFMPEG_PATH}/include"
                            "${CMAKE_CURRENT_SOURCE_DIR}/${CUSTOM_LOG_INCLUDE_DIR}/"
                            )


target_link_directories(${PROJECT_NAME} PRIVATE
                        "${SDL2_LIB_PATH}"
                        "${FFMPEG_PATH}/lib/")

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_link_libraries(${PROJECT_NAME} PRIVATE custom_log)

target_link_libraries(${PROJECT_NAME} PRIVATE message_queue)

target_link_libraries(${PROJECT_NAME} PRIVATE ijkmediaplayer)

#target_link_libraries(${PROJECT_NAME} PRIVATE
#                        "${CMAKE_CURRENT_SOURCE_DIR}/SDL2/lib/x64/SDL2.lib"
#                        "${CMAKE_CURRENT_SOURCE_DIR}/ffmpeg-4.2.1-win32-dev/lib/avformat.lib"
#                        "${CMAKE_CURRENT_SOURCE_DIR}/ffmpeg-4.2.1-win32-dev/lib/avcodec.lib"
#                        "${CMAKE_CURRENT_SOURCE_DIR}/ffmpeg-4.2.1-win32-dev/lib/avdevice.lib"
#                        "${CMAKE_CURRENT_SOURCE_DIR}/ffmpeg-4.2.1-win32-dev/lib/avfilter.lib"
#                        "${CMAKE_CURRENT_SOURCE_DIR}/ffmpeg-4.2.1-win32-dev/lib/avutil.lib"
#                        "${CMAKE_CURRENT_SOURCE_DIR}/ffmpeg-4.2.1-win32-dev/lib/postproc.lib"
#                        "${CMAKE_CURRENT_SOURCE_DIR}/ffmpeg-4.2.1-win32-dev/lib/swresample.lib"
#                        "${CMAKE_CURRENT_SOURCE_DIR}/ffmpeg-4.2.1-win32-dev/lib/swscale.lib"
#                        "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22000.0/um/x64/Ole32.Lib")

set(ADD_LIBRARIES
    $<$<PLATFORM_ID:Windows>:avformat avcodec avdevice avfilter avutil swresample swscale SDL2>
    $<$<OR:$<PLATFORM_ID:Linux>,$<PLATFORM_ID:Android>>:avformat avcodec avdevice avfilter avutil swresample swscale SDL2>
)

target_link_libraries(${PROJECT_NAME} PRIVATE "${ADD_LIBRARIES}")

#添加子目录，这样子目录中CMakeLists.txt才会被调用
add_subdirectory(custom_log)
add_subdirectory(message_queue)
add_subdirectory(ijkmediaplayer)



# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.player)
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
