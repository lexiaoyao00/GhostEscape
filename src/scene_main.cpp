#include "scene_main.h"
#include "player.h"
#include "enemy.h"
#include "world/effect.h"
#include "spawner.h"
#include "screen/UI_mouse.h"
#include "world/spell.h"
#include "screen/hud_stats.h"
#include "screen/hud_text.h"

void SceneMain::init()
{
    SDL_HideCursor();
    // SDL_ShowCursor();
    world_size_ = game_.getScreanSize() * 3.0f;
    camera_position_ = world_size_ / 2.0f - game_.getScreanSize() / 2.0f;
    player_ = new Player();
    player_->init();
    player_->setPosition(world_size_ / 2.0f);
    addChild(player_);

    spawner_ = new Spawner();
    spawner_->init();
    spawner_->setTarget(player_);
    addChild(spawner_);


    hud_stats_ = HUDStats::addHUDStatsChild(this, player_, glm::vec2(30.0f));
    hud_text_score_ = HUDText::addHUDTextChild(this, "Score: 0", glm::vec2(game_.getScreanSize().x - 120.f,30.f),glm::vec2(200,50));

    ui_mouse_ = UIMouse::addUIMouseChild(this,"assets/UI/29.png","assets/UI/30.png", 1.0f, Anchor::CENTER);
}

void SceneMain::handleEvents(SDL_Event& event)
{
    Scene::handleEvents(event);
}

void SceneMain::update(float dt)
{
    Scene::update(dt);
    updateScore();
}

void SceneMain::render()
{
    renderBackground();

    Scene::render();
}

void SceneMain::clean()
{
    Scene::clean();
}

void SceneMain::renderBackground()
{
    auto start = -camera_position_;
    auto end = world_size_ - camera_position_;
    game_.drawGrid(start, end, 80.0f, SDL_FColor{0.5, 0.5, 0.5, 1.0});
    game_.drawBoundary(start, end, 5.0f, SDL_FColor{1.0, 1.0, 1.0, 1.0});
}

void SceneMain::updateScore()
{
    hud_text_score_->setText("Score: " + std::to_string(game_.getScore()));
}
