#add_subdirectory(basic_chess)
set(BASIC_CHESS basic_chess.cpp)
set(PLAYER player.cpp)
add_executable(fivechess main.cpp ${BASIC_CHESS} ${PLAYER})