cmake_minimum_required(VERSION 3.30)
project(SDL2_2DPlatformer)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

add_executable(SDL2_2DPlatformer main.cpp
        src/Game_Engine.cpp
        src/Game_Engine.h
        src/Player.cpp
        src/Player.h
        src/FPSCounter.cpp
        src/FPSCounter.h
        src/Inventory.cpp
        src/Inventory.h
        src/Item.cpp
        src/Item.h
)

target_link_libraries(SDL2_2DPlatformer ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL_TTF_LIBRARIES} SDL2_image SDL2_ttf)

