#include "scene_main.h"
#include "player.h"
#include "enemy.h"
#include "world/effect.h"
#include "spawner.h"
#include "screen/UI_mouse.h"
#include "world/spell.h"
#include "screen/hud_stats.h"
#include "screen/hud_text.h"
#include "screen/hud_button.h"
#include "scene_title.h"

void SceneMain::init()
{
    Scene::init();
    SDL_HideCursor();
    // SDL_ShowCursor();

    game_.playMusic("assets/bgm/OhMyGhost.ogg");

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

    hud_button_pause_ = HUDButton::addHUDButtonChild(this, game_.getScreanSize() - glm::vec2(230.f,30.f),
        "assets/UI/A_Pause1.png", "assets/UI/A_Pause2.png","assets/UI/A_Pause3.png");
    hud_button_restart_ = HUDButton::addHUDButtonChild(this, game_.getScreanSize() - glm::vec2(140.f,30.f),
        "assets/UI/A_Restart1.png", "assets/UI/A_Restart2.png","assets/UI/A_Restart3.png");
    hud_button_back_ = HUDButton::addHUDButtonChild(this, game_.getScreanSize() - glm::vec2(50.f,30.f),
        "assets/UI/A_Back1.png", "assets/UI/A_Back2.png","assets/UI/A_Back3.png");

    hud_stats_ = HUDStats::addHUDStatsChild(this, player_, glm::vec2(30.0f));
    hud_text_score_ = HUDText::addHUDTextChild(this, "Score: 0", glm::vec2(game_.getScreanSize().x - 120.f,30.f),glm::vec2(200,50));

    ui_mouse_ = UIMouse::addUIMouseChild(this,"assets/UI/29.png","assets/UI/30.png", 1.0f, Anchor::CENTER);
}

bool SceneMain::handleEvents(SDL_Event& event)
{
    return Scene::handleEvents(event);
}

void SceneMain::update(float dt)
{
    Scene::update(dt);
    updateScore();
    checkButtonPause();
    checkButtonRestart();
    checkButtonBack();
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

void SceneMain::checkButtonPause()
{
    if (!hud_button_pause_->getIsTrigger()) return;
    if (is_pause_) resume();
    else pause();
}

void SceneMain::checkButtonRestart()
{
    if (!hud_button_restart_->getIsTrigger()) return;
    auto scene = new SceneMain();
    game_.safeChangeScene(scene);   // 或者 当前场景 先 clean() 再 init(),但是有风险
}

void SceneMain::checkButtonBack()
{
    if (!hud_button_back_->getIsTrigger()) return;
    auto scene = new SceneTitle();
    game_.safeChangeScene(scene);
}
