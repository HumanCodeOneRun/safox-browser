cmake_minimum_required(VERSION 3.5)

project(FolkTell VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
option(${PROJECT_NAME}_TEST "enable test" OFF)
#set(CMAKE_PREFIX_PATH "/Users/stevenwong/Qt/6.2.4/macOS/lib/cmake" )
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools WebEngineCore Sql Core WebEngineWidgets)

function(include_sub_directories_recursively root_dir)
    if (IS_DIRECTORY ${root_dir})     

        include_directories(${root_dir})
    endif()

    file(GLOB ALL_SUB RELATIVE ${root_dir} ${root_dir}/*) 
    foreach(sub ${ALL_SUB})
        if (IS_DIRECTORY ${root_dir}/${sub})
            include_sub_directories_recursively(${root_dir}/${sub}) 
        endif()
    endforeach()
endfunction()

include_sub_directories_recursively(${CMAKE_CURRENT_SOURCE_DIR})




find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools WebEngineWidgets WebEngineCore Sql Core)

set(TS_FILES FolkTell_zh_CN.ts)

set(PROJECT_SOURCES
        src/main.cpp

        src/ui/browserwindow/browserwindow.cpp
        src/ui/browserwindow/browserwindow.h
        src/ui/browserwindow/browserwindow.ui
        src/ui/toolbar/toolbar.cpp
        src/ui/toolbar/toolbar.h
        src/ui/toolbar/toolbar.ui
        src/core/browser/browser.cpp
        src/core/browser/browser.h
        src/core/app/mainapplication.cpp
        src/core/app/mainapplication.h

        src/core/history/historyitem.cpp
        src/core/history/historyitem.h
        src/core/history/history.cpp
        src/core/history/history.h
        src/core/history/historymodel.h
        src/core/history/historymodel.cpp
        src/core/history/historydao.h
        src/core/history/historydao.cpp
        src/ui/history/historybar.h
        src/ui/history/historybar.cpp
        src/ui/history/historybar.ui
        src/ui/popupmenu/popupmenu.h
        src/ui/popupmenu/popupmenu.cpp
        src/ui/history/historywidget.h
        src/ui/history/historywidget.cpp
        src/ui/history/historywidget.ui
        src/core/webengine/webview.cpp
        src/core/webengine/webview.h
        src/core/dao/basedao.h
        src/core/dao/basedao.cpp
        src/core/dao/bookmarkdao.cpp
        src/core/dao/bookmarkdao.h
        src/core/dao/bookmarkgroupdao.cpp
        src/core/dao/bookmarkgroupdao.h
        src/core/dao/userdao.h
        src/core/dao/userdao.cpp
        src/core/bookmark/bookmarkmodel.h
        src/core/bookmark/bookmarkmodel.cpp
        src/ui/bookmark/bookmarkitem.h
        src/ui/bookmark/bookmarkitem.cpp
        src/ui/bookmark/bookmarkwidget.h
        src/ui/bookmark/bookmarkwidget.cpp
        src/core/user/usermodel.h
        src/core/user/usermodel.cpp
        src/core/downloads/downloaditem.h
        src/core/downloads/downloaditem.cpp
        src/core/downloads/downloadmanager.h
        src/core/downloads/downloadmanager.cpp
        src/core/dao/connections.h
        src/core/dao/connections.cpp

        src/core/third_party/ad-block/ad_block_client.cc
        src/core/third_party/ad-block/ad_block_client.h
        src/core/third_party/ad-block/bad_fingerprint.h
        src/core/third_party/ad-block/bad_fingerprints.h
        src/core/third_party/ad-block/base.h
        src/core/third_party/ad-block/BloomFilter.cpp
        src/core/third_party/ad-block/BloomFilter.h
        src/core/third_party/ad-block/context_domain.cc
        src/core/third_party/ad-block/context_domain.h
        src/core/third_party/ad-block/cosmetic_filter.cc
        src/core/third_party/ad-block/cosmetic_filter.h
        src/core/third_party/ad-block/filter.cc
        src/core/third_party/ad-block/filter.h
        src/core/third_party/ad-block/hashFn.cc
        src/core/third_party/ad-block/hashFn.h
        src/core/third_party/ad-block/hash_set.h
        src/core/third_party/ad-block/no_fingerprint_domain.cc
        src/core/third_party/ad-block/no_fingerprint_domain.h
        src/core/third_party/ad-block/protocol.cc
        src/core/third_party/ad-block/protocol.h

        src/core/adblock/adblock_request_interceptor.cpp
        src/core/adblock/adblock_request_interceptor.h
        src/core/adblock/default_request_interceptor.cpp
        src/core/adblock/default_request_interceptor.h

#        qtsingleapplication.cpp
#        qtsingleapplication.h
#        mainmenu.cpp
#        mainmenu.h
#        mainmenu.ui
        src/ui/icon.qrc
        src/core/taskscheduler/databasetaskscheduler.h
        src/core/taskscheduler/databasetaskscheduler.cpp
        src/core/setting/Config.h
        src/core/setting/Config.cpp
        src/core/setting/homepage.h
        src/core/setting/homepage.cpp

        src/core/service/service.h
        )



if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    if(${PROJECT_NAME}_TEST)
        qt_add_library(
            FolkTell_lib
            SHARED
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
        )

    else()
        qt_add_executable(
            FolkTell
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
        )
    endif()

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET FolkTell APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(FolkTell SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(FolkTell
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()





if(${PROJECT_NAME}_TEST)
    target_link_libraries(FolkTell_lib PUBLIC Qt${QT_VERSION_MAJOR}::Widgets Qt6::WebEngineCore Qt6::Sql Qt6::Core Qt${QT_VERSION_MAJOR}::WebEngineWidgets)
    enable_testing()
    add_subdirectory(tests)
else()
    target_link_libraries(FolkTell PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::WebEngineCore Qt6::Sql Qt6::Core Qt${QT_VERSION_MAJOR}::WebEngineWidgets)
    set_target_properties(FolkTell PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
        AUTOMOC TRUE
    )
    if(QT_VERSION_MAJOR EQUAL 6)
        qt_finalize_executable(FolkTell)
    endif()
endif()

