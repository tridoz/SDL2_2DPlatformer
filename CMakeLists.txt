cmake_minimum_required(VERSION 3.30)
project(SDL2_2DPlatformer)

set(CMAKE_CXX_STANDARD 20)

# Trova le librerie SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Aggiungi le cartelle di inclusione per SDL2, pugixml e le altre librerie
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} /usr/include)

# Aggiungi l'eseguibile
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
        src/Enemy.cpp
        src/Enemy.h
        src/enemies/Zombie.cpp
        src/enemies/Zombie.h
        src/enemies/Knight.cpp
        src/enemies/Knight.h
        src/enemies/Skeleton.cpp
        src/enemies/Skeleton.h
        src/enemies/Mage.cpp
        src/enemies/Mage.h
        src/Enemy_manager.cpp
        src/Enemy_manager.h
)

# Collega le librerie necessarie
target_link_libraries(SDL2_2DPlatformer ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} pugixml SDL2_image SDL2_ttf)
