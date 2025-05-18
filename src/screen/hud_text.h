#ifndef HUD_TEXT_H
#define HUD_TEXT_H

#include "../core/object_affiliate.h"
#include "../affiliate/text_label.h"
#include "../affiliate/sprite.h"

class HUDText : public ObjectScreen
{
protected:
    TextLabel* text_labe_ = nullptr;
    Sprite* sprite_bg_ = nullptr;   // 背景图
    glm::vec2 size_ = glm::vec2(0.0f, 0.0f); // 背景图大小

public:
    static HUDText* addHUDTextChild(Object* parent, const std::string& text, glm::vec2 render_pos, glm::vec2 size,
        const std::string& font_path = "assets/font/VonwaonBitmap-16px.ttf", int font_size = 32,
        const std::string& bg_path = "assets/UI/Textfield_01.png", Anchor anchor = Anchor::CENTER);

    void setBgSizeByText(float margin = 50.0f);
    // getters and setters
    void setTextLabel(TextLabel* text_label) { text_labe_ = text_label; }
    void setSpriteBg(Sprite* sprite_bg) { sprite_bg_ = sprite_bg; }
    TextLabel* getTextLabel() { return text_labe_; }
    Sprite* getSpriteBg() { return sprite_bg_; }
    glm::vec2 getSize() { return size_; }
    void setSize(const glm::vec2& size);

    void setText(const std::string& text) { text_labe_->setText(text); }
    std::string getText() { return text_labe_->getText(); }

    void setBackground(const std::string& file_path);
};



#endif // HUD_TEXT_H