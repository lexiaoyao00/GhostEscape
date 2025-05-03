#ifndef OBJECT_WORLD_H
#define OBJECT_WORLD_H

#include "object_screen.h"

class ObjectWorld : public ObjectScreen
{
protected:
    glm::vec2 postion_ = glm::vec2(0,0);     // position of the world

    virtual void init() override { type_ = ObjectType::OBJECT_WORLD; };

public:

    virtual void update(float dt) override;

    // getter and setter
    glm::vec2 getPostion() { return postion_; }
    void setPosition(glm::vec2 p);
    virtual void setRenderPosition(glm::vec2 renderPosition) override;
};



#endif // OBJECT_WORLD_H