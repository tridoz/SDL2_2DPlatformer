#include "Player.h"
#include <cmath>
#include <iostream>

Player::Player() {
    
    this->running = true;

    this->lastFrameTime = 0;
    this->frameDelay = 75;

    this->current_state = IDLE;

    this->currentX = 0;
    this->currentY = 0;
    this->nextX = 0;
    this->nextY = 0;

    this->speed = 3.25f;
    this->dx = 0.0f;
    this->dy = 0.0f;
    this->movement_angle = 0.0f;
    this->animation_index = 0;
    this->direction = 3;
}


void Player::move(int x, int y) {

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

void Player::spawn(int x, int y) {

    this->sprite_rect = {x, y-44, 40, 64};

    this->nextX = this->sprite_rect.x + (this->sprite_rect.w / 2.0f);
    this->nextY = this->sprite_rect.y + (this->sprite_rect.h / 2.0f);

    this->currentX = this->sprite_rect.x + (this->sprite_rect.w / 2.0f);
    this->currentY = this->sprite_rect.y + (this->sprite_rect.h / 2.0f);

}

void Player::updateAnimationFrame(SDL_Renderer* renderer) {

    if (this->sprite == nullptr) {
        this->sprite = IMG_LoadTexture(renderer, "../Assets/Player/animations.png");
        if (!this->sprite) {
            std::cout << "Failed Texture Loading" << IMG_GetError() << std::endl;
            return;
        }
    }

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - this->lastFrameTime >= this->frameDelay) {
        this->animation_index++;
        this->lastFrameTime = currentTime;

        if (this->current_state == IDLE) {
            switch (this->direction) {
                case 1:  // up
                    this->animation_index %= this->up_idle.size();
                    break;
                case 2:  // right
                    this->animation_index %= this->right_idle.size();
                    break;
                case 3:  // down
                    this->animation_index %= this->down_idle.size();
                    break;
                case 4:  // left
                    this->animation_index %= this->left_idle.size();
                    break;
                default:
                    break;
            }
        }

        else if (this->current_state == RUN) {
            switch (this->direction) {
                case 1:  // up
                    this->animation_index %= this->up_run.size();
                    break;
                case 2:  // right
                    this->animation_index %= this->right_run.size();
                    break;
                case 3:  // down
                    this->animation_index %= this->down_run.size();
                    break;
                case 4:  // left
                    this->animation_index %= this->left_run.size();
                    break;
                default:
                    break;
            }
        }
    }

    SDL_Rect *srcRect = nullptr;
    switch (this->current_state) {
        case IDLE:
            switch (this->direction) {
                case 1:  // up
                    srcRect = &this->up_idle[this->animation_index % this->up_idle.size()];
                    break;
                case 2:  // right
                    srcRect = &this->right_idle[this->animation_index % this->right_idle.size()];
                    break;
                case 3:  // down
                    srcRect = &this->down_idle[this->animation_index % this->down_idle.size()];
                    break;
                case 4:  // left
                    srcRect = &this->left_idle[this->animation_index % this->left_idle.size()];
                    break;
                default:
                    break;
            }
            break;

        case RUN:
            switch (this->direction) {
                case 1:  // up
                    srcRect = &this->up_run[this->animation_index % this->up_run.size()];
                    break;
                case 2:  // right
                    srcRect = &this->right_run[this->animation_index % this->right_run.size()];
                    break;
                case 3:  // down
                    srcRect = &this->down_run[this->animation_index % this->down_run.size()];
                    break;
                case 4:  // left
                    srcRect = &this->left_run[this->animation_index % this->left_run.size()];
                    break;
                default:
                    break;
            }
            break;

        default:
            break;
    }

    if (srcRect != nullptr) {
        SDL_RenderCopy(renderer, this->sprite, srcRect, &this->sprite_rect);
    }
}



void Player::update(SDL_Renderer *renderer) {


    double distanceX = std::abs(this->currentX - this->nextX);
    double distanceY = std::abs(this->currentY - this->nextY);
    double distance = sqrt(distanceX * distanceX + distanceY * distanceY);

    if (distance >= this->speed) {

        this->current_state = RUN;
        double dx = this->speed * cos(this->movement_angle);
        double dy = this->speed * sin(this->movement_angle);

        this->currentX += dx;
        this->currentY += dy;

    }else {

        this->current_state = IDLE;
    }

    this->sprite_rect.x = this->currentX - this->sprite_rect.w / 2.0f;
    this->sprite_rect.y = this->currentY - this->sprite_rect.h / 2.0f;

    this->updateAnimationFrame( renderer );
}

bool Player::isAtDestination() const {

    double distanceX = std::abs(this->currentX - this->nextX);
    double distanceY = std::abs(this->currentY - this->nextY);
    double distance = sqrt(distanceX * distanceX + distanceY * distanceY);

    return distance <= this->speed;
}

std::pair< bool, std::pair<std::string, std::string> > Player::loadAnimations() {
    std::ifstream animationSheet("../Assets/Player/player_animation_sheet.txt");

    std::string line;
    std::string current_section;

    if ( !animationSheet ) {
        return std::make_pair(false, std::pair<std::string, std::string>("Player:loadAnimations", strerror( errno ) ) );
    }

    while (std::getline(animationSheet, line)) {

        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        if (line.empty()) continue;

        // Sezione per IDLE
        if (line == "IDLE DOWN:") {
            current_section = "down";
        } else if (line == "IDLE RIGHT:") {
            current_section = "right";
        } else if (line == "IDLE LEFT:") {
            current_section = "left";
        } else if (line == "IDLE UP:") {
            current_section = "up";
        }

        // Sezione per RUN
        else if (line == "RUN DOWN:") {
            current_section = "run_down";
        } else if (line == "RUN RIGHT:") {
            current_section = "run_right";
        } else if (line == "RUN LEFT:") {
            current_section = "run_left";
        } else if (line == "RUN UP:") {
            current_section = "run_up";
        } else {

            int x, y, w, h;
            if (sscanf(line.c_str(), "%d %d %d %d", &x, &y, &w, &h) == 4) {
                SDL_Rect rect = {x, y, w, h};

                // Aggiungi IDLE
                if (current_section == "down") {
                    down_idle.push_back(rect);
                } else if (current_section == "right") {
                    right_idle.push_back(rect);
                } else if (current_section == "left") {
                    left_idle.push_back(rect);
                } else if (current_section == "up") {
                    up_idle.push_back(rect);
                }

                // Aggiungi RUN
                else if (current_section == "run_down") {
                    down_run.push_back(rect);
                } else if (current_section == "run_right") {
                    right_run.push_back(rect);
                } else if (current_section == "run_left") {
                    left_run.push_back(rect);
                } else if (current_section == "run_up") {
                    up_run.push_back(rect);
                }
            }
        }
    }

    animationSheet.close();
    return std::make_pair(true, std::pair<std::string, std::string>() );
}


SDL_Rect *Player::getSprite() {
    return &this->sprite_rect;
}

double Player::getCurrentX() const {
    return this->currentX;
}

double Player::getCurrentY() const {
    return this->currentY;
}

void Player::setX(const double newX) {
    this->currentX = newX;
    this->nextX = this->currentX;
}

void Player::setY(const double newY) {
    this->currentY = newY;
    this->nextY = this->currentY;
}

Inventory* Player::getInventory() {
    return &this->inventory;
}







