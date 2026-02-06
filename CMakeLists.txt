cmake_minimum_required(VERSION 3.16)

project(acoustic-calibrator-terminal LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS SerialPort)

add_executable(acoustic-calibrator-terminal
  main.cpp
  mainwindow/mainwindow.cpp
  mainwindow/mainwindow.h
  mainwindow/main_window_labels.h
  com_port_driver/com_port_driver.cpp
  com_port_driver/com_port_driver.h
)
target_link_libraries(acoustic-calibrator-terminal PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(acoustic-calibrator-terminal PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(acoustic-calibrator-terminal PRIVATE Qt${QT_VERSION_MAJOR}::SerialPort)

target_include_directories(acoustic-calibrator-terminal PRIVATE mainwindow com_port_driver)

include(GNUInstallDirs)
install(TARGETS acoustic-calibrator-terminal
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
