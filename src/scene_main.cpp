#include "scene_main.h"
#include "player.h"
#include "enemy.h"
#include "world/effect.h"
#include "spawner.h"
#include "screen/UI_mouse.h"
#include "world/spell.h"

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

    ui_mouse_ = UIMouse::addUIMouseChild(this,"assets/UI/29.png","assets/UI/30.png", 1.0f, Anchor::CENTER);
    // glm::vec2 pos = world_size_ / 2.0f + glm::vec2(200.0f);
    // auto enemy = new Enemy();
    // enemy->init();
    // enemy->setTarget(player_);
    // enemy->setPosition(pos);
    // // addChild(enemy);

    // Effect::addEffectChild(this, "assets/effect/184_3.png", pos, 2.0f, enemy);

}

void SceneMain::handleEvents(SDL_Event& event)
{
    Scene::handleEvents(event);
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            auto pos = game_.getMousePosition() + camera_position_;
            Spell::addSpellChild(this, "assets/effect/Thunderstrike w blur.png", pos, 100.0f, 3.0f,Anchor::CENTER);
        }

    }
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
