cmake_minimum_required(VERSION 3.16)
project(FiveChessWithAI)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)

add_executable(fivechess ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(fivechess fivechess_src)