#ifndef SPRITE_ANIME_H
#define SPRITE_ANIME_H


#include "sprite.h"

class SpriteAnime : public Sprite
{
    int current_frame_ = 0;
    int total_frames_ = 0;
    int fps_ = 10;
    float frame_timer_ = 0;
    bool is_loop_ = true;

public:
    static SpriteAnime* addSpriteAnimeChild(ObjectScreen* parent, const std::string& file_path,float scale = 1.0f, Anchor anchor = Anchor::CENTER);
    virtual void update(float dt) override;

    virtual void setTexture(Texture texture) override;

    // getters and setters
    void setTotalFrames(int total_frames) { total_frames_ = total_frames; }
    void setFps(int fps) { this->fps_ = fps; }
    void setFrameTimer(float frame_timer) { frame_timer_ = frame_timer; }
    void setCurrentFrame(int current_frame) { current_frame_ = current_frame; }
    void setLoop(bool is_loop) { is_loop_ = is_loop; }

    int getTotalFrames() { return total_frames_; }
    int getFps() { return fps_; }
    float getFrameTimer() { return frame_timer_; }
    int getCurrentFrame() { return current_frame_; }
    bool getLoop() { return is_loop_; }
};


#endif // SPRITE_ANIME_H