#ifndef OBJECT_SCREEN_H
#define OBJECT_SCREEN_H

#include "object.h"

class ObjectScreen : public Object
{
protected:
    glm::vec2 render_postion_ = glm::vec2(0,0);  // 渲染(屏幕)位置

    virtual void init() override { type_ = ObjectType::OBJECT_SCREEN; }
public:
    // getter and setter
    glm::vec2 getRenderPosition() { return render_postion_; }
    virtual void setRenderPosition(glm::vec2 position) { render_postion_ = position; }
};



#endif // OBJECT_SCREEN_H