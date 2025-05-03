#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>

#include <string>

#include "asset_store.h"


class Scene;
class Game
{
    AssetStore* asset_store_ = nullptr; // 资源管理器
    glm::vec2 screan_size_ = glm::vec2(0);
    bool is_running_ = true;
    Scene* current_scene_ = nullptr; // 当前场景

    Uint64 FPS = 60;    // 帧率
    Uint64 frame_delay_ = 0; // 帧延迟,单位纳秒
    float dt_ = 0.0f; // 帧间隔

    SDL_Window* window_ = nullptr;  //  窗口
    SDL_Renderer* renderer_ = nullptr;  // 渲染器

    Game() = default;
    ~Game() = default;
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

public:
    static Game& GetInstance()
    {
        static Game instance;
        return instance;
    }

    void run(); // 运行游戏,进入主循环
    void init(std::string title, int width, int height); // 初始化游戏
    void handleEvents(); // 处理事件
    void update(float dt); // 更新游戏状态
    void render(); // 渲染游戏画面
    void clean(); // 清理游戏资源

    // getter and setter
    glm::vec2 getScreanSize() const { return screan_size_; }; // 获取屏幕大小
    Scene* getCurrentScene() const { return current_scene_; }; // 获取当前场景
    AssetStore* getAssetStore() const { return asset_store_; }; // 获取资源管理器

    // 工具函数
    void drawGrid(const glm::vec2& top_left, const glm::vec2& bottom_right, float grid_width, SDL_FColor fcolor); // 绘制网格
    void drawBoundary(const glm::vec2& top_left, const glm::vec2& bottom_right, float grid_width, SDL_FColor fcolor); // 绘制边界
};

#endif // GAME_H