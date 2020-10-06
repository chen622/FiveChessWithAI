cmake_minimum_required(VERSION 3.16)
project(FiveChessWithAI)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR})
add_subdirectory(src)

#add_executable(fivechess src)