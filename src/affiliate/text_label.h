#ifndef TEXT_LABEL_H
#define TEXT_LABEL_H


#include "../core/object_affiliate.h"
#include <string>


class TextLabel : public ObjectAffiliate
{
protected:
    TTF_Text* ttf_text_ = nullptr;
    std::string font_path_;
    int font_size_ = 16;

public:
    static TextLabel* addTextLabelChild(ObjectScreen* parent, const std::string& text, const std::string& font_path, int font_size = 16, Anchor anchor = Anchor::CENTER);

    virtual void render() override;
    virtual void clean() override;

    // setters and getters
    void setFont(const std::string& font_path, int font_size);  // init 后需要立刻调用
    void setFontPath(const std::string& font_path);
    void setFontSize(int font_size);
    void setText(const std::string& text);
    std::string getText() const { return ttf_text_->text; }

private:
    void updateSize(); // 根据文字内容决定大小

};




#endif // TEXT_LABEL_H