#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <unistd.h>

#include <string>
#include <iostream>
#include <thread>
#include <algorithm>

#include "Player.h"
#include "FPSCounter.h"

class Game_Engine {

private:

    //CUSTOM PARAMETERS
    Player player;
    FPSCounter frame_counter;

    int player_level = 1;
    int player_previous_level = 0;
    int player_new_level = 1;

    int player_map = 1;
    int player_previous_map = 0;
    int player_new_map = 1;

    int new_player_x = 400;
    int new_player_y = 400;

    //SDL2 PARAMETERS
    SDL_Window* game_window{};
    SDL_Renderer* game_renderer{};


    std::vector<SDL_Rect> tiles{}; // tutti i rettangoli

    std::vector<std::vector<int>>  can_be_walked; //sapere se posso andare oppure no
    std::vector<std::vector< std::pair<int, int> > >  textures; //dove vanno inserite tutte le texture
    std::vector< SDL_Texture*>  tile_textures{}; //le texture effettive

    SDL_Event game_event{};

    //SDL2 WINDOW PARAMETERS
    std::string title;
    int game_width, game_height;

    //CONST FILEPATH FOR FONTS, SPRITES AND OTHER THINGS
    const int frame_rate = 200;
    const unsigned int frame_duration = (1000000 / this->frame_rate );
    const unsigned int tile_width = 64;
    const unsigned int tile_height = 64;

    //CONTROL PARAMETERS
    bool game_running = false;
    bool error_occurred = false;
    bool inventory_displayed = false;
    std::string error_message;
    std::string what_exploded;

    void renderLevel( );
    void loadTextures();
    void loadLevel();
    void saveMaps();

public:

    Game_Engine();
    Game_Engine( const std::string &title, int width, int height );
    ~Game_Engine();

    bool Init();
    void run();




    [[nodiscard]] bool isRunning() const;
    [[nodiscard]] bool errorHasOccurred() const;
    std::string getErrorMessage();
    std::string getErrorCause();

};



#endif
