#include "enemy.h"
#include "affiliate/sprite_anime.h"
#include "core/scene.h"
#include "affiliate/collider.h"
#include "raw/stats.h"

Enemy *Enemy::addEnemyChild(Object *parent, glm::vec2 pos, Player *target)
{
    auto enemy = new Enemy();
    enemy->init();
    enemy->setPosition(pos);
    enemy->setTarget(target);

    if (parent) parent->safeAddChild(enemy);

    return enemy;
}

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

    collider_ = Collider::addColliderChild(this,anim_normal_->getSize());
    stats_ = Stats::addStatsChild(this);

    setType(ObjectType::ENEMY);

}

void Enemy::update(float dt)
{
    Actor::update(dt);

    if (target_->getActive())
    {
        aimTagert(target_);
        move(dt);
        attack();
    }
    checkState();
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
    State new_state;
    if (stats_->getHealth() <= 0 ) new_state = State::DEAD;
    else if (stats_->getInvincible()) new_state = State::HURT;
    else new_state = State::NORMAL;

    if (new_state != current_state_) changeState(new_state);

}

void Enemy::changeState(State new_state)
{
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

void Enemy::attack()
{
    if (!collider_ || !target_ || target_->getCollider() == nullptr) return;

    if (collider_->isColliding(target_->getCollider()))
    {
        if (stats_ && target_->getStats())
        {
            target_->takeDamage(stats_->getDamage());
        }
    }
}

void Enemy::remove()
{
    if (anim_dead_->getFinish())
    {
        need_remove_ = true;
    }

}
