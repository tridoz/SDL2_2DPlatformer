//
// Created by trida on 2/1/25.
//

#include "Item.h"
//ITEM CLASS
Item::Item() {
    this->src_rect = {0, 0, 0 ,0};
    this->dest_rect = {0, 0, 0 ,0};
    this->icon_texture = nullptr;
    this->animation_textures.resize(0);
    this->setAsSpell();
    this->setAsArmorPiece();
}

Item::~Item() {
    this->animation_textures.clear();
    this->icon_texture = nullptr;
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

SDL_Texture* Item::getIconTexture() const {
    return this->icon_texture;
}

std::vector<SDL_Texture*>* Item::getAnimationTextures() {
    return &this->animation_textures;
}


//ARMOR PIECE CLASS
ArmorPiece::ArmorPiece() {
    this->setAsArmorPiece();
}

float ArmorPiece::getPhysicalResistance() const {
    return this->physical_resistance;
}

float ArmorPiece::getFireResistance() const {
    return this->fire_resistance;
}

float ArmorPiece::getIceResistance() const {
    return this->ice_resistance;
}

float ArmorPiece::getShockResistance() const {
    return this->shock_resistance;
}

float ArmorPiece::getHolyResistance() const {
    return this->holy_resistance;
}

float ArmorPiece::getChaosResistance() const {
    return this->chaos_resistance;
}

float ArmorPiece::getCriticalDamageBuff() const {
    return this->critical_damage_buff;
}

float ArmorPiece::getCriticalChanceBuff() const {
    return this->critical_chance_buff;
}

float ArmorPiece::getAttackSpeedBuff () const {
    return this->attack_speed_buff;
}

float ArmorPiece::getResourcesCostBuff() const {
    return this->resources_cost_buff;
}

float ArmorPiece::getRecoveryTimeBuff() const {
    return this->recovery_time_buff;
}

float ArmorPiece::getWeight() const {
    return this->weigth;
}

float ArmorPiece::getPoise() const {
    return this->poise;
}

float ArmorPiece::getVigor() const {
    return this->vigor;
}

float ArmorPiece::getMind() const {
    return this->mind;
}

float ArmorPiece::getEndurance() const {
    return this->endurance;
}

float ArmorPiece::getStrength() const {
    return this->strength;
}

float ArmorPiece::getDexterity() const {
    return this->dexterity;
}

float ArmorPiece::getIntelligence() const {
    return this->intelligence;
}

float ArmorPiece::getFaith() const {
    return this->faith;
}

float ArmorPiece::getArcane() const {
    return this->arcane;
}

float ArmorPiece::getPhysicalDamageBuff() const {
    return this->physical_damage_buff;
}

float ArmorPiece::getFireDamageBuff() const {
    return this->fire_damage_buff;
}

float ArmorPiece::getIceDamageBuff() const {
    return this->ice_damage_buff;
}

float ArmorPiece::getShockDamageBuff() const {
    return this->shock_damage_buff;
}

float ArmorPiece::getHolyDamageBuff() const {
    return this->holy_damage_buff;
}

float ArmorPiece::getChaosDamageBuff() const {
    return this->chaos_damage_buff;
}





//SPELL CLASS
Spell::Spell() {
    this->setAsSpell();
}

float Spell::getPhysicalDamage() const {
    return this->physical_damage;
}

float Spell::getFireDamage() const {
    return this->fire_damage;
}

float Spell::getIceDamage() const {
    return this->ice_damage;
}

float Spell::getShockDamage() const {
    return this->shock_damage;
}

float Spell::getHolyDamage() const {
    return this->holy_damage;
}

float Spell::getChaosDamage() const {
    return this->chaos_damage;
}

float Spell::getCastingTime() const {
    return this->casting_time;
}

float Spell::getRecoveryTime() const {
    return this->recovery_time;
}

float Spell::getHealthCost() const {
    return this->health_cost;
}

float Spell::getManaCost() const {
    return this->mana_cost;
}




