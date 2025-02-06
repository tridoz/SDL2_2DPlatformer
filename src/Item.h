#ifndef ITEM_H
#define ITEM_H

#include <SDL2/SDL.h>

#include <vector>

class Item {
protected:

    SDL_Rect src_rect;
    SDL_Rect dest_rect;
    SDL_Texture* icon_texture;

    std::vector<SDL_Texture*> animation_textures;

    //SPELLS
    float physical_damage;
    float fire_damage;
    float ice_damage;
    float shock_damage;
    float holy_damage;
    float chaos_damage;

    float casting_time;
    float recovery_time;
    float health_cost;
    float mana_cost;

    //ARMOR PIECE
    float physical_resistance;
    float fire_resistance;
    float ice_resistance;
    float shock_resistance;
    float holy_resistance;
    float chaos_resistance;

    float critical_damage_buff;
    float critical_chance_buff;
    float attack_speed_buff;
    float resources_cost_buff;
    float recovery_time_buff;
    
    float weigth;
    float poise;

    float vigor;
    float mind;
    float endurance;
    float strength;
    float dexterity;
    float intelligence;
    float faith;
    float arcane;

    float physical_damage_buff;
    float fire_damage_buff;
    float ice_damage_buff;
    float shock_damage_buff;
    float holy_damage_buff;
    float chaos_damage_buff;

public:
    Item();
    ~Item();
    void setAsArmorPiece();
    void setAsSpell();

    SDL_Rect *getSrcRect();
    SDL_Rect *getDestRect();
    SDL_Texture* getIconTexture();
    std::vector<SDL_Texture*>* getAnimationTextures();
};

class ArmorPiece: public Item {
    public:
    ArmorPiece();
    float getPhysicalResistance();
    float getFireResistance();
    float getIceResistance();
    float getShockResistance();
    float getHolyResistance();
    float getChaosResistance();

    float getCriticalDamageBuff();
    float getCriticalChanceBuff();
    float getAttackSpeedBuff();
    float getResourcesCostBuff();
    float getRecoveryTimeBuff();

    float getWeigth();
    float getPoise();

    float getVigor();
    float getMind();
    float getEndurance();
    float getStrength();
    float getDexterity();
    float getIntelligence();
    float getFaith();
    float getArcane();

    float getPhysicalDamageBuff();
    float getFireDamageBuff();
    float getIceDamageBuff();
    float getShockDamageBuff();
    float getHolyDamageBuff();
    float getChaosDamageBuff();

    
};

class Spell: public Item {
    public:
    Spell();
};


#endif //ITEM_H
