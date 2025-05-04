#include "enemy.h"
#include "affiliate/sprite_anime.h"
#include "core/scene.h"

void Enemy::init()
{
    Actor::init();
    anim_normal_ = SpriteAnime::addSpriteAnimeChild(this,"assets/sprite/ghost-Sheet.png",2.0f);
    anim_hurt_ = SpriteAnime::addSpriteAnimeChild(this,"assets/sprite/ghostHurt-Sheet.png",2.0f);
    anim_dead_ = SpriteAnime::addSpriteAnimeChild(this,"assets/sprite/ghostDead-Sheet.png",2.0f);
    anim_hurt_->setActive(false);
    anim_dead_->setActive(false);
    anim_dead_->setLoop(false);

    current_anim_ = anim_normal_;
}

void Enemy::update(float dt)
{
    Actor::update(dt);
    aimTagert(target_);
    move(dt);

    timer_ += dt;
    if (timer_ > 2.0f && timer_ < 4.0f) {
        changeState(State::HURT);
    }
    else if (timer_ > 4.0f) {
        changeState(State::DEAD);
    }
    remove();
}

void Enemy::aimTagert(Player *target)
{
    if (target == nullptr) return;
    auto direction = target->getPosition() - this->getPosition();
    direction =glm::normalize(direction);
    velocity_ = direction * max_speed_;
}

void Enemy::checkState()
{
}

void Enemy::changeState(State new_state)
{
    if (current_state_ == new_state) return;

    current_anim_->setActive(false);
    switch (new_state)
    {
    case State::NORMAL:
        current_anim_ = anim_normal_;
        current_anim_->setActive(true);
        break;

    case State::HURT:
        current_anim_ = anim_hurt_;
        current_anim_->setActive(true);
        break;

    case State::DEAD:
        current_anim_ = anim_dead_;
        current_anim_->setActive(true);
        break;

    default:
        break;
    }
    current_state_ = new_state;

}

void Enemy::remove()
{
    if (anim_dead_->getFinish())
    {
        need_remove_ = true;
    }

}
