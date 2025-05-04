#ifndef COLLIDER_H
#define COLLIDER_H


#include "../core/object_affiliate.h"

class Collider : public ObjectAffiliate
{
protected:
    enum class Type
    {
        CIRCLE,         // size_ 的 x 轴为直径,默认 y = x
        RECTANGLE
    };
    Type type_ = Type::CIRCLE;

public:
    virtual void render() override;

    bool isColliding(const Collider* other) const;
    static Collider* addColliderChild(ObjectScreen* parent, glm::vec2 size, Type type = Type::CIRCLE, Anchor anchor = Anchor::CENTER);

    // getters and setters
    Type getType() const { return type_; }
    void setType(Type type) { type_ = type; }
};


#endif // COLLIDER_H