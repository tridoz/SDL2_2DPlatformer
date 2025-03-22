#ifndef ITEM_H
#define ITEM_H

#include <SDL2/SDL.h>

#include <vector>

class Item {
protected:

    SDL_Rect src_rect;
    SDL_Rect dest_rect;

    SDL_Texture* icon_texture;

    std::vector<SDL_Texture*> animation_textures{10, nullptr};


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
    [[nodiscard]] SDL_Texture* getIconTexture() const;
    std::vector<SDL_Texture*>* getAnimationTextures();
};

class ArmorPiece: public Item {
    public:
    ArmorPiece();
    [[nodiscard]] float getPhysicalResistance() const;
    [[nodiscard]] float getFireResistance() const;
    [[nodiscard]] float getIceResistance() const;
    [[nodiscard]] float getShockResistance() const;
    [[nodiscard]] float getHolyResistance() const;
    [[nodiscard]] float getChaosResistance() const;

    [[nodiscard]] float getCriticalDamageBuff() const;
    [[nodiscard]] float getCriticalChanceBuff() const;
    [[nodiscard]] float getAttackSpeedBuff() const;
    [[nodiscard]] float getResourcesCostBuff() const;
    [[nodiscard]] float getRecoveryTimeBuff() const;

    [[nodiscard]] float getWeight() const;
    [[nodiscard]] float getPoise() const;

    [[nodiscard]] float getVigor() const;
    [[nodiscard]] float getMind() const;
    [[nodiscard]] float getEndurance() const;
    [[nodiscard]] float getStrength() const;
    [[nodiscard]] float getDexterity() const;
    [[nodiscard]] float getIntelligence() const;
    [[nodiscard]] float getFaith() const;
    [[nodiscard]] float getArcane() const;

    [[nodiscard]] float getPhysicalDamageBuff() const;
    [[nodiscard]] float getFireDamageBuff() const;
    [[nodiscard]] float getIceDamageBuff() const;
    [[nodiscard]] float getShockDamageBuff() const;
    [[nodiscard]] float getHolyDamageBuff() const;
    [[nodiscard]]float getChaosDamageBuff() const;

    
};

class Spell: public Item {
    public:
    Spell();
    [[nodiscard]] float getPhysicalDamage() const;
    [[nodiscard]] float getFireDamage() const;
    [[nodiscard]] float getIceDamage() const;
    [[nodiscard]] float getShockDamage() const;
    [[nodiscard]] float getHolyDamage() const;
    [[nodiscard]] float getChaosDamage() const;

    [[nodiscard]] float getCastingTime() const;
    [[nodiscard]] float getRecoveryTime() const;
    [[nodiscard]] float getHealthCost() const;
    [[nodiscard]] float getManaCost() const;
};



#endif //ITEM_H
