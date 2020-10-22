set(BASIC_CHESS basic_chess.cpp)
set(PLAYER player.cpp)
set(GAME chess_game.cpp)
#add_executable(fivechess main.cpp ${BASIC_CHESS} ${PLAYER} ${GAME})
# Add libraries
add_library(fivechess_src STATIC ${BASIC_CHESS} ${PLAYER} ${GAME})
target_include_directories(fivechess_src PRIVATE "${CMAKE_CURRENT_LIST_DIR}/*.h")