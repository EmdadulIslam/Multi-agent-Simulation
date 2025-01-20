cmake_minimum_required(VERSION 3.16)
project(RT_MASP VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt
find_package(Qt6 COMPONENTS Core Widgets Gui Concurrent REQUIRED)

# TensorFlow (assumes you've installed or built TensorFlow C++ libraries)
# Adjust the paths to match your local setup
find_path(TENSORFLOW_INCLUDE_DIR tensorflow)
find_library(TENSORFLOW_LIB tensorflow_cc)

include_directories(
    ${TENSORFLOW_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(RT-MASP
    main.cpp
    src/Agent.cpp
    src/Environment.cpp
    src/SimulationManager.cpp
    src/MainWindow.cpp
)

target_link_libraries(RT-MASP
    Qt6::Core
    Qt6::Widgets
    Qt6::Gui
    Qt6::Concurrent
    ${TENSORFLOW_LIB}
)

