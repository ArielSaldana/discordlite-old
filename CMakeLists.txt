cmake_minimum_required(VERSION 3.26)
project(discordlite)

set(CMAKE_CXX_STANDARD 23)

# RapidJSON library to quickly parse json
find_package(RapidJSON CONFIG REQUIRED)

# Dependency websocketpp required for websockets
find_package(websocketpp CONFIG REQUIRED)

# Retrieve include directories for websocketpp and add them to our include directories
get_target_property(websocketpp_INCLUDE_DIRS websocketpp::websocketpp INTERFACE_INCLUDE_DIRECTORIES)
include_directories(${websocketpp_INCLUDE_DIRS})

#target_link_libraries(discordlite PUBLIC rapidjson)


add_library(discordlite library.cpp)

add_subdirectory(discord-client)
add_subdirectory(discord-bot)
target_link_libraries(discord_bot PUBLIC discord_client)


#find_package(RapidJSON CONFIG REQUIRED)
#target_link_libraries(main PRIVATE rapidjson)


