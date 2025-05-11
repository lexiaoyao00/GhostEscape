#ifndef OBJECT_WORLD_H
#define OBJECT_WORLD_H

#include "object_screen.h"
#include "../affiliate/collider.h"

class ObjectWorld : public ObjectScreen
{
protected:
    glm::vec2 position_ = glm::vec2(0, 0); // position of the world
    Collider *collider_ = nullptr;         // collider of the world

public:
    virtual void init() override { type_ = ObjectType::OBJECT_WORLD; };
    virtual void update(float dt) override;

    // tools
    virtual void takeDamage(float) {return;}


    // getter and setter
    virtual glm::vec2 getPosition() const override { return position_; }
    void setPosition(glm::vec2 p);
    virtual void setRenderPosition(glm::vec2 renderPosition) override;
    Collider *getCollider() { return collider_; }
    void setCollider(Collider *collider) { collider_ = collider; }
};

#endif // OBJECT_WORLD_H