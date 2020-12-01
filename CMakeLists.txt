cmake_minimum_required(VERSION 3.16)
project(FiveChessWithAI)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(thirdparty)
include_directories(thirdparty)

add_subdirectory(src bin)