//
// Created by trida on 8/3/25.
//

#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <random>
#include <thread>

#include "enemies/Knight.h"
#include "enemies/Mage.h"
#include "enemies/Skeleton.h"
#include "enemies/Zombie.h"

#include <vector>
#include <unordered_map>




class Enemy_manager {
private:
    typedef enum {
        ZOMBIES,
        KNIGHTS,
        MAGES,
        SKELETONS
    }ENEMIES_MAP_INDEXES;

    std::vector<std::vector<int>>  can_be_walked;
    int map_width;
    int map_height;

    std::vector<std::thread> threads;

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> enemy_type_generator;
    std::uniform_int_distribution<int> enemy_x_coord_generator;
    std::uniform_int_distribution<int> enemy_y_coord_genetator;

    int max_enemy_number;

    int zombies_spawn_percentage = 40;
    int kgnith_spawn_percentage = 30;
    int skeleton_spawn_percentage = 20;
    int mage_spawn_percentage = 10;

    std::unordered_map<ENEMIES_MAP_INDEXES, std::vector<Enemy*> > enemies_map;

    void update_enemies_type(std::vector<Enemy*> &vec, int x, int y, SDL_Renderer* renderer);

public:
    Enemy_manager();

    void set_map( std::vector<std::vector<int>> can_be_walked, int high, int width);
    void generate_enemies(int map, int level );
    void print_enemies(SDL_Renderer *renderer, int x, int y);


};



#endif //ENEMY_MANAGER_H
