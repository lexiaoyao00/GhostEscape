#ifndef PLAYER_H
#define PLAYER_H

#include "core/actor.h"
#include "affiliate/sprite_anime.h"
#include "world/effect.h"
#include "weapon_thunder.h"

class Timer;
class Player : public Actor
{
    WeaponThunder* weapon_thunder_ = nullptr;
    SpriteAnime* sprite_idle_ = nullptr;
    SpriteAnime* sprite_move_ = nullptr;
    Effect* dead_effect_ = nullptr;
    Timer* flash_timer_ = nullptr;

    bool is_moving_ = false;
public:
    virtual void init() override;
    virtual bool handleEvents(SDL_Event& event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

    virtual void takeDamage(float damage) override;

    void keyboardControl();
    void syncCamera();
    void checkState();
    void changeState(bool is_moving);
    void checkIsDead();
};



#endif // PLAYER_H