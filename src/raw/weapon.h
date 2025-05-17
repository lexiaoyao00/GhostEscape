#ifndef WEAPON_H
#define WEAPON_H

#include "../core/object.h"

class Spell;
class Actor;
class Weapon : public Object
{
protected:
    Actor *parent_ = nullptr;
    float cooldown_ = 1.0f;
    float mana_cost_ = 0.0f;
    float cooldown_timer_ = 0.0f;

public:
    virtual void update(float dt) override;

    void attack(glm::vec2 position,Spell *spell);   // 确保调用了这个函数的时候,一定执行了attack()
    bool canAttack();
    // getters and setters
    void setParent(Actor *parent) { parent_ = parent; }
    Actor *getParent() { return parent_; }

    void setCooldown(float cooldown) { cooldown_ = cooldown; }
    float getCooldown() { return cooldown_; }

    void setManaCost(float mana_cost) { mana_cost_ = mana_cost; }
    float getManaCost() { return mana_cost_; }
};

#endif // WEAPON_H