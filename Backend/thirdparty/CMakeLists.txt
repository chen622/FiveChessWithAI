set(MONGOOSE mongoose.c)
add_library(mongoose SHARED ${MONGOOSE})

set(HTTP_SVR http_server.cpp)
add_library(http_svr SHARED ${HTTP_SVR})
target_link_libraries(http_svr mongoose)