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
    std::vector<Object*> object_to_add_;
    std::vector<Object*> children_;
    bool is_active_ = true;
    bool need_remove_ = false;

public:
    Object() = default;
    virtual ~Object() = default;    // 所有的类,不在构造函数和析构函数里面做任何事情

    virtual void init() {};     // 需要初始化的事物,在 init() 里面做
    virtual bool handleEvents(SDL_Event& event);    // 处理事件:事件如果被处理了,则返回 true,否则继续向下传递(每次传递的时候检查是否已经被处理)
    virtual void update(float dt);
    virtual void render();
    virtual void clean();    // 需要清理的资源,在 clean() 里面做

    void safeAddChild(Object* child) {object_to_add_.push_back(child);}
    virtual void addChild(Object* child) { children_.push_back(child); }
    virtual void removeChild(Object* child) {
        children_.erase(std::remove(children_.begin(), children_.end(), child), children_.end());
    }

    // getter and setter
    void setActive(bool active) { is_active_ = active; }
    bool getActive() const { return is_active_; }
    ObjectType getType() const { return type_; }
    void setType(ObjectType type) { type_ = type; }
    bool needRemove() const { return need_remove_; }
    void setNeedRemove(bool need_remove) { need_remove_ = need_remove; }
};



#endif // OBJECT_H