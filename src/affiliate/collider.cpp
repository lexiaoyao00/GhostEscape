#include "collider.h"

void Collider::render()
{
#ifdef DEBUG_MODE       // in src\core\defs.h
    ObjectAffiliate::render();

    auto pos = parent_->getRenderPosition() + offset_;
    game_.renderFillCircle(pos,size_,0.3f);
#endif  // DEBUG_MODE
}

bool Collider::isColliding(const Collider *other) const
{
    if (!other)
        return false;

    if (type_ == Type::CIRCLE && other->type_ == Type::CIRCLE)  // 两个圆的情况
    {
        auto point1 = parent_->getPosition() + offset_ + size_ / 2.0f;
        auto point2 = other->parent_->getPosition() + other->offset_ + other->size_ / 2.0f;
        return glm::length(point1 - point2) < (size_.x + other->size_.x) / 2.0f;
    }

    // TODO: 其他情况
    return false;
}

Collider *Collider::addColliderChild(ObjectScreen *parent, glm::vec2 size, Type type, Anchor anchor)
{
    auto collider = new Collider();
    collider->init();
    collider->setParent(parent);
    collider->setSize(size);
    collider->setType(type);

    parent->addChild(collider);

    return collider;
}
