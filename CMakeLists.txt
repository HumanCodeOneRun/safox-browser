cmake_minimum_required(VERSION 3.5)

project(FolkTell VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_PREFIX_PATH "/Users/cuddly/Qt/6.2.4/macos/lib/cmake")
# add your own cmake prefix path
list(APPEND CMAKE_PREFIX_PATH "/Users/stevenwong/Qt/6.2.4/macos")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools WebEngineCore Sql Core WebEngineWidgets)
#find_package(Qt6 REQUIRED COMPONENTS WebEngineWidgets)



include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/dao)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools WebEngineWidgets WebEngineCore Sql Core) 

set(TS_FILES FolkTell_zh_CN.ts)

set(PROJECT_SOURCES
        src/main.cpp
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
        src/user/usermodel.h
        src/user/usermodel.cpp
        # src/tests/user/user_test.cpp
#        qtsingleapplication.cpp
#        qtsingleapplication.h
#        mainmenu.cpp
#        mainmenu.h
#        mainmenu.ui
#        icon.qrc

        ${TS_FILES}
)



if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_library(
        FolkTell_lib
        SHARED
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

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
target_link_libraries(FolkTell_lib PUBLIC Qt${QT_VERSION_MAJOR}::Widgets Qt6::WebEngineCore Qt6::Sql Qt6::Core Qt${QT_VERSION_MAJOR}::WebEngineWidgets)

set_target_properties(FolkTell PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    AUTOMOC TRUE
)




enable_testing()
add_subdirectory(tests)
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(FolkTell)
endif()
