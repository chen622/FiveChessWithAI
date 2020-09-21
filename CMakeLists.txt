cmake_minimum_required(VERSION 3.16)
project(FiveChessWithAI)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(src DIR_SRCS)

add_executable(fivechess ${DIR_SRCS})