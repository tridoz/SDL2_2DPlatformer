#include <iostream>
#include <ostream>

#include "src/Game_Engine.h"

int main(int argc, char** argv) {
    Game_Engine game_engine("Game", 1536, 1024);
    //ciao
    game_engine.Init();

    if ( game_engine.errorHasOccurred() ) {
        std::cout<<"Cause< "<<game_engine.getErrorCause()<<" >"<<std::endl;
        std::cout<<"Error< "<<game_engine.getErrorMessage()<<" >"<<std::endl;
        return 10;
    }

    game_engine.run();

    if ( game_engine.errorHasOccurred() ) {
        std::cout<<"Cause< "<<game_engine.getErrorCause()<<" >"<<std::endl;
        std::cout<<"Error< "<<game_engine.getErrorMessage()<<" >"<<std::endl;
        return -1;
    }

    return 0;
}