#include "sprite.h"

Texture::Texture(const std::string &file_path)
{
    texture = Game::GetInstance().getAssetStore()->getTexture(file_path);
    SDL_GetTextureSize(texture, &src_rect.w, &src_rect.h);
}

Sprite *Sprite::addSpriteChild(ObjectScreen *parent, const std::string &file_path, float scale, Anchor anchor)
{
    auto sprite = new Sprite();
    sprite->init();
    sprite->setTexture(Texture(file_path));
    sprite->setScale(scale);
    sprite->setParent(parent);

    parent->addChild(sprite);
    return sprite;
}

void Sprite::render()
{
    if (!texture_.texture || !parent_ || is_finish_)
    {
        return;
    }

    auto pos = parent_->getRenderPosition() + offset_;
    game_.renderTexture(texture_, pos, size_);

}

void Sprite::setTexture(Texture texture)
{
    texture_ = texture;
    size_ = glm::vec2(texture.src_rect.w, texture.src_rect.h);
}
