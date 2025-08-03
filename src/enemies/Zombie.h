//
// Created by trida on 8/3/25.
//

#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "../Enemy.h"


class Zombie: public Enemy {
public:
    Zombie();
    Zombie(int x, int y):Enemy(x, y) {
        this->red = 0;
        this->green = 255;
        this->blue = 0;
    };
};



#endif //ZOMBIE_H
