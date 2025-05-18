#include "game.h"
#include "../scene_main.h"
#include "../scene_title.h"
#include "object_screen.h"
#include "object_world.h"
#include "actor.h"
#include "asset_store.h"
#include "../affiliate/sprite.h"
#include <fstream>

void Game::run()
{
    while (is_running_){
        auto start = SDL_GetTicksNS();
        if (next_scene_)
        {
            changeScene(next_scene_);
            next_scene_ = nullptr;
        }
        handleEvents();
        update(dt_);
        render();
        auto end = SDL_GetTicksNS();
        auto elapsed = end - start;
        if (elapsed < frame_delay_){
            SDL_DelayNS((frame_delay_ - elapsed)); // 等待剩余时间
            dt_ = frame_delay_ / 1.0e9;
        }
        else{
            dt_ = elapsed / 1.0e9;
        }
    }
}

void Game::init(std::string title, int width, int height)
{
    screan_size_ = glm::vec2(width, height);
    // SDL3 初始化
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init Error: %s", SDL_GetError());
    }

    // 不需要进行 SDL_image 初始化
    // mixer 初始化
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG)){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_Init Error: %s", SDL_GetError());
    }
    if (!Mix_OpenAudio(0,NULL)){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_OpenAudio Error: %s", SDL_GetError());
    }
    Mix_AllocateChannels(16);   // 分配16个通道
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);  // 设置音乐音量
    Mix_Volume(-1, MIX_MAX_VOLUME / 4);  // 设置音效音量

    //SDL_TTF 初始化
    if (!TTF_Init()){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_Init Error: %s", SDL_GetError());
    }

    //创建窗口与渲染器
    SDL_CreateWindowAndRenderer(title.c_str(), width, height, SDL_WINDOW_RESIZABLE, &window_, &renderer_);
    if (!window_ || !renderer_){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindowAndRenderer Error: %s", SDL_GetError());
    }

    // 设置窗口逻辑分辨率
    SDL_SetRenderLogicalPresentation(renderer_,width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    ttf_engine_ = TTF_CreateRendererTextEngine(renderer_);

    // 计算帧延迟
    frame_delay_ = 1000000000 / FPS; // 60 FPS

    // 创建资源管理器
    asset_store_ = new AssetStore(renderer_);

    // 创建场景
    current_scene_ = new SceneTitle();
    current_scene_->init();
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_EVENT_QUIT:
                is_running_ = false;
                break;
            default:
                current_scene_->handleEvents(event);
                break;
        }
    }
}

void Game::update(float dt)
{
    mouse_buttons_ = SDL_GetMouseState(&mouse_position_.x, &mouse_position_.y);
    current_scene_->update(dt);
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);

    current_scene_->render();

    SDL_RenderPresent(renderer_);
}

void Game::clean()
{
    if (current_scene_ != nullptr){
        delete current_scene_;
        current_scene_ = nullptr;
    }

    if (asset_store_ != nullptr){
        delete asset_store_;
        asset_store_ = nullptr;
    }

    if (ttf_engine_ != nullptr){
        TTF_DestroyRendererTextEngine(ttf_engine_);
        ttf_engine_ = nullptr;
    }

    // 释放渲染器和窗口
    if (renderer_)
    {
        SDL_DestroyRenderer(renderer_);
    }
    if (window_)
    {
        SDL_DestroyWindow(window_);
    }
    // 退出Mix
    Mix_CloseAudio();
    Mix_Quit();
    // 退出TTF
    TTF_Quit();
    // 退出SDL
    SDL_Quit();
}

void Game::setScore(int score)
{
    score_ = score;
    if (score_ > high_score_){
        high_score_ = score_;
    }
}

void Game::addScore(int score)
{
    setScore(score_ + score);
}

void Game::changeScene(Scene *scene)
{
    current_scene_->clean();
    if (current_scene_ != nullptr){
        delete current_scene_;
    }
    current_scene_ = scene;
    current_scene_->init();
}

void Game::renderTexture(const Texture &texture, const glm::vec2 &position, const glm::vec2 &size, const glm::vec2 &mask)
{
    SDL_FRect src_rect = {
        texture.src_rect.x,
        texture.src_rect.y + texture.src_rect.h * (1 - mask.y),
        texture.src_rect.w * mask.x,
        texture.src_rect.h * mask.y
    };
    SDL_FRect dst = {
        position.x,
        position.y + size.y * (1 - mask.y),
        size.x * mask.x,
        size.y * mask.y
    };
    SDL_RenderTextureRotated(renderer_, texture.texture, &src_rect, &dst, texture.angle, nullptr, texture.is_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Game::renderFillCircle(const glm::vec2 &position, const glm::vec2 &size, float alpha)
{
    auto texture = asset_store_->getTexture("assets/UI/circle.png");
    SDL_FRect dst = {
        position.x,
        position.y,
        size.x,
        size.y
    };
    SDL_SetTextureAlphaModFloat(texture, alpha);
    SDL_RenderTexture(renderer_, texture, NULL, &dst);
}

void Game::renderHBar(const glm::vec2 &position, const glm::vec2 &size, float percent, SDL_FColor color)
{
    SDL_SetRenderDrawColorFloat(renderer_, color.r, color.g, color.b, color.a);
    SDL_FRect boundary_rect = {
        position.x,
        position.y,
        size.x,
        size.y
    };
    SDL_FRect fill_rect = {
        position.x,
        position.y,
        size.x * percent,
        size.y
    };
    SDL_RenderRect(renderer_, &boundary_rect);
    SDL_RenderFillRect(renderer_, &fill_rect);
    SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1);
}

TTF_Text *Game::creatTTF_Text(const std::string &text, const std::string &font_path, int font_size)
{
    auto font = asset_store_->getFont(font_path, font_size);
    return TTF_CreateText(ttf_engine_, font, text.c_str(), 0);
}

bool Game::isMouseInRect(const glm::vec2 &top_left, const glm::vec2 &bottom_right)
{
    return mouse_position_.x >= top_left.x && mouse_position_.x <= bottom_right.x && mouse_position_.y >= top_left.y && mouse_position_.y <= bottom_right.y;
}

std::string Game::loadTextFile(const std::string &path)
{
    std::ifstream file(path);
    std::string line, content;

    while (std::getline(file, line)){
        content += line + "\n";
    }
    return content;
}

void Game::drawGrid(const glm::vec2 &top_left, const glm::vec2 &bottom_right, float grid_width, SDL_FColor fcolor)
{
    SDL_SetRenderDrawColorFloat(renderer_, fcolor.r, fcolor.g, fcolor.b, fcolor.a);
    for (float x = top_left.x; x <= bottom_right.x; x += grid_width){
        SDL_RenderLine(renderer_, x, top_left.y, x, bottom_right.y);
    }
    for (float y = top_left.y; y <= bottom_right.y; y += grid_width){
        SDL_RenderLine(renderer_, top_left.x, y, bottom_right.x, y);
    }

    SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1);
}

void Game::drawBoundary(const glm::vec2 &top_left, const glm::vec2 &bottom_right, float grid_width, SDL_FColor fcolor)
{
    SDL_SetRenderDrawColorFloat(renderer_, fcolor.r, fcolor.g, fcolor.b, fcolor.a);
    for (float i = 0; i < grid_width; i++)
    {
        SDL_FRect rect = {
            top_left.x - i,
            top_left.y - i,
            bottom_right.x - top_left.x + 2 * i,
            bottom_right.y - top_left.y + 2 * i
        };
        SDL_RenderRect(renderer_, &rect);
    }
    SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1);
}
