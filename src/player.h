#ifndef PLAYER_H
#define PLAYER_H

#include "core/actor.h"
#include "affiliate/sprite_anime.h"

class Player : public Actor
{
    SpriteAnime* sprite_idle_ = nullptr;
    SpriteAnime* sprite_move_ = nullptr;
    bool is_moving_ = false;
public:
    virtual void init() override;
    virtual void handleEvents(SDL_Event& event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

    void keyboardControl();
    void syncCamera();
    void checkState();
    void changeState(bool is_moving);
};



#endif // PLAYER_H