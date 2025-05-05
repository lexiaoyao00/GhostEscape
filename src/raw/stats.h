#ifndef STATUS_H
#define STATUS_H

#include "../core/actor.h"


class Stats : public Object
{
protected:
    Actor* parent_ = nullptr;
    float health_ = 100.0f;
    float max_health_ = 100.0f;
    float mana_ = 100.0f;
    float max_mana_ = 100.0f;
    float mana_regen_ = 40.0f;
    float damage_ = 40.0f;


    bool is_alive_ = true;
    bool is_invincible_ = false;
    float invincible_time_ = 1.5f;
    float invincible_timer_ = 0.0f;

public:
    static Stats* addStatsChild(Actor* parent, float max_health = 100.0f, float max_mana = 100.0f, float mana_regen = 40.0f, float damage = 40.0f);
    virtual void update(float dt) override;

    bool canUseMana(float mana_cost);
    void useMana(float mana_cost);
    void regenMana(float dt);
    void takeDamage(float damage);

    // getters and setters
    Actor* getParent() const { return parent_; }
    float getHealth() const { return health_; }
    float getMaxHealth() const { return max_health_; }
    float getMana() const { return mana_; }
    float getMaxMana() const { return max_mana_; }
    float getManaRegen() const { return mana_regen_; }
    float getDamage() const { return damage_; }
    bool isAlive() const { return is_alive_; }
    bool isInvincible() const { return is_invincible_; }
    float getInvincibleTime() const { return invincible_time_; }

    void setParent(Actor* parent) { this->parent_ = parent; }
    void setHealth(float health) { health_ = health; }
    void setMaxHealth(float max_health) { max_health_ = max_health; }
    void setMana(float mana) { mana_ = mana; }
    void setMaxMana(float max_mana) { max_mana_ = max_mana; }
    void setManaRegen(float mana_regen) { mana_regen_ = mana_regen; }
    void setDamage(float damage) { damage_ = damage; }
    void setAlive(bool alive) { is_alive_ = alive; }
    void setInvincible(bool invincible) { is_invincible_ = invincible; }
    void setInvincibleTime(float invincible_time) { invincible_time_ = invincible_time; }

};



#endif // STATUS_H