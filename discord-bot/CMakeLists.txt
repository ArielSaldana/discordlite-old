cmake_minimum_required(VERSION 3.25)
project(discord_bot)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

add_executable(discord_bot main.cpp)
#target_link_libraries(example PRIVATE ${CMAKE_BINARY_DIR}/libwarframe.dylib)
#target_link_libraries(discord_bot PRIVATE discordlite ${OPENSSL_CRYPTO_LIBRARY} ${OPENSSL_SSL_LIBRARY})
target_link_libraries(discord_bot PUBLIC discord_client)
#target_link_libraries(discord_bot PRIVATE discord_client ${OPENSSL_CRYPTO_LIBRARY} ${OPENSSL_SSL_LIBRARY})
