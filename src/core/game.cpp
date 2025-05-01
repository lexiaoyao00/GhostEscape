#include "game.h"
#include "../scene_main.h"


void Game::run()
{
    while (is_running_){
        auto start = SDL_GetTicksNS();
        handleEvents();
        update(0.0f);
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

    // 计算帧延迟
    frame_delay_ = 1000000000 / FPS; // 60 FPS

    // 创建场景
    current_scene_ = new SceneMain();
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
