//
// Created by trida on 8/3/25.
//

#ifndef KNIGHT_H
#define KNIGHT_H
#include "../Enemy.h"


class Knight: public Enemy {
public:
    Knight();
    Knight(int x, int y):Enemy(x, y) {
        this->red = 0;
        this->green = 0;
        this->blue = 255;
    };

};



#endif //KNIGHT_H
