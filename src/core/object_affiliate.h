#ifndef OBJECT_AFFILIATE_H
#define OBJECT_AFFILIATE_H

#include "object_screen.h"

class ObjectAffiliate : public Object
{
protected:
    ObjectScreen* parent_ = nullptr; // 父节点
    glm::vec2 offset_ = glm::vec2(0, 0); // 相对父节点偏移量
    glm::vec2 size_ = glm::vec2(0, 0); // 大小

    Anchor anchor_ = Anchor::CENTER; // 锚点

public:
    void setOffsetByAnchor(const Anchor anchor);
    void setScale(float scale);

    // getters and setters
    void setParent(ObjectScreen* parent) { parent_ = parent; }
    ObjectScreen* getParent() { return parent_; }
    void setOffset(glm::vec2 offset) { offset_ = offset; }
    glm::vec2 getOffset() { return offset_; }
    void setSize(glm::vec2 size);
    glm::vec2 getSize() { return size_; }
    void setAnchor(Anchor anchor) { anchor_ = anchor; }
    Anchor getAnchor() { return anchor_; }
};


#endif // OBJECT_AFFILIATE_H