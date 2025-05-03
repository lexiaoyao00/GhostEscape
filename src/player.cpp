#include "player.h"
#include "core/scene.h"

void Player::init()
{
    max_speed_ = 500.0f;
}

void Player::handleEvents(SDL_Event& e)
{

}

void Player::update(float dt)
{
    keyboardControl();
    velocity_ *= 0.9f; //friction
    move(dt);
    syncCamera();
}

void Player::render()
{
    game_.drawBoundary(render_postion_, render_postion_ + glm::vec2(20.0f), 5.0f, {1.0, 0, 0, 1.0});
}

void Player::clean()
{

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
