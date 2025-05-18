#include "hud_button.h"

HUDButton *HUDButton::addHUDButtonChild(Object *parent, glm::vec2 render_pos, const std::string &normal_file_path, const std::string &hover_file_path, const std::string &press_file_path, float scale, Anchor anchor)
{
    auto hud_button = new HUDButton();
    hud_button->init();
    hud_button->setRenderPosition(render_pos);
    hud_button->sprite_normal_ = Sprite::addSpriteChild(hud_button, normal_file_path, scale, anchor);
    hud_button->sprite_hover_ = Sprite::addSpriteChild(hud_button, hover_file_path, scale, anchor);
    hud_button->sprite_press_ = Sprite::addSpriteChild(hud_button, press_file_path, scale, anchor);
    hud_button->sprite_hover_->setActive(false);
    hud_button->sprite_press_->setActive(false);

    if (parent)  parent->addChild(hud_button);
    return hud_button;
}

bool HUDButton::handleEvents(SDL_Event &event)
{
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            if (is_hover_)
            {
                is_press_ = true;
                game_.playSound("assets/sound/UI_button08.wav");
                return true;
            }
        }
    }
    else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP)
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            is_press_ = false;
            if (is_hover_)
            {
                is_trigger_ = true;
                return true;
            }
        }
    }
    return false;
}

void HUDButton::update(float)
{
    checkHover();
    checkState();
}

void HUDButton::checkHover()
{
    bool new_hover = false;
    auto pos = render_postion_ + sprite_normal_->getOffset();
    auto size = sprite_normal_->getSize();
    if (game_.isMouseInRect(pos, pos + size))
    {
        new_hover = true;
    }
    else
    {
        new_hover = false;
    }
    if (is_hover_ != new_hover)
    {
        is_hover_ = new_hover;
        if (is_hover_ && !is_press_) game_.playSound("assets/sound/UI_button12.wav");
    }
}

void HUDButton::checkState()
{
    if (!is_press_ && !is_hover_)
    {
        sprite_normal_->setActive(true);
        sprite_hover_->setActive(false);
        sprite_press_->setActive(false);
    }
    else if (!is_press_ && is_hover_)
    {
        sprite_normal_->setActive(false);
        sprite_hover_->setActive(true);
        sprite_press_->setActive(false);
    }
    else
    {
        sprite_normal_->setActive(false);
        sprite_hover_->setActive(false);
        sprite_press_->setActive(true);
    }
}

bool HUDButton::getIsTrigger()
{
    if (is_trigger_)
    {
        is_trigger_ = false;
        is_press_ = false;
        is_hover_ = false;

        return true;
    }
    return false;
}

void HUDButton::setScale(float scale)
{
    sprite_normal_->setScale(scale);
    sprite_hover_->setScale(scale);
    sprite_press_->setScale(scale);
}
