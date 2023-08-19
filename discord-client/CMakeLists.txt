cmake_minimum_required(VERSION 3.26)
project(discord_client)

set(CMAKE_CXX_STANDARD 23)

add_library(discord_client src/library.cpp
        include/gateway/v10/events/receive/hello.h
        include/gateway/v10/events/send/identify.h
        include/gateway/v10/events/serialize.h
        include/gateway/v10/events/deserialize.h)

file(GLOB_RECURSE HEADER_FILES include/*.h)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

target_include_directories(discord_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${RapidJSON_INCLUDE_DIRS})
target_link_libraries(discord_client PRIVATE discordlite ${OPENSSL_CRYPTO_LIBRARY} ${OPENSSL_SSL_LIBRARY})
