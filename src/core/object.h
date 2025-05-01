#ifndef OBJECT_H
#define OBJECT_H

#include "game.h"

class Object
{
protected:
    Game& game = Game::GetInstance();
public:
    Object() = default;
    virtual ~Object() = default;    // 所有的类,不在构造函数和析构函数里面做任何事情

    virtual void init() {};     // 需要初始化的事物,在 init() 里面做
    virtual void handleEvents(SDL_Event&) {};
    virtual void update(float) {};
    virtual void render() {};
    virtual void clean() {};    // 需要清理的资源,在 clean() 里面做
};



#endif // OBJECT_H