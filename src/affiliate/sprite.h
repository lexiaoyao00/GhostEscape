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


public:
    static Sprite* addSpriteChild(ObjectScreen* parent, const std::string& file_path, float scale = 1.0f);
    virtual void render() override;

    // tools
    void setScale(float scale) { size_ *= scale; }

    // getters and setters
    Texture* getTexture() { return &texture_; }
    virtual void setTexture(Texture texture);
};


#endif // SPRITE_H