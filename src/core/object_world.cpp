#include "object_world.h"
#include "scene.h"

void ObjectWorld::update(float dt)
{
    ObjectScreen::update(dt);
    render_postion_ = game_.getCurrentScene()->worldToScreen(position_);
}

void ObjectWorld::setPosition(glm::vec2 p)
{
    position_ = p;
    render_postion_ = game_.getCurrentScene()->worldToScreen(p);
}

void ObjectWorld::setRenderPosition(glm::vec2 renderPosition)
{
    render_postion_ = renderPosition;
    position_ = game_.getCurrentScene()->screenToWorld(renderPosition);
}
