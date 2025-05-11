#ifndef SPELL_H
#define SPELL_H


#include "../core/object_world.h"
#include "../affiliate/sprite_anime.h"


class Spell : public ObjectWorld
{
protected:
    SpriteAnime *sprite_ = nullptr;
    float damage_ = 60.0f;
public:
    static Spell* addSpellChild(Object* parent, const std::string& file_path, glm::vec2 pos, float damage, float scale = 1.0f, Anchor anchor = Anchor::CENTER);
    virtual void update(float dt) override;

    void setSpriteAnime(SpriteAnime *sprite) { sprite_ = sprite; }

private:
    void attack();

};


#endif // SPELL_H