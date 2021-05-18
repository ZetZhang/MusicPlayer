cmake_minimum_required(VERSION 3.5) # default version 3.5

set(project_name MusicPlayer)
project(${project_name})

set(CMAKE_CXX_STANDARD 11)

# 项目文件
set(ui_files
    MainWidget.ui
    MusicListDialog.ui
    LyricWidget.ui
    )

set(qrc_files
    imagefile.qrc
    )

set(source_files
    main.cpp
    Music.cpp
    MainWidget.cpp
    MusicListWidget.cpp
    MusicList.cpp
    MusicListDialog.cpp
    LyricWidget.cpp
    SubPageDownloadSong.cpp
    SettingManager.cpp
    )

set(header_files
    Music.h
    myQSS.h
    MainWidget.h
    MusicListWidget.h
    MusicList.h
    MusicListDialog.h
    LyricWidget.h
    SubPageDownloadSong.h
    SettingManager.h
    sliderwithclick.h
    )

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Multimedia Sql Core REQUIRED)


add_library(qt_target ${source_files})
set(CMAKE_INSTALL_PREFIX "/tmp/${TARGET}/")
install(TARGETS qt_target DESTINATION bin)


find_package(PkgConfig)
# 添加pkg依赖xxx yyy zzz
find_package(PkgConfig REQUIRED)
pkg_search_module(PKGS_DEP REQUIRED
    libavcodec
    libavdevice
    libavfilter
    libavformat
    libavutil
    libpostproc
    libswresample
    libswscale
    sdl2
)
# # 上面的指令会生成 PKGS_DEP_CFLAGS 和 PKGS_DEP_LDFLAGS

# # 设置依赖pkg的CGLAGS
foreach(flag ${PKGS_DEP_CFLAGS}) 
    set(EXTRA_CFLGAS "${EXTRA_CFLGAS} ${flag}") 
endforeach(flag) 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLGAS}") 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_CFLGAS}") 

# # 设置依赖pkg的LDFLAGS
add_executable(${project_name} ${source_files} ${ui_files} ${qrc_files} ${header_files})
target_link_libraries(${project_name} Qt5::Widgets Qt5::Multimedia Qt5::Sql Qt5::Core)
target_link_libraries(${project_name} ${PKGS_DEP_LDFLAGS})

add_subdirectory(CloudMusic)
add_subdirectory(Utility)
add_subdirectory(qtsingleapplication/src)
