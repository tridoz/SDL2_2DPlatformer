//
// Created by trida on 8/3/25.
//

#ifndef MAGE_H
#define MAGE_H
#include "../Enemy.h"


class Mage: public Enemy {
public:
    Mage();
    Mage(int x, int y):Enemy(x, y) {
        this->red = 255;
        this->green = 0;
        this->blue = 0;
    };
};



#endif //MAGE_H
