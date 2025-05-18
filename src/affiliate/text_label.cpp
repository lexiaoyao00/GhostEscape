#include "text_label.h"

TextLabel *TextLabel::addTextLabelChild(ObjectScreen *parent, const std::string &text, const std::string &font_path, int font_size, Anchor anchor)
{
    TextLabel *label = new TextLabel();
    label->init();
    label->setFont(font_path, font_size);
    label->setText(text);
    label->setAnchor(anchor);
    label->updateSize();
    if (parent)
    {
        label->setParent(parent);
        parent->addChild(label);
    }
    return label;
}

void TextLabel::render()
{
    ObjectAffiliate::render();
    auto pos = parent_->getRenderPosition() + offset_;
    TTF_DrawRendererText(ttf_text_, pos.x, pos.y);
}

void TextLabel::clean()
{
    if (ttf_text_ != nullptr)
        TTF_DestroyText(ttf_text_);
}

void TextLabel::setFont(const std::string &font_path, int font_size)
{
    font_path_ = font_path;
    font_size_ = font_size;
    auto font = game_.getAssetStore()->getFont(font_path_, font_size_);
    if (!ttf_text_) ttf_text_ = game_.creatTTF_Text("", font_path, font_size);
    TTF_SetTextFont(ttf_text_, font);
    updateSize();
}

void TextLabel::setFontPath(const std::string &font_path)
{
    font_path_ = font_path;
    // 可能是新的font,从asset store中载入
    auto font = game_.getAssetStore()->getFont(font_path_, font_size_);
    TTF_SetTextFont(ttf_text_, font);
    updateSize();
}

void TextLabel::setFontSize(int font_size)
{
    font_size_ = font_size;
    // 可能是新的font,从asset store中载入
    auto font = game_.getAssetStore()->getFont(font_path_, font_size_);
    TTF_SetTextFont(ttf_text_, font);
    updateSize();
}

void TextLabel::setText(const std::string &text)
{
    TTF_SetTextString(ttf_text_, text.c_str(), text.length());
    updateSize();
}

void TextLabel::updateSize()
{
    int w, h;
    TTF_GetTextSize(ttf_text_, &w, &h);
    setSize(glm::vec2(w, h));
}
