#include "UI_mouse.h"

UIMouse *UIMouse::addUIMouseChild(Object *parent, const std::string &sprite1_path, const std::string &sprite2_path, float scale, Anchor anchor)
{
    auto ui_mouse = new UIMouse();
    ui_mouse->init();

    ui_mouse->sprite1_ = Sprite::addSpriteChild(ui_mouse, sprite1_path, scale, anchor);
    ui_mouse->sprite2_ = Sprite::addSpriteChild(ui_mouse, sprite2_path, scale, anchor);

    if (parent)
        parent->addChild(ui_mouse);

    return ui_mouse;
}

void UIMouse::update(float dt)
{
    ObjectScreen::update(dt);

    timer_ += dt;
    if (timer_ < 0.3f)
    {
        sprite1_->setActive(true);
        sprite2_->setActive(false);
    }
    else if (timer_ < 0.6f)
    {
        sprite1_->setActive(false);
        sprite2_->setActive(true);
    }
    else
    {
        timer_ = 0;
    }

    setRenderPosition(game_.getMousePosition());
}
