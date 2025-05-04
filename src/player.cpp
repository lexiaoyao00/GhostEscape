#include "player.h"
#include "core/scene.h"
#include "affiliate/sprite_anime.h"

void Player::init()
{
    Actor::init();
    max_speed_ = 500.0f;

    sprite_idle_ = SpriteAnime::addSpriteAnimeChild(this, "assets/sprite/ghost-idle.png", 2.0f);
    sprite_move_ = SpriteAnime::addSpriteAnimeChild(this, "assets/sprite/ghost-move.png", 2.0f);
    sprite_move_->setActive(false);
}

void Player::handleEvents(SDL_Event &event)
{
    Actor::handleEvents(event);
}

void Player::update(float dt)
{
    Actor::update(dt);
    keyboardControl();
    velocity_ *= 0.9f; // friction
    checkState();
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
    if (currentState[SDL_SCANCODE_W])
    {
        velocity_.y = -max_speed_;
    }
    if (currentState[SDL_SCANCODE_S])
    {
        velocity_.y = max_speed_;
    }

    if (currentState[SDL_SCANCODE_A])
    {
        velocity_.x = -max_speed_;
    }
    if (currentState[SDL_SCANCODE_D])
    {
        velocity_.x = max_speed_;
    }
}

void Player::move(float dt)
{
    setPosition(postion_ + velocity_ * dt);
    postion_ = glm::clamp(postion_, glm::vec2(0.0f), game_.getCurrentScene()->getWorldSize());
}

void Player::syncCamera()
{
    game_.getCurrentScene()->setCameraPosition(postion_ - game_.getScreanSize() / 2.0f);
}

void Player::checkState()
{
    if (velocity_.x < 0.0f)
    {
        sprite_idle_->setFlip(true);
        sprite_move_->setFlip(true);
    }
    else
    {
        sprite_idle_->setFlip(false);
        sprite_move_->setFlip(false);
    }

    bool new_is_moving = (glm::length(velocity_) > 0.1f);
    if (new_is_moving != is_moving_)
    {
        is_moving_ = new_is_moving;
        changeState(is_moving_);
    }
}

void Player::changeState(bool is_moving)
{
    if (is_moving)
    {
        sprite_idle_->setActive(false);
        sprite_move_->setActive(true);
        sprite_move_->setCurrentFrame(sprite_idle_->getCurrentFrame());
        sprite_move_->setFrameTimer(sprite_idle_->getFrameTimer());
    }
    else
    {
        sprite_idle_->setActive(true);
        sprite_move_->setActive(false);
        sprite_idle_->setCurrentFrame(sprite_move_->getCurrentFrame());
        sprite_idle_->setFrameTimer(sprite_move_->getFrameTimer());
    }
}
