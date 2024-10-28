cmake_minimum_required(VERSION 3.10)

project(polyshmup LANGUAGES C)
add_executable(polyshmup)

include_directories(BEFORE p8sdl)

source_group(TREE . PREFIX p8sdl)

target_sources(polyshmup PRIVATE game.c)
target_sources(polyshmup PRIVATE 
    p8sdl/p8sdl-colors.c
    p8sdl/p8sdl-consts.c
    p8sdl/p8sdl-draw.c
    p8sdl/p8sdl-print.c
    p8sdl/p8sdl-screenshot.c
    p8sdl/p8sdl-sprites.c
    p8sdl/p8sdl.c
)

find_package(SDL2 REQUIRED)
include_directories(polyshmup ${SDL2_INCLUDE_DIRS})
target_link_libraries(polyshmup ${SDL2_LIBRARIES})

find_package(SDL2_ttf REQUIRED)
target_link_libraries(polyshmup SDL2_ttf::SDL2_ttf)
