#include "actor.h"
#include "scene.h"
#include "../raw/stats.h"
#include "../affiliate/affiliate_bar.h"

void Actor::move(float dt)
{
    setPosition(position_ + velocity_ * dt);
    position_ = glm::clamp(position_, glm::vec2(0.0f), game_.getCurrentScene()->getWorldSize());
}

void Actor::updateHealthBar()
{
    if (!stats_ || !health_bar_) return;
    health_bar_->setPercentage(stats_->getHealth() / stats_->getMaxHealth());
}

void Actor::update(float dt)
{
    ObjectWorld::update(dt);
    updateHealthBar();
}

void Actor::takeDamage(float damage)
{
    if (!stats_) return;
    stats_->takeDamage(damage);
}

bool Actor::getAlive() const
{
    if (!stats_) return true;
    return stats_->getAlive();
}
