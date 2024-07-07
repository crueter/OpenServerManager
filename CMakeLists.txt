cmake_minimum_required(VERSION 3.5)

project(ServerUITest VERSION 0.1 LANGUAGES CXX)

# set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets VirtualKeyboard)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets VirtualKeyboard)

set(UI_ELEMENTS
    MainWindow

    server/ServerPreview

    pages/ServersPage

    dialogs/ServerInfoDialog
    dialogs/ConsoleOutputDialog
)

set(CODE_ELEMENTS
    ServerData

    data/DataManager
)

set(RESOURCES
    icons.qrc
)

foreach(ELEMENT ${UI_ELEMENTS})
    set(HEADERS ${HEADERS} include/${ELEMENT}.h)
    set(SOURCES ${SOURCES} src/${ELEMENT}.cpp)
    set(UI ${UI} ui/${ELEMENT}.ui)
endforeach()

foreach(ELEMENT ${CODE_ELEMENTS})
    set(HEADERS ${HEADERS} include/${ELEMENT}.h)
    set(SOURCES ${SOURCES} src/${ELEMENT}.cpp)
endforeach()

foreach(RESOURCE ${RESOURCES})
    set(QRC ${QRC} ${RESOURCE})
endforeach()

set(PROJECT_SOURCES
    main.cpp

    ${UI}
    ${HEADERS}
    ${SOURCES}
    ${QRC}
)

qt_wrap_ui(SOURCES ${UI})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ServerUITest
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ServerUITest APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ServerUITest SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ServerUITest
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ServerUITest PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::VirtualKeyboard)
target_include_directories(ServerUITest PRIVATE "include")
target_include_directories(ServerUITest PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ServerUITest)
endif()
set_target_properties(ServerUITest PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ServerUITest
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ServerUITest)
endif()
