cmake_minimum_required(VERSION 3.16)
project(arm-pi-tweaker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt5
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

# Enable Qt's automatic MOC, UIC, and RCC processing
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Source files
set(SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    upgradewidget.cpp
    upgradewidget.h
    systemmanager.cpp
    systemmanager.h
    gpumanager.cpp
    gpumanager.h
    kernelmanager.cpp
    kernelmanager.h
    storagemanager.cpp
    storagemanager.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link Qt libraries
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets)

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)