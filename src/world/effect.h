#ifndef EFFECT_H
#define EFFECT_H

#include "../core/object_world.h"
#include "../affiliate/sprite_anime.h"
#include <string>

class Effect : public ObjectWorld
{
    SpriteAnime *sprite_anime_ = nullptr;
    ObjectWorld *next_object_ = nullptr; // 播放完毕后添加到场景中去

public:
    static Effect *addEffectChild(Object *parent, const std::string &file_path, glm::vec2 pos, float scale = 1.0f, ObjectWorld *next_object = nullptr);

    virtual void update(float dt) override;

    // getters and setters
    SpriteAnime *getSpriteAnime() const { return sprite_anime_; }
    void setSpriteAnime(SpriteAnime *sprite_anime) { sprite_anime_ = sprite_anime; }
    ObjectWorld *getNextObject() const { return next_object_; }
    void setNextObject(ObjectWorld *next_object) { next_object_ = next_object; }

private:
    void checkFinish();
};

#endif // EFFECT_H