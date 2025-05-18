#ifndef HUD_BUTTON_H
#define HUD_BUTTON_H

#include "../core/object_screen.h"
#include "../affiliate/sprite.h"

class HUDButton : public ObjectScreen
{
protected:
    Sprite *sprite_normal_ = nullptr;
    Sprite *sprite_hover_   = nullptr;
    Sprite *sprite_press_ = nullptr;

    bool is_hover_ = false;
    bool is_press_ = false;
    bool is_trigger_ = false;

public:
    static HUDButton* addHUDButtonChild(Object* parent, glm::vec2 render_pos,
        const std::string &normal_file_path, const std::string &hover_file_path, const std::string &press_file_path,
        float scale = 1.0f,Anchor anchor = Anchor::CENTER);

    virtual void handleEvents(SDL_Event& event) override;
    virtual void update(float dt) override;

    void checkHover();
    void checkState();

    // getters and setters
    Sprite* getSpriteNormal() { return sprite_normal_; }
    Sprite* getSpriteHover() { return sprite_hover_; }
    Sprite* getSpritePress() { return sprite_press_; }

    bool getIsHover() { return is_hover_; }
    bool getIsPress() { return is_press_; }
    bool getIsTrigger();    // 只要触发一次,就会重置 is_trigger_ 状态
    void setIsTrigger(bool is_trigger) { is_trigger_ = is_trigger; }
    void setIsPress(bool is_press) { is_press_ = is_press; }
    void setIsHover(bool is_hover) { is_hover_ = is_hover; }
};



#endif // HUD_BUTTON_H