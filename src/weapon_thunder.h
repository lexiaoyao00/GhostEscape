#ifndef WEAPON_THUNDER_H
#define WEAPON_THUNDER_H

#include "raw/weapon.h"

class WeaponThunder : public Weapon
{

public:
    static WeaponThunder* addWeaponThunderChild(Actor* actor, float cool_down_, float mana_cost_);
    virtual void handleEvents(SDL_Event& event) override;
};




#endif // WEAPON_THUNDER_H