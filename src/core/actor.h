#ifndef ACTOR_H
#define ACTOR_H

#include "object_world.h"

class Stats;
class Actor : public ObjectWorld
{
protected:
    Stats* stats_ = nullptr;            // 角色属性
    glm::vec2 velocity_ = glm::vec2(0, 0);    // 速度
    float max_speed_ = 100.0f;                   // 最大速度

public:
    // tools
    void move(float dt);


    // getters and setters
    Stats* getStats() const { return stats_; }
    void setStats(Stats* stats) { stats_ = stats; }

    glm::vec2 getVelocity() const { return velocity_; }
    void setVelocity(const glm::vec2& velocity) { velocity_ = velocity; }

    float getMaxSpeed() const { return max_speed_; }
    void setMaxSpeed(float max_speed) { max_speed_ = max_speed; }

    // tools
    void takeDamage(float damage);
    bool getAlive() const;
};


#endif // ACTOR_H