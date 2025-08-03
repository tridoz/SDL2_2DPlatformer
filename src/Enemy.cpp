//
// Created by trida on 8/2/25.
//

#include "Enemy.h"

Enemy::Enemy(int x, int y) {
    this->sprite_rect = {x, y-44, 40, 64};

    this->nextX = this->sprite_rect.x + (this->sprite_rect.w / 2.0f);
    this->nextY = this->sprite_rect.y + (this->sprite_rect.h / 2.0f);

    this->currentX = this->sprite_rect.x + (this->sprite_rect.w / 2.0f);
    this->currentY = this->sprite_rect.y + (this->sprite_rect.h / 2.0f);

    this->running = true;

    this->lastFrameTime = 0;
    this->frameDelay = 75;

    this->current_state = ENEMY_STATUS::IDLE;

    this->currentX = 0;
    this->currentY = 0;
    this->nextX = 0;
    this->nextY = 0;

    this->speed = 1.62f;
    this->dx = 0.0f;
    this->dy = 0.0f;
    this->movement_angle = 0.0f;
    this->animation_index = 0;
    this->direction = 3;
}




void Enemy::move(int x, int y) {

    this->nextX = x;
    this->nextY = y;

    double distanceX = this->nextX - this->currentX;
    double distanceY = this->nextY - this->currentY;

    this->movement_angle = atan2(distanceY, distanceX);
    double degree = this->movement_angle * 180 / M_PI;

    if ( degree > -45 && degree <= 45 ) {
        this->direction = 2;
    }else if ( degree > 45 && degree <= 135) {
        this->direction = 3;
    }else if ( degree > -135 && degree <= -45) {
        this->direction = 1;
    }else {
        this->direction = 4;
    }

}

void Enemy::updateAnimationFrame(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, this->red, this->green, this->blue, 255);
    SDL_RenderDrawRect(renderer, &this->sprite_rect);
}



void Enemy::update(SDL_Renderer *renderer) {
    double distanceX = std::abs(this->currentX - this->nextX);
    double distanceY = std::abs(this->currentY - this->nextY);
    double distance = sqrt(distanceX * distanceX + distanceY * distanceY);

    if (distance >= this->speed) {

        this->current_state = ENEMY_STATUS::RUN;
        double dx = this->speed * cos(this->movement_angle);
        double dy = this->speed * sin(this->movement_angle);

        this->currentX += dx;
        this->currentY += dy;

    }else {

        this->current_state = ENEMY_STATUS::IDLE;
    }

    this->sprite_rect.x = this->currentX - this->sprite_rect.w / 2.0f;
    this->sprite_rect.y = this->currentY - this->sprite_rect.h / 2.0f;

    this->updateAnimationFrame( renderer );
}

bool Enemy::isAtDestination() const {
    double distanceX = std::abs(this->currentX - this->nextX);
    double distanceY = std::abs(this->currentY - this->nextY);
    double distance = sqrt(distanceX * distanceX + distanceY * distanceY);

    return distance <= this->speed;
}

