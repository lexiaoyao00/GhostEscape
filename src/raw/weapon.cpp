#include "weapon.h"
#include "../core/actor.h"
#include "../world/spell.h"
#include "stats.h"
#include "../core/scene.h"

void Weapon::update(float dt)
{
    Object::update(dt);

    cooldown_timer_ += dt;
}

void Weapon::attack(glm::vec2 position,Spell *spell)
{
    if (spell == nullptr) return;
    parent_->getStats()->useMana(mana_cost_);
    cooldown_timer_ = 0.0f;
    spell->setPosition(position);
    game_.getCurrentScene()->safeAddChild(spell);
}

bool Weapon::canAttack()
{
    if (cooldown_timer_ < cooldown_) return false;
    if (!parent_->getStats()->canUseMana(mana_cost_)) return false;

    return true;
}
