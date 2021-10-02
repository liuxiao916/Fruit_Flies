cmake_minimum_required(VERSION 3.15)
project(fly_state_new)

find_package(OpenCV REQUIRED)
set(CMAKE_CXX_STANDARD 14)

add_executable(fly_state_new main.cpp state.cpp state.h board.cpp board.h)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(fly_state_new ${OpenCV_LIBS})