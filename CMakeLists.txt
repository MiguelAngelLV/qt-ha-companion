cmake_minimum_required(VERSION 3.5)

project(QtHaCompanion LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Mqtt REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Mqtt REQUIRED)


add_executable(QtHaCompanion
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
        src/home-assistant/HADevice.cpp
        src/home-assistant/HADevice.h
        src/home-assistant/HASensor.cpp src/home-assistant/HASensor.h
        src/sensors/RAMUsage.cpp src/sensors/RAMUsage.h
        src/HomeAssistantCompanion.cpp src/HomeAssistantCompanion.h)

target_link_libraries(QtHaCompanion PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Mqtt)
