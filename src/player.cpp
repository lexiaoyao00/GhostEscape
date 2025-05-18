#include "player.h"
#include "core/scene.h"
#include "affiliate/sprite_anime.h"
#include "affiliate/collider.h"
#include "raw/stats.h"
#include "affiliate/text_label.h"
#include "raw/timer.h"

void Player::init()
{
    Actor::init();
    flash_timer_ = Timer::addTimerChild(this, 0.4f);
    flash_timer_->start();

    max_speed_ = 500.0f;
    sprite_idle_ = SpriteAnime::addSpriteAnimeChild(this, "assets/sprite/ghost-idle.png", 2.0f);
    sprite_move_ = SpriteAnime::addSpriteAnimeChild(this, "assets/sprite/ghost-move.png", 2.0f);
    sprite_move_->setActive(false);

    collider_ = Collider::addColliderChild(this, sprite_idle_->getSize() / 2.0f);
    stats_ = Stats::addStatsChild(this);

    dead_effect_ = Effect::addEffectChild(game_.getCurrentScene(), "assets/effect/1764.png", glm::vec2(0.0f), 2.0f, nullptr);
    dead_effect_->setActive(false);

    weapon_thunder_ = WeaponThunder::addWeaponThunderChild(this, 2.0f,40.0f);
}

bool Player::handleEvents(SDL_Event &event)
{
    return Actor::handleEvents(event);
}

void Player::update(float dt)
{
    Actor::update(dt);
    keyboardControl();
    velocity_ *= 0.9f; // friction
    checkState();
    move(dt);
    syncCamera();
    checkIsDead();
}

void Player::render()
{
    if (stats_->getInvincible() && flash_timer_->getProgress() < 0.5f)
    {
        return;
    }

    Actor::render();
}

void Player::clean()
{
    Actor::clean();
}

void Player::takeDamage(float damage)
{
    if (!stats_ || stats_->getInvincible()) return;
    Actor::takeDamage(damage);
    game_.playSound("assets/sound/hit-flesh-02-266309.mp3");
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


void Player::syncCamera()
{
    game_.getCurrentScene()->setCameraPosition(position_ - game_.getScreanSize() / 2.0f);
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

void Player::checkIsDead()
{
    if (!stats_->getAlive())
    {
        dead_effect_->setActive(true);
        dead_effect_->setPosition(getPosition());
        // setNeedRemove(true);
        setActive(false);
        game_.playSound("assets/sound/female-scream-02-89290.mp3");
    }
}
