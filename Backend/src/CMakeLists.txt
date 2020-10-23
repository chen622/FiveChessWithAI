set(BASIC_CHESS basic_chess.cpp)
set(PLAYER player.cpp)
set(GAME chess_game.cpp)

add_executable(fivechess main.cpp ${BASIC_CHESS} ${PLAYER} ${GAME})
add_executable(fivechess_svr server.cpp)
target_link_libraries(fivechess_svr http_svr jsoncpp)