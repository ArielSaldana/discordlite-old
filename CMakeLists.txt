cmake_minimum_required(VERSION 3.26)
project(discordlite)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_ROOT_DIR})
include_directories(${OPEN_SSL_HEADER_ROOT_DIR})

# RapidJSON library to quickly parse json
find_package(RapidJSON CONFIG REQUIRED)

# Dependency websocketpp required for websockets
find_package(websocketpp CONFIG REQUIRED)

# Retrieve include directories for websocketpp and add them to our include directories
get_target_property(websocketpp_INCLUDE_DIRS websocketpp::websocketpp INTERFACE_INCLUDE_DIRECTORIES)
include_directories(${websocketpp_INCLUDE_DIRS})

#target_link_libraries(discordlite PUBLIC rapidjson)

#file(GLOB_RECURSE HEADER_FILES include/*.h)
#file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
#
#add_library(discordlite SHARED ${HEADER_FILES} ${SOURCE_FILES})

#add_library(discordlite)

add_subdirectory(discord-client)
add_subdirectory(discord-bot)
target_link_libraries(discord_bot PUBLIC discord_client)

#find_package(RapidJSON CONFIG REQUIRED)
#target_link_libraries(main PRIVATE rapidjson)
