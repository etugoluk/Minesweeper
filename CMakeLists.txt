cmake_minimum_required(VERSION 3.1)
project(minesweeper)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror")

set(SRC_EXE src/main.cpp src/Exception.cpp)
set(SRC_GUI_LIB GUI/GUI.cpp)
set(SRC_LOGIC_LIB Logic/Cell.cpp Logic/Logic.cpp)

add_library(logic_lib SHARED ${SRC_LOGIC_LIB})
add_library(gui_lib SHARED ${SRC_GUI_LIB})

add_executable(minesweeper ${SRC_EXE})

target_link_libraries(minesweeper logic_lib)
target_link_libraries(minesweeper gui_lib)