#ifndef SCENE_TITLE_H
#define SCENE_TITLE_H

#include "core/scene.h"

class HUDButton;
class HUDText;
class SceneTitle : public Scene
{
protected:
    SDL_FColor boundary_color_ = {0.5, 0.5, 0.5, 1};
    float color_timer_ = 0;

    HUDButton* buttron_start_ = nullptr;
    HUDButton* buttron_credits_ = nullptr;
    HUDButton* buttron_quit_ = nullptr;

    HUDText* credits_text_ = nullptr;

public:
    virtual void init() override;
    virtual void handleEvents(SDL_Event& event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

private:
    void renderBackground();
    void updateColor();

    void checkButtonStart();
    void checkButtonCredits();
    void checkButtonQuit();
};





#endif // SCENE_TITLE_H