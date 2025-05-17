#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "core/scene.h"

class Spawner;
class Player;
class UIMouse;
class HUDStats;
class SceneMain : public Scene
{
    Player* player_ = nullptr;
    Spawner* spawner_ = nullptr;
    UIMouse* ui_mouse_ = nullptr;
    HUDStats* hud_stats_ = nullptr;
public:
    SceneMain() = default;
    ~SceneMain() = default;

    void init() override;
    void handleEvents(SDL_Event& event) override;
    void update(float dt) override;
    void render() override;
    void clean() override;

private:
    void renderBackground();
};


#endif // SCENE_MAIN_H