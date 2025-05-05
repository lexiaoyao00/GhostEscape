#include "stats.h"

Stats *Stats::addStatsChild(Actor *parent, float max_health, float max_mana, float mana_regen, float damage)
{
    Stats *stats = new Stats();
    stats->parent_ = parent;
    stats->max_health_ = max_health;
    stats->max_mana_ = max_mana;
    stats->mana_regen_ = mana_regen;
    stats->damage_ = damage;
    stats->health_ = max_health;
    stats->mana_ = max_mana;
    stats->is_alive_ = true;

    parent->addChild(stats);
    return stats;
}

void Stats::update(float dt)
{
    Object::update(dt);
    regenMana(dt);
    if (is_invincible_)
    {
        invincible_timer_ += dt;
        if (invincible_timer_ >= invincible_time_)
        {
            is_invincible_ = false;
            invincible_timer_ = 0.0f;
        }
    }
}

bool Stats::canUseMana(float mana_cost)
{
    return mana_ >= mana_cost;
}

void Stats::regenMana(float dt)
{
    mana_ += dt * mana_regen_;
    if (mana_ > max_mana_) mana_ = max_mana_;
}

void Stats::useMana(float mana_cost)
{
    mana_ -= mana_cost;
    if (mana_ < 0) mana_ = 0;
}

void Stats::takeDamage(float damage)
{
    if (is_invincible_) return;

    health_ -= damage;
    if (health_ < 0)
    {
        health_ = 0;
        is_alive_ = false;
    }

    SDL_Log("Health: %f", health_);
    is_invincible_ = true;
    invincible_timer_ = 0.0f;
}
