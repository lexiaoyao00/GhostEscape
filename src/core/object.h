#ifndef OBJECT_H
#define OBJECT_H

#include "game.h"
#include "defs.h"
#include <vector>
#include <algorithm>

class Object
{
protected:
    ObjectType type_ = ObjectType::NONE;
    Game& game_ = Game::GetInstance();
    std::vector<Object*> children_;
public:
    Object() = default;
    virtual ~Object() = default;    // 所有的类,不在构造函数和析构函数里面做任何事情

    virtual void init() {};     // 需要初始化的事物,在 init() 里面做
    virtual void handleEvents(SDL_Event& event);
    virtual void update(float dt);
    virtual void render();
    virtual void clean();    // 需要清理的资源,在 clean() 里面做

    virtual void addChild(Object* child) { children_.push_back(child); }
    virtual void removeChild(Object* child) {
        children_.erase(std::remove(children_.begin(), children_.end(), child), children_.end());
    }

    // getter and setter
    ObjectType getType() const { return type_; }
    void setType(ObjectType type) { type_ = type; }
};



#endif // OBJECT_H