#include "actor.h"
#include "scene.h"

void Actor::move(float dt)
{
    setPosition(position_ + velocity_ * dt);
    position_ = glm::clamp(position_, glm::vec2(0.0f), game_.getCurrentScene()->getWorldSize());
}