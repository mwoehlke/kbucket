cmake_minimum_required(VERSION 3.6)
project(kbucket)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)

find_package(Qt5 5.3.0 CONFIG REQUIRED COMPONENTS Core Gui Widgets)
find_package(KF5 5.2.0 REQUIRED COMPONENTS
    CoreAddons
    I18n
    XmlGui
    TextWidgets
)

add_executable(${PROJECT_NAME}
    MainWindow.cpp
    main.cpp
)

target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    KF5::CoreAddons
    KF5::I18n
    KF5::XmlGui
    KF5::TextWidgets
)

install(TARGETS ${PROJECT_NAME} ${INSTALL_TARGETS_DEFAULT_ARGS})
