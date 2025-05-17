#ifndef HUD_STATS_H
#define HUD_STATS_H


#include "../core/object_screen.h"

class Sprite;
class Actor;
class HUDStats : public ObjectScreen
{
protected:
    Actor* target_ = nullptr;

    Sprite* health_bar_ = nullptr;
    Sprite* health_bar_bg_ = nullptr;
    Sprite* health_icon_ = nullptr;
    float health_percentage_ = 1.0f;

    Sprite* mana_bar_ = nullptr;
    Sprite* mana_bar_bg_ = nullptr;
    Sprite* mana_icon_ = nullptr;
    float mana_percentage_ = 1.0f;

public:
    static HUDStats* addHUDStatsChild(Object* parent,Actor* target, glm::vec2 render_position);

    virtual void init() override;
    virtual void update(float dt) override;

    // getters and setters
    Actor* getTarget() { return target_; }
    void setTarget(Actor* target) { target_ = target; }

    Sprite* getHealthBar() { return health_bar_; }
    Sprite* getHealthBarBg() { return health_bar_bg_; }
    Sprite* getHealthIcon() { return health_icon_; }
    float getHealthPercentage() { return health_percentage_; }
    void setHealthBar(Sprite* bar) { health_bar_ = bar; }
    void setHealthBarBg(Sprite* bar_bg) { health_bar_bg_ = bar_bg; }
    void setHealthIcon(Sprite* icon) { health_icon_ = icon; }
    void setHealthPercentage(float percentage) { health_percentage_ = percentage; }

    Sprite* getManaBar() { return mana_bar_; }
    Sprite* getManaBarBg() { return mana_bar_bg_; }
    Sprite* getManaIcon() { return mana_icon_; }
    float getManaPercentage() { return mana_percentage_; }
    void setManaBar(Sprite* bar) { mana_bar_ = bar; }
    void setManaBarBg(Sprite* bar_bg) { mana_bar_bg_ = bar_bg; }
    void setManaIcon(Sprite* icon) { mana_icon_ = icon; }
    void setManaPercentage(float percentage) { mana_percentage_ = percentage; }

private:
    void updateHealthBar();
    void updateManaBar();
};


#endif // HUD_STATS_H