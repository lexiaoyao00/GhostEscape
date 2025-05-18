#include "bg_star.h"
#include "../core/scene.h"

BgStar *BgStar::addBgStarChild(Object *parent, int num, float scale_far, float scale_mid, float scale_near)
{
    BgStar *star = new BgStar();
    star->init();
    star->num_ = num;
    star->scale_far_ = scale_far;
    star->scale_mid_ = scale_mid;
    star->scale_near_ = scale_near;

    star->star_far_.reserve(num); // 预先把内存分配好,以免后续重新分配
    star->star_mid_.reserve(num);
    star->star_near_.reserve(num);
    auto extra = Game::GetInstance().getCurrentScene()->getWorldSize() - Game::GetInstance().getScreanSize();
    for (auto i = 0; i < num; i++)
    {
        star->star_far_.emplace_back(Game::GetInstance().randomVec2(glm::vec2(0), Game::GetInstance().getScreanSize() + extra * scale_far));
        star->star_mid_.emplace_back(Game::GetInstance().randomVec2(glm::vec2(0), Game::GetInstance().getScreanSize() + extra * scale_mid));
        star->star_near_.emplace_back(Game::GetInstance().randomVec2(glm::vec2(0), Game::GetInstance().getScreanSize() + extra * scale_near));
    }
    if (parent) parent->addChild(star);
    return star;
}

void BgStar::update(float dt)
{
    timer_ += dt;

    color_far_ = {0.5f + 0.5f * sinf(timer_ * 0.9f), 0.5f + 0.5f * sinf(timer_ * 0.8f), 0.5f + 0.5f * sinf(timer_ * 0.7f), 1};
    color_mid_ = {0.5f + 0.5f * sinf(timer_ * 0.8f), 0.5f + 0.5f * sinf(timer_ * 0.7f), 0.5f + 0.5f * sinf(timer_ * 0.6f), 1};
    color_near_ = {0.5f + 0.5f * sinf(timer_ * 0.7f), 0.5f + 0.5f * sinf(timer_ * 0.6f), 0.5f + 0.5f * sinf(timer_ * 0.5f), 1};
}

void BgStar::render()
{
    game_.drawPoint(star_far_, -game_.getCurrentScene()->getCameraPosition() * scale_far_, color_far_);
    game_.drawPoint(star_mid_, -game_.getCurrentScene()->getCameraPosition() * scale_mid_, color_mid_);
    game_.drawPoint(star_near_, -game_.getCurrentScene()->getCameraPosition() * scale_near_, color_near_);
}
