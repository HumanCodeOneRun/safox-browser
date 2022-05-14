cmake_minimum_required(VERSION 3.5)

project(FolkTell VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(${PROJECT_NAME}_TEST "enable test" ON)
set(CMAKE_PREFIX_PATH "/Users/stevenwong/Qt/6.2.4/macos/lib/cmake")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools WebEngineCore Sql Core WebEngineWidgets)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/lib/dao)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools WebEngineWidgets WebEngineCore Sql Core) 

set(TS_FILES FolkTell_zh_CN.ts)

set(PROJECT_SOURCES
        src/main.cpp
<<<<<<< HEAD
        #src/browserwindow/browserwindow.cpp
        #src/browserwindow/browserwindow.h
        #src/browserwindow/browserwindow.ui
        #src/lib/toolbar/toolbar.cpp
        #src/lib/toolbar/toolbar.h
        #src/lib/toolbar/toolbar.ui
        #src/browser.cpp
        #src/browser.h
        #src/mainapplication.cpp
        #src/mainapplication.h
        
        #src/lib/history/historyitem.cpp
        #src/lib/history/historyitem.h
        #src/lib/history/history.cpp
        #src/lib/history/history.h
        #src/lib/history/historymodel.h
        #src/lib/history/historymodel.cpp
        #src/lib/history/historydao.h
        #src/lib/history/historydao.cpp
        #src/lib/history/historybar.h
        #src/lib/history/historybar.cpp
        #src/lib/history/historybar.ui
        #src/lib/history/historywidget.h
        #src/lib/history/historywidget.cpp
        #src/lib/history/historywidget.ui
        src/lib/webengine/webview.cpp
        src/lib/webengine/webview.h
        src/lib/dao/basedao.h
        src/lib/dao/basedao.cpp
        src/lib/dao/bookmarkdao.cpp
        src/lib/dao/bookmarkdao.h
        src/lib/dao/bookmarkgroupdao.cpp
        src/lib/dao/bookmarkgroupdao.h
        src/lib/dao/userdao.h
        src/lib/dao/userdao.cpp
        src/lib/bookmark/bookmarkmodel.h
        src/lib/bookmark/bookmarkmodel.cpp
        src/lib/user/usermodel.h
        src/lib/user/usermodel.cpp
        src/lib/downloads/downloaditem.h
        src/lib/downloads/downloaditem.cpp
        src/lib/downloads/downloadmanager.h
        src/lib/downloads/downloadmanager.cpp
        src/lib/dao/connections.h
        src/lib/dao/connections.cpp
=======
        src/browserwindow/browserwindow.cpp
        src/browserwindow/browserwindow.h
        src/browserwindow/browserwindow.ui
        src/toolbar/toolbar.cpp
        src/toolbar/toolbar.h
        src/toolbar/toolbar.ui
        src/browser.cpp
        src/browser.h
        src/mainapplication.cpp
        src/mainapplication.h
        src/history/historyitem.cpp
        src/history/historyitem.h
        src/history/history.cpp
        src/history/history.h
        src/history/historymodel.h
        src/history/historymodel.cpp
        src/history/historydao.h
        src/history/historydao.cpp
        src/history/historybar.h
        src/history/historybar.cpp
        src/history/historybar.ui
        src/history/historywidget.h
        src/history/historywidget.cpp
        src/history/historywidget.ui
        src/webengine/webview.cpp
        src/webengine/webview.h
        src/dao/basedao.h
        src/dao/basedao.cpp
        src/dao/bookmarkdao.cpp
        src/dao/bookmarkdao.h
        src/dao/bookmarkgroupdao.cpp
        src/dao/bookmarkgroupdao.h
        src/dao/userdao.h
        src/dao/userdao.cpp
        src/bookmark/bookmarkmodel.h
        src/bookmark/bookmarkmodel.cpp
        src/bookmark/bookmarkwidget.h
        src/bookmark/bookmarkwidget.cpp
        src/bookmark/bookmarkwidget.ui
        src/bookmark/bookmarkitem.h
        src/bookmark/bookmarkitem.cpp
        src/bookmark/bookmarkitem.ui
        src/user/usermodel.h
        src/user/usermodel.cpp
        # src/tests/user/user_test.cpp
>>>>>>> 3eaab7e (add bookmarkWidget)
#        qtsingleapplication.cpp
#        qtsingleapplication.h
#        mainmenu.cpp
#        mainmenu.h
#        mainmenu.ui
        src/icon.qrc
        src/lib/taskscheduler/databasetaskscheduler.h
        src/lib/taskscheduler/databasetaskscheduler.cpp
        src/lib/setting/Config.h
        src/lib/setting/Config.cpp
        src/lib/setting/homepage.h
        src/lib/setting/homepage.cpp
        ${TS_FILES}
        )



if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    if(${PROJECT_NAME}_TEST)
        qt_add_library(
            FolkTell_lib
            SHARED
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
        )
    endif()

    qt_add_executable(
        FolkTell
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

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

target_link_libraries(FolkTell PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::WebEngineCore Qt6::Sql Qt6::Core Qt${QT_VERSION_MAJOR}::WebEngineWidgets)

set_target_properties(FolkTell PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    AUTOMOC TRUE
)



if(${PROJECT_NAME}_TEST)
    target_link_libraries(FolkTell_lib PUBLIC Qt${QT_VERSION_MAJOR}::Widgets Qt6::WebEngineCore Qt6::Sql Qt6::Core Qt${QT_VERSION_MAJOR}::WebEngineWidgets)
    enable_testing()
    add_subdirectory(tests)
endif()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(FolkTell)
endif()
