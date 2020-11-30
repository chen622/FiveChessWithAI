set(BASIC_CHESS basic_chess.cpp)
set(PLAYER player.cpp)
set(GAME chess_game.cpp)
set(TREE tree_node.cpp)

add_executable(fivechess main.cpp ${BASIC_CHESS} ${PLAYER} ${GAME} ${TREE})
add_executable(fivechess_svr server.cpp  ${BASIC_CHESS} ${PLAYER} ${GAME} ${TREE})
target_link_libraries(fivechess_svr http_svr jsoncpp)