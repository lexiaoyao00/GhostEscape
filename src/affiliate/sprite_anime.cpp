#include "sprite_anime.h"

SpriteAnime *SpriteAnime::addSpriteAnimeChild(ObjectScreen *parent, const std::string &file_path, float scale, Anchor anchor)
{
    auto sprite_anime = new SpriteAnime();
    sprite_anime->init();
    sprite_anime->setAnchor(anchor);
    sprite_anime->setTexture(Texture(file_path));
    sprite_anime->setScale(scale);
    sprite_anime->setParent(parent);

    parent->addChild(sprite_anime);

    return sprite_anime;
}

void SpriteAnime::update(float dt)
{
    if (is_finish_) return;
    frame_timer_ += dt;
    if (frame_timer_ >= 1.0f / fps_)
    {
        current_frame_++;
        if (current_frame_ >= total_frames_)
        {
            current_frame_ = 0;

            if (!is_loop_) is_finish_ = true;
        }
        frame_timer_ = 0.0f;
    }
    texture_.src_rect.x = current_frame_ * texture_.src_rect.w;
}

void SpriteAnime::setTexture(Texture texture)
{
    texture_ = texture;
    total_frames_ = texture.src_rect.w / texture.src_rect.h;
    texture_.src_rect.w = texture.src_rect.h;
    size_ = glm::vec2(texture_.src_rect.w, texture_.src_rect.h);
}
