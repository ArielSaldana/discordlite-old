cmake_minimum_required(VERSION 3.25)
project(discord_bot)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

add_executable(discord_bot main.cpp)
target_link_libraries(discord_bot PUBLIC discord_client PRIVATE ${OPENSSL_CRYPTO_LIBRARY} PRIVATE ${OPENSSL_SSL_LIBRARY})
