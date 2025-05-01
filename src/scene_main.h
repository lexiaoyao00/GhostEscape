#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "core/scene.h"

class SceneMain : public Scene
{
public:
    SceneMain() = default;
    ~SceneMain() = default;

    void init() override;
    void handleEvents(SDL_Event& event) override;
    void update(float dt) override;
    void render() override;
    void clean() override;
};


#endif // SCENE_MAIN_H