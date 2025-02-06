#ifndef INVENTORY_H
#define INVENTORY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <vector>
#include <iostream>

class Inventory {



    SDL_Rect background;

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
