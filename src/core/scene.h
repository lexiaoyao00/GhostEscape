#ifndef SCENE_H
#define SCENE_H

#include "object.h"
#include "object_world.h"
#include "object_screen.h"
#include "glm/glm.hpp"
#include <vector>

class Scene : public Object
{
protected:
    glm::vec2 camera_position_ = glm::vec2(0);  // 相机位置
    glm::vec2 world_size_ = glm::vec2(0);   // 世界大小
    std::vector<ObjectWorld*> children_world_;  // 世界中的物体
    std::vector<ObjectScreen*> children_screen_; // 屏幕中的物体


public:
    Scene() = default;
    ~Scene() = default;

    virtual void init() override {};
    virtual void handleEvents(SDL_Event& event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

    virtual void addChild(Object* child) override;
    virtual void removeChild(Object* child) override; // 将子对象从容器中移除

    glm::vec2 worldToScreen(const glm::vec2& world_position) const { return world_position - camera_position_; }
    glm::vec2 screenToWorld(const glm::vec2& screen_position) const { return screen_position + camera_position_; }

    // getters and setters
    glm::vec2 getCameraPosition() const { return camera_position_; }
    void setCameraPosition(const glm::vec2& camera_position);
    glm::vec2 getWorldSize() const { return world_size_; }
    void setWorldSize(const glm::vec2& world_size) { world_size_ = world_size; }
    std::vector<ObjectWorld*>& getChildrenWorld() { return children_world_; }
    std::vector<ObjectScreen*>& getChildrenScreen() { return children_screen_; }
};


#endif // SCENE_H