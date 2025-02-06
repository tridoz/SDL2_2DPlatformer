#include "Game_Engine.h"

Game_Engine::Game_Engine() {
    this->title = "Game Engine";
    this->game_width = 800;
    this->game_height = 800;
}

Game_Engine::Game_Engine(const std::string &title, const int width, const int height) {
    this->title = title;
    this->game_width = width;
    this->game_height = height;
}

Game_Engine::~Game_Engine() {

    if ( this->game_renderer != nullptr ) {
        SDL_DestroyRenderer(this->game_renderer);
    }

    if ( this->game_window != nullptr ) {
        SDL_DestroyWindow(this->game_window);
    }

}

bool Game_Engine::Init() {

    SDL_SetRenderDrawBlendMode( this->game_renderer, SDL_BLENDMODE_BLEND);

    if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        this->error_message = SDL_GetError();
        this->what_exploded = "SDL_Init";
        this->error_occurred = true;
        this->game_running = false;
        SDL_Quit();
        return false;
    }
    std::cout<<"SDL initialized correctly"<<std::endl;

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        this->error_message = SDL_GetError();
        this->what_exploded = "IMG_Init";
        this->error_occurred = true;
        this->game_running = false;
        SDL_Quit();
        return false;
    }
    std::cout<<"SDL_image initialized correctly"<<std::endl;

    if ( TTF_Init() == -1 ) {
        this->error_message = TTF_GetError();
        this->what_exploded = "TTF_Init";
        this->error_occurred = true;
        this->game_running = false;
        return false;
    }
    std::cout<<"SDL_ttf initialized correctly"<<std::endl;

    this->game_window = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->game_width, this->game_height, SDL_WINDOW_SHOWN);
    if ( !this->game_window ) {
        this->error_message = SDL_GetError();
        this->what_exploded = "SDL_CreateWindow (game window)";
        this->error_occurred = true;
        this->game_running = false;
        SDL_Quit();
        return false;
    }
    std::cout<<"game_window created correctly"<<std::endl;

    this->game_renderer = SDL_CreateRenderer(this->game_window, -1, SDL_RENDERER_ACCELERATED);
    if ( !this->game_renderer ) {
        this->error_message = SDL_GetError();
        this->what_exploded = "SDL_CreateRenderer (game renderer)";
        this->error_occurred = true;
        this->game_running = false;
        SDL_DestroyWindow(this->game_window);
        SDL_Quit();
        return false;
    }
    std::cout<<"game_renderer created correctly"<<std::endl;

    std::pair< bool, std::pair<std::string, std::string> > player_animation_output = this->player.loadAnimations();
    if ( !player_animation_output.first ) {
        this->error_message = player_animation_output.second.second;
        this->what_exploded = player_animation_output.second.first;
        this->error_occurred = true;
        this->game_running = false;
        SDL_DestroyWindow(this->game_window);
        SDL_DestroyRenderer(this->game_renderer);
        SDL_Quit();
        return false;
    }


    this->game_running = true;
    return true;

}

std::string Game_Engine::getErrorMessage() {
    return this->error_message;
}

std::string Game_Engine::getErrorCause() {
    return this->what_exploded;
}

bool Game_Engine::isRunning() const {
    return this->game_running;;
}

bool Game_Engine::errorHasOccurred() const {
    return this->error_occurred;
}

void Game_Engine::run() {

    this->player.spawn(400, 400);
    this->player.getInventory()->load( this->game_renderer );

    std::cout << "Running Game Engine" << std::endl;

    while (this->game_running) {

        SDL_RenderClear(this->game_renderer);

        if ( this->player_map != this->player_previous_map ) {
            this -> loadTextures();
            this->player_previous_map = this->player_map;
        }

        if ( this->player_level != this->player_previous_level ) {

            if ( this->player.isAtDestination() == true ) {

                this->player.setX( this->new_player_x );
                this->player.setY( this->new_player_y );
                this->loadLevel();
                this->player_previous_level = this->player_level;
            }

        }

        if ( this->inventory_displayed == false ) {
            this->renderLevel();
            this->player.update( this->game_renderer );
        }else if ( this->inventory_displayed == true ) {
            this->player.getInventory()->render_inventory( this->game_renderer );
        }

        SDL_RenderPresent(this->game_renderer);

        while (SDL_PollEvent(&this->game_event)) {

            if (this->game_event.type == SDL_QUIT) {

                this->game_running = false;

            }

            if (this->game_event.type == SDL_MOUSEBUTTONDOWN) {

                if (this->game_event.button.button == SDL_BUTTON_LEFT) {

                    int index_x = floor( game_event.button.x / 64  );
                    int index_y = floor( game_event.button.y / 64  );

                    if ( this->can_be_walked[ index_y ][ index_x ] != -1 ) {

                        this->player.move(this->game_event.button.x, this->game_event.button.y);

                        if ( this->can_be_walked[ index_y ][ index_x ] != 0 ) {
                            this->player_level = this->can_be_walked[ index_y ][ index_x ];
                            if ( index_x == 0 || index_x == 23) {
                                this->new_player_y =  64 *  index_y  + 32;
                                if ( index_x == 0)
                                    this->new_player_x = ( 64 * ( 22  ) + 32 );
                                else
                                    this->new_player_x =  96;

                            }else if (index_y == 0 || index_y == 15) {

                                this->new_player_x = 64 * index_x + 32;
                                if ( index_y == 0)
                                    this->new_player_y = ( 64 * ( 14  ) + 32 );
                                else
                                    this->new_player_y =  96;
                            }
                        }

                    }

                }

            }else if ( this->game_event.type == SDL_KEYDOWN ) {
                if (this->game_event.key.keysym.scancode == SDL_SCANCODE_I) {
                    this->inventory_displayed = !inventory_displayed;
                }else if (this->game_event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    if ( this->inventory_displayed == true ) {
                        this->inventory_displayed = false;
                    }
                }
            }

        }

         this->frame_counter.update();

        if (this->frame_counter.getFPS() > 0) {

            std::cout << "FPS: " << this->frame_counter.getFPS() << "\r" << std::flush;

        }


        usleep(this->frame_duration);

    }

    std::cout << "QUITTING GAME" << std::endl;

}

void Game_Engine::loadTextures( ) {

    std::string main_file_path = "../Assets/Maps/Map" + std::to_string( this->player_map ) + "/all_textures.txt";
    std::ifstream textures( main_file_path );

    if ( !textures ) {
        this->error_message = "Could not open map file " + main_file_path;
        this->error_occurred = false;
        this->what_exploded = "Game_Engine::loadTextures()";
        this->game_running = false;
        SDL_Quit();
        return;
    }

    std::string line;
    while ( std::getline(textures, line) ) {
        std::string filepath = "../Assets/Maps/Map" + std::to_string( this->player_map ) + "/Textures/" + line;
        SDL_Texture *texture = IMG_LoadTexture( this->game_renderer, filepath.c_str( ) );
        if ( !texture ) {
            this->error_message = "Could not load texture " + filepath;
        }
        this->tile_textures.push_back( texture );
    }

    std::cout<<"Textures Loaded"<<std::endl;

}

void Game_Engine::loadLevel() {

    std::string walkpath = "../Assets/Maps/Map" + std::to_string(this->player_map) + "/Level" + std::to_string(this->player_level) + "/Walkable_Map.txt";
    std::string texturepath = "../Assets/Maps/Map" + std::to_string(this->player_map) + "/Level" + std::to_string(this->player_level) + "/Texture_Map.txt";

    std::ifstream walk_file( walkpath );
    std::ifstream texture_file( texturepath );

    if ( !walk_file || !texture_file ) {
        this->what_exploded = "Game_Engine::loadlevel";
        this->error_message = "couldn't open file [" + walkpath + "] or file [" + texturepath + "]";
        this->error_occurred = true;
        this->game_running = false;
        SDL_Quit();
        IMG_Quit();
        return;
    }

    for (auto & cell : this->can_be_walked) {
        cell.clear();
    }
    this->can_be_walked.clear();

    for (auto & texture : this->textures) {
        texture.clear();
    }
    this->textures.clear();

    std::string line;

    while ( std::getline( walk_file, line ) ) {
        std::istringstream ss( line );
        int value;
        std::vector<int> row;
        while ( ss >> value ) {
            row.push_back(value);
        }
        this->can_be_walked.push_back(row);
    }

    while ( std::getline( texture_file, line ) ) {
        std::istringstream ss( line );
        char delimiter = ' ';
        std::vector<std::pair<int, int> > row;

        while ( std::getline( ss, line, delimiter) ) {
            int file_index, texture_position;
            sscanf( line.c_str(), "(%d,%d)", &file_index, &texture_position );
            row.emplace_back(file_index, texture_position );
        }

        this->textures.push_back( row );

    }

}

void Game_Engine::renderLevel() {

    this->tiles.clear();

    for ( int i = 0 ; i<this->textures.size() ; i++) {
        for ( int j = 0 ; j<this->textures[i].size() ; j++ ) {

            int f = this->textures[i][j].first;
            int s = this->textures[i][j].second;

            SDL_Rect srcRect = {0, 45*s, 45, 45};
            SDL_Rect dstRect = {64*j, 64*i, 64, 64};

            this->tiles.push_back( dstRect );

            SDL_RenderCopy( this->game_renderer, this->tile_textures[f], &srcRect, &dstRect );

        }

    }

}
