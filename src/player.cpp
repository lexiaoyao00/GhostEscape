#include "player.h"
#include "core/scene.h"
#include "affiliate/sprite_anime.h"

void Player::init()
{
    Actor::init();
    max_speed_ = 500.0f;

    SpriteAnime::addSpriteAnimeChild(this,"assets/sprite/ghost-idle.png",2.0f);
}

void Player::handleEvents(SDL_Event& event)
{
    Actor::handleEvents(event);
}

void Player::update(float dt)
{
    Actor::update(dt);
    keyboardControl();
    velocity_ *= 0.9f; //friction
    move(dt);
    syncCamera();
}

void Player::render()
{
    Actor::render();
}

void Player::clean()
{
    Actor::clean();
}

void Player::keyboardControl()
{
    auto currentState = SDL_GetKeyboardState(NULL);
    if (currentState[SDL_SCANCODE_W]){
        velocity_.y = -max_speed_;
    }
    if (currentState[SDL_SCANCODE_S]){
        velocity_.y = max_speed_;
    }

    if (currentState[SDL_SCANCODE_A]){
        velocity_.x = -max_speed_;
    }
    if (currentState[SDL_SCANCODE_D]){
        velocity_.x = max_speed_;
    }

}

void Player::move(float dt)
{
    setPosition(postion_ + velocity_ * dt);
    postion_ = glm::clamp(postion_, glm::vec2(0.0f),game_.getCurrentScene()->getWorldSize());
}

void Player::syncCamera()
{
    game_.getCurrentScene()->setCameraPosition(postion_ - game_.getScreanSize() / 2.0f);
}
