//
// Created by trida on 8/3/25.
//

#ifndef SKELETON_H
#define SKELETON_H
#include "../Enemy.h"


class Skeleton: public Enemy {
public:
    Skeleton();
    Skeleton(int x, int y):Enemy(x, y) {
        this->red = 255;
        this->green = 255;
        this->blue = 255;
    };
};



#endif //SKELETON_H
