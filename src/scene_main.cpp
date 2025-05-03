#include "scene_main.h"
#include "player.h"

void SceneMain::init()
{
    world_size_ = game_.getScreanSize() * 3.0f;
    camera_position_ = world_size_ / 2.0f - game_.getScreanSize() / 2.0f;
    player_ = new Player();
    player_->init();
    player_->setPosition(world_size_ / 2.0f);

    addChild(player_);
}

void SceneMain::handleEvents(SDL_Event& event)
{
    Scene::handleEvents(event);
}

void SceneMain::update(float dt)
{
    Scene::update(dt);
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
