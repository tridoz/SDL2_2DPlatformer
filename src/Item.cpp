//
// Created by trida on 2/1/25.
//

#include "Item.h"
//ITEM CLASS
Item::Item() {
    this->src_rect = {0, 0, 0 ,0};
    this->dest_rect = {0, 0, 0 ,0};
    this->icon_texture = NULL;
    this->animation_textures.resize(0);
}

void Item::setAsSpell() {
    this->physical_resistance = 0;
    this->fire_resistance = 0;
    this->ice_resistance = 0;
    this->shock_resistance = 0;
    this->holy_resistance = 0;
    this->chaos_resistance = 0;

    this->critical_damage_buff = 0;
    this->critical_chance_buff = 0;
    this->attack_speed_buff = 0;
    this->resources_cost_buff = 0;
    this->recovery_time_buff = 0;
    this->weigth = 0;
    this->poise = 0;

    this->vigor = 0;
    this->mind = 0;
    this->endurance = 0;
    this->strength = 0;
    this->dexterity = 0;
    this->intelligence = 0;
    this->faith = 0;
    this->arcane = 0;

    this->physical_damage_buff = 0;
    this->fire_damage_buff = 0;
    this->ice_damage_buff = 0;
    this->shock_damage_buff = 0;
    this->holy_damage_buff = 0;
    this->chaos_damage_buff = 0;
}

void Item::setAsArmorPiece() {
    this->physical_damage  = 0;
    this->fire_damage = 0;
    this->ice_damage = 0;
    this->shock_damage = 0;
    this->holy_damage = 0;
    this->chaos_damage = 0;

    this->casting_time = 0;
    this->recovery_time = 0;
    this->health_cost = 0;
    this->mana_cost = 0;
}

SDL_Rect* Item::getSrcRect() {
    return &this->src_rect;
}

SDL_Rect* Item::getDestRect() {
    return &this->dest_rect;
}

SDL_Texture* Item::getIconTexture() {
    return this->icon_texture;
}

std::vector<SDL_Texture*>* Item::getAnimationTextures() {
    return &this->animation_textures;
}


//ARMORPIECE CLASS
ArmorPiece::ArmorPiece() {
    this->setAsArmorPiece();
}


//SPELL CLASS
Spell::Spell() {
    this->setAsSpell();
}



