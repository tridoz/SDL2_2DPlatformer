//
// Created by trida on 8/3/25.
//

#include "Enemy_manager.h"

#include <iostream>
#include <random>

Enemy_manager::Enemy_manager() {
    this -> enemies_map.clear();
    this->gen = std::mt19937(rd());
}

void Enemy_manager::set_map(std::vector<std::vector<int>> can_be_walked, int high, int width) {
    this->map_width = width;
    this->map_height = high;
    this->can_be_walked = can_be_walked;
    this->enemy_x_coord_generator = std::uniform_int_distribution<int>(1, this->map_width - 2);
    this->enemy_y_coord_genetator = std::uniform_int_distribution<int>(1, this->map_height - 2);
    std::cout<<"mappa settata correttamente\n";
}


void Enemy_manager::generate_enemies(int map, int level) {
    std::cout << "[DEBUG] Inizio generazione nemici per mappa " << map << ", livello " << level << "\n";

    switch (map) {
        case 1:
            this->max_enemy_number = 10;
            break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            std::cout << "[DEBUG] Mappa " << map << " non ancora implementata.\n";
            return;
        default:
            std::cerr << "[ERRORE] Numero di mappa non valido: " << map << "\n";
            return;
    }

    if (this->can_be_walked.empty() || this->can_be_walked[0].empty()) {
        std::cerr << "[ERRORE] Mappa non inizializzata correttamente (can_be_walked vuota).\n";
        return;
    }

    std::cout << "[DEBUG] Dimensioni mappa: " << map_width << "x" << map_height << "\n";

    this->enemy_type_generator = std::uniform_int_distribution<int>(0, 10);  // tipo da 0 a 10 inclusi

    for (int i = 0; i < this->max_enemy_number; i++) {
        int x = -1, y = -1;
        int attempts = 0;
        const int max_attempts = 100;

        do {
            x = this->enemy_x_coord_generator(gen);
            y = this->enemy_y_coord_genetator(gen);
            attempts++;

            if (x < 0 || x >= map_width || y < 0 || y >= map_height) {
                std::cerr << "[ERRORE] Coordinate fuori dai limiti generate: x=" << x << ", y=" << y << "\n";
            } else if (this->can_be_walked[y][x] != 0) {
                std::cout << "[DEBUG] Coordinate occupate o invalide: (" << x << "," << y << ") = "
                          << this->can_be_walked[y][x] << "\n";
            }

            if (attempts >= max_attempts) {
                std::cerr << "[ERRORE] Troppi tentativi falliti per trovare coordinate valide.\n";
                return;
            }

        } while (x < 0 || y < 0 || x >= map_width || y >= map_height || this->can_be_walked[y][x] != 0);

        int enemy_type = this->enemy_type_generator(gen);
        std::cout << "[DEBUG] Nemico #" << i << ": tipo=" << enemy_type << ", pos=(" << x << "," << y << ")\n";

        if (enemy_type >= 0 && enemy_type < 4) {
            std::cout << "[DEBUG] -> Zombie\n";
            this->enemies_map[ZOMBIES].push_back(new Zombie(x, y));
        } else if (enemy_type >= 4 && enemy_type < 7) {
            std::cout << "[DEBUG] -> Knight\n";
            this->enemies_map[KNIGHTS].push_back(new Knight(x, y));
        } else if (enemy_type >= 7 && enemy_type < 9) {
            std::cout << "[DEBUG] -> Skeleton\n";
            this->enemies_map[SKELETONS].push_back(new Skeleton(x, y));
        } else if (enemy_type >= 9 && enemy_type <= 10) {
            std::cout << "[DEBUG] -> Mage\n";
            this->enemies_map[MAGES].push_back(new Mage(x, y));
        } else {
            std::cerr << "[ERRORE] Tipo nemico sconosciuto: " << enemy_type << "\n";
        }
    }

    std::cout << "[DEBUG] Nemici generati correttamente.\n";
}


void Enemy_manager::update_enemies_type(std::vector<Enemy*> &vec, int x, int y, SDL_Renderer* renderer) {
    for ( int i = 0 ; i<vec.size(); i++) {
        vec.at(i)->move(x, y);
        vec.at(i)->update(renderer);
    }
}


void Enemy_manager::print_enemies(SDL_Renderer* renderer, int x, int y) {
    threads.clear(); // Se li riusi ogni frame

    for (auto& [key, vec] : this->enemies_map) {
        threads.emplace_back(&Enemy_manager::update_enemies_type, this, std::ref(vec), x, y, renderer);
    }

    for (auto& t : threads) {
        t.join();
    }

}


