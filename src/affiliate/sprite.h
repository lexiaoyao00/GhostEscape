#ifndef SPRITE_H
#define SPRITE_H

#include "../core/object_affiliate.h"

struct Texture
{
    SDL_Texture* texture = nullptr;
    SDL_FRect src_rect = {0, 0, 0, 0};
    glm::vec2 size = glm::vec2(0, 0);
    float angle = 0;
    bool is_flip = false;

    Texture() = default;
    Texture(const std::string& file_path);
};


class Sprite : public ObjectAffiliate
{
protected:
    Texture texture_;
    bool is_finish_ = false;
    glm::vec2 percentage_ = glm::vec2(1.0f);

public:
    static Sprite* addSpriteChild(ObjectScreen* parent, const std::string& file_path, float scale = 1.0f, Anchor anchor = Anchor::CENTER);
    virtual void render() override;

    // tools

    // getters and setters
    Texture* getTexture() { return &texture_; }
    virtual void setTexture(Texture texture);
    void setFlip(bool is_flip) { texture_.is_flip = is_flip; }
    void setAngle(float angle) { texture_.angle = angle; }
    bool getFlip() const { return texture_.is_flip; }
    float getAngle() const { return texture_.angle; }
    bool getFinish() const { return is_finish_; }
    void setFinish(bool is_finish) { is_finish_ = is_finish; }
    glm::vec2 getPercentage() const { return percentage_; }
    void setPercentage(glm::vec2 percentage) { percentage_ = percentage; }
};


#endif // SPRITE_H