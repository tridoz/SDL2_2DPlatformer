#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <cmath>

#include <vector>
#include <fstream>

#include "Inventory.h"

typedef enum {

    IDLE,
    RUN,
    ATTACK_PRIMARY,
    ATTACK_SECONDARY,
    ATTACK_SPECIAL_ONE,
    ATTACK_SPECIAL_TWO

} PLAYER_STATUS;


class Player {
private:
    // DRAW STUFF
    SDL_Texture* sprite{};
    SDL_Rect sprite_rect{};

    Inventory inventory;

    std::vector<SDL_Rect> down_idle{};
    std::vector<SDL_Rect> right_idle{};
    std::vector<SDL_Rect> up_idle{};
    std::vector<SDL_Rect> left_idle{};

    std::vector<SDL_Rect> down_run{};
    std::vector<SDL_Rect> right_run{};
    std::vector<SDL_Rect> up_run{};
    std::vector<SDL_Rect> left_run{};

    //STATS
    float nerves;
    float nerves_needed;


    float health;
    float mana;
    float stamina;

    float max_equip_load;

    float poise;
    float discovery;

    float vigor;
    float mind;
    float endurance;
    float strength;
    float dexterity;
    float intelligence;
    float faith;
    float arcane;
    
    float physical_damage;
    float fire_damage;
    float cold_damage;
    float shock_damage;
    float holy_damage;
    float chaos_damage;

    float physical_defense;
    float fire_defense;
    float cold_defense;
    float shock_defense;
    float holy_defense;
    float chaos_defense;

    //ANIMATION CONTROL
    Uint32 lastFrameTime;
    Uint32 frameDelay;

    // PLAYER CONTROL
    PLAYER_STATUS current_state;
    bool running;

    double currentX;
    double currentY;

    double nextX;
    double nextY;

    double speed;
    double dx;
    double dy;
    double movement_angle;
    int animation_index;
    int direction;

    void updateAnimationFrame(SDL_Renderer *renderer);

public:
    
    Player();

    void move(int x, int y);
    void update(SDL_Renderer* renderer);

    void spawn(int x, int y);
    std::pair< bool, std::pair<std::string, std::string> >  loadAnimations();

    SDL_Rect* getSprite();

    [[nodiscard]] bool isAtDestination() const;
    [[nodiscard]] double getCurrentX() const;
    [[nodiscard]] double getCurrentY() const;

    void setX(double newX);
    void setY(double newY);

    Inventory* getInventory();

};

#endif //PLAYER_H
