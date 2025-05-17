#ifndef ACTOR_H
#define ACTOR_H

#include "object_world.h"

class Stats;
class AffiliateBar;
class Actor : public ObjectWorld
{
protected:
    Stats* stats_ = nullptr;            // 角色属性
    AffiliateBar* health_bar_ = nullptr;    // 角色血条
    glm::vec2 velocity_ = glm::vec2(0, 0);    // 速度
    float max_speed_ = 100.0f;                   // 最大速度

public:

    virtual void update(float dt) override;
    // tools
    virtual void takeDamage(float damage) override;
    bool getAlive() const;
    void move(float dt);


    // getters and setters
    Stats* getStats() const { return stats_; }
    void setStats(Stats* stats) { stats_ = stats; }

    AffiliateBar* getHealthBar() const { return health_bar_; }
    void setHealthBar(AffiliateBar* health_bar) { health_bar_ = health_bar; }

    glm::vec2 getVelocity() const { return velocity_; }
    void setVelocity(const glm::vec2& velocity) { velocity_ = velocity; }

    float getMaxSpeed() const { return max_speed_; }
    void setMaxSpeed(float max_speed) { max_speed_ = max_speed; }

private:
    void updateHealthBar();

};


#endif // ACTOR_H