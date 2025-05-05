#ifndef ENEMY_H
#define ENEMY_H

#include "player.h"

class Enemy : public Actor
{
    enum class State{
        NORMAL,
        HURT,
        DEAD
    };

    State current_state_ = State::NORMAL;

    Player *target_ = nullptr;
    SpriteAnime *anim_normal_ = nullptr;
    SpriteAnime *anim_hurt_ = nullptr;
    SpriteAnime *anim_dead_ = nullptr;
    SpriteAnime *current_anim_ = nullptr;

public:
    static Enemy *addEnemyChild(Object *parent, glm::vec2 pos, Player *target);

    virtual void init() override;
    virtual void update(float dt) override;

    void aimTagert(Player *target);

    void checkState();
    void changeState(State new_state);
    void attack();
    void remove();

    // getters and setters
    Player *getTarget() const { return target_; }
    void setTarget(Player *target) { target_ = target; }
};

#endif // ENEMY_H