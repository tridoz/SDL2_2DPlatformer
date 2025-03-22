#ifndef INVENTORY_H
#define INVENTORY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <vector>
#include <iostream>
#include <pugixml.hpp>

#include "Item.h"


class Inventory {

    SDL_Rect background;

    std::vector<Spell> spells;
    std::vector<ArmorPiece> equippedArmors;
    std::vector<Item> InventoryItems;

    const int max_equipable_spells = 6;
    const int max_equipable_armors = 11;
    const int capacity = 70;

    int equipped_spells;
    int equipped_armors;
    int inventory_item;

    int starting_x_item;
    int starting_y_item;

    int margin_x_item;
    int margin_y_item;

    int border_size;
    int icon_size;
    int border_icon_diff;

public:

    Inventory();
    void load(SDL_Renderer* renderer);

    void render_inventory( SDL_Renderer* renderer );


};



#endif //INVENTORY_H
