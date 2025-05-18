#include "spawner.h"
#include "enemy.h"
#include "world/effect.h"
#include "core/scene.h"

void Spawner::update(float dt)
{
    Object::update(dt);

    if (!target_ || !target_->getActive()) return;

    timer_ += dt;
    if (timer_ > interval_) {
        timer_ = 0;
        game_.playSound("assets/sound/silly-ghost-sound-242342.mp3");
        for (int i = 0; i < num_; ++i) {
            // spawn enemy
            auto pos = game_.randomVec2(
                game_.getCurrentScene()->getCameraPosition(),
                game_.getCurrentScene()->getCameraPosition() + game_.getScreanSize()
            );
            Enemy* enemy = Enemy::addEnemyChild(nullptr, pos, target_);
            Effect::addEffectChild(game_.getCurrentScene(), "assets/effect/184_3.png", pos, 1.0f, enemy);
        }
    }
}
