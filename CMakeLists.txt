cmake_minimum_required(VERSION 3.10)

project(DucklingLimbo)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

file(GLOB SRC_FILES src/*.cpp)

add_executable(DucklingLimbo ${SRC_FILES})

target_link_libraries(DucklingLimbo
    SDL2::SDL2
    SDL2_ttf::SDL2_ttf
)