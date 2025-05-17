#ifndef WEAPON_THUNDER_H
#define WEAPON_THUNDER_H

#include "raw/weapon.h"
#include "screen/hud_skill.h"

class WeaponThunder : public Weapon
{
protected:
    HUDSkill* hud_skill_ = nullptr;

public:
    virtual void init() override;
    virtual void update(float dt) override;

    static WeaponThunder* addWeaponThunderChild(Actor* actor, float cool_down_, float mana_cost_);
    virtual void handleEvents(SDL_Event& event) override;
};




#endif // WEAPON_THUNDER_H