#ifndef UI_MOUSE_H
#define UI_MOUSE_H

/**
 * UI显示类
 */

#include "../core/object_screen.h"
#include "../affiliate/sprite.h"

#include <string>

class UIMouse : public ObjectScreen
{
protected:
    Sprite* sprite1_ = nullptr;
    Sprite* sprite2_ = nullptr;

    float timer_ = 0.0f;

public:
    static UIMouse* addUIMouseChild(Object* parent, const std::string& sprite1_path, const std::string& sprite2_path, float scale = 1.0f, Anchor anchor = Anchor::CENTER);
    virtual void update(float dt) override;
    // getters and setters
    Sprite* getSprite1() { return sprite1_; }
    Sprite* getSprite2() { return sprite2_; }

    void setSprite1(Sprite* sprite) { sprite1_ = sprite; }
    void setSprite2(Sprite* sprite) { sprite2_ = sprite; }

};


#endif // UI_MOUSE_H