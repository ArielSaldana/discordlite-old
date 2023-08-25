cmake_minimum_required(VERSION 3.26)
project(discord_client)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(discord_client src/client.cpp
        src/gateway/v10/events/receive/hello.h
        src/gateway/v10/events/send/identify.h
        src/gateway/v10/events/serializable.h
        src/gateway/v10/events/deserializable.h
        src/networking/socket.h
        src/networking/socket.cpp)

file(GLOB_RECURSE HEADER_FILES include/*.h)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

target_include_directories(discord_client
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${RapidJSON_INCLUDE_DIRS})
#target_link_libraries(discord_client PRIVATE discordlite ${OPENSSL_CRYPTO_LIBRARY} ${OPENSSL_SSL_LIBRARY})
