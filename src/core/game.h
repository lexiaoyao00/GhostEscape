#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>

#include <random>
#include <string>

#include "asset_store.h"

struct Texture;
class Scene;
class Game
{
    AssetStore* asset_store_ = nullptr; // 资源管理器
    glm::vec2 screan_size_ = glm::vec2(0);  // 屏幕大小

    glm::vec2 mouse_position_ = glm::vec2(0);    // 鼠标位置,屏幕坐标
    SDL_MouseButtonFlags mouse_buttons_ = 0; // 鼠标按键状态

    bool is_running_ = true; // 游戏是否运行
    Scene* current_scene_ = nullptr; // 当前场景

    Uint64 FPS = 60;    // 帧率
    Uint64 frame_delay_ = 0; // 帧延迟,单位纳秒
    float dt_ = 0.0f; // 帧间隔

    SDL_Window* window_ = nullptr;  //  窗口
    SDL_Renderer* renderer_ = nullptr;  // 渲染器

    // 随机数生成器
    std::mt19937 gen_ = std::mt19937(std::random_device{}());

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
    glm::vec2 getMousePosition() const { return mouse_position_; }; // 获取鼠标位置,相对于屏幕
    SDL_MouseButtonFlags getMouseButtons() const { return mouse_buttons_; }; // 获取鼠标按键状态

    // 渲染函数
    void renderTexture(const Texture& texture, const glm::vec2& position, const glm::vec2& size, const glm::vec2 &mask = glm::vec2(1.0f)); // 渲染纹理
    void renderFillCircle(const glm::vec2& position, const glm::vec2& size, float alpha);
    void renderHBar(const glm::vec2& position, const glm::vec2& size, float percent, SDL_FColor color); // 渲染水平条形进度条

    // 工具函数
    void drawGrid(const glm::vec2& top_left, const glm::vec2& bottom_right, float grid_width, SDL_FColor fcolor); // 绘制网格
    void drawBoundary(const glm::vec2& top_left, const glm::vec2& bottom_right, float grid_width, SDL_FColor fcolor); // 绘制边界

    // 随机数生成函数
    float randomFloat(float min, float max) { return std::uniform_real_distribution<float>(min, max)(gen_); } // 生成随机浮点数
    int randomInt(int min, int max) { return std::uniform_int_distribution<int>(min, max)(gen_); } // 生成随机整数

    glm::vec2 randomVec2(const glm::vec2& top_left, const glm::vec2& bottom_right) {
        return glm::vec2(randomFloat(top_left.x, bottom_right.x), randomFloat(top_left.y, bottom_right.y));
    }
    glm::ivec2 randomIVec2(const glm::ivec2& top_left, const glm::ivec2& bottom_right) {
        return glm::ivec2(randomInt(top_left.x, bottom_right.x), randomInt(top_left.y, bottom_right.y));
    }
};

#endif // GAME_H