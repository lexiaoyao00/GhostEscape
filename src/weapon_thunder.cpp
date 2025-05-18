#include "weapon_thunder.h"
#include "world/spell.h"
#include "core/scene.h"
#include "core/actor.h"

void WeaponThunder::init()
{
    Weapon::init();

    auto scene = game_.getCurrentScene();
    auto pos = glm::vec2(game_.getScreanSize().x - 300.0f,30.f);
    hud_skill_ = HUDSkill::addHUDSkillChild(scene,"assets/UI/Electric-Icon.png",pos,0.14f,Anchor::CENTER);
}

void WeaponThunder::update(float dt)
{
    Weapon::update(dt);

    if (hud_skill_){
        hud_skill_->setPercentage(cooldown_timer_ / cooldown_);
    }
}

WeaponThunder *WeaponThunder::addWeaponThunderChild(Actor *parent, float cool_down_, float mana_cost_)
{
    auto weapon = new WeaponThunder();
    weapon->init();
    weapon->setParent(parent);
    weapon->setCooldown(cool_down_);
    weapon->setManaCost(mana_cost_);

    parent->addChild(weapon);

    return weapon;
}

bool WeaponThunder::handleEvents(SDL_Event &event)
{
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
        if (event.button.button == SDL_BUTTON_LEFT){
            if (canAttack()){
                game_.playSound("assets/sound/big-thunder.mp3");
                auto pos = game_.getMousePosition() + game_.getCurrentScene()->getCameraPosition();
                auto spell = Spell::addSpellChild(nullptr,"assets/effect/Thunderstrike w blur.png",pos,40.0f,3.0f,Anchor::CENTER);
                attack(pos,spell);

                return true;
            }
        }
    }
    return false;
}
