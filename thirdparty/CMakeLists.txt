set(MONGOOSE mongoose.c)
add_library(mongoose SHARED ${MONGOOSE})

set(HTTP_SVR http_server.cpp)
add_library(http_svr SHARED ${HTTP_SVR})
target_link_libraries(http_svr mongoose)

include_directories(${CMAKE_CURRENT_LIST_DIR})

add_library( # Sets the name of the library.
        jsoncpp
        # Sets the library as a shared library.
        SHARED
        # Provides a relative path to your source file(s).
        json/json_tool.h
        json/json_reader.cpp
        json/json_valueiterator.inl
        json/json_value.cpp
        json/json_writer.cpp
        json/assertions.h
        json/allocator.h
        json/config.h
        json/json_features.h
        json/forwards.h
        json/json.h
        json/reader.h
        json/value.h
        json/version.h
        json/writer.h
        )