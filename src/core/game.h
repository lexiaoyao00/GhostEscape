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
    AssetStore *asset_store_ = nullptr;    // 资源管理器
    glm::vec2 screan_size_ = glm::vec2(0); // 屏幕大小

    glm::vec2 mouse_position_ = glm::vec2(0); // 鼠标位置,屏幕坐标
    SDL_MouseButtonFlags mouse_buttons_ = 0;  // 鼠标按键状态

    bool is_running_ = true;         // 游戏是否运行
    Scene *current_scene_ = nullptr; // 当前场景
    Scene *next_scene_ = nullptr;    // 下一个场景

    Uint64 FPS = 60;         // 帧率
    Uint64 frame_delay_ = 0; // 帧延迟,单位纳秒
    float dt_ = 0.0f;        // 帧间隔

    int score_ = 0;      // 得分
    int high_score_ = 0; // 最高分

    SDL_Window *window_ = nullptr;         //  窗口
    SDL_Renderer *renderer_ = nullptr;     // 渲染器
    TTF_TextEngine *ttf_engine_ = nullptr; // 字体引擎

    // 随机数生成器
    std::mt19937 gen_ = std::mt19937(std::random_device{}());

    Game() = default;
    ~Game() = default;
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;

public:
    static Game &GetInstance()
    {
        static Game instance;
        return instance;
    }

    void run();                                          // 运行游戏,进入主循环
    void init(std::string title, int width, int height); // 初始化游戏
    bool handleEvents();                                 // 处理事件
    void update(float dt);                               // 更新游戏状态
    void render();                                       // 渲染游戏画面
    void clean();                                        // 清理游戏资源

    // getter and setter
    glm::vec2 getScreanSize() const { return screan_size_; };                // 获取屏幕大小
    Scene *getCurrentScene() const { return current_scene_; };               // 获取当前场景
    AssetStore *getAssetStore() const { return asset_store_; };              // 获取资源管理器
    glm::vec2 getMousePosition() const { return mouse_position_; };          // 获取鼠标位置,相对于屏幕
    SDL_MouseButtonFlags getMouseButtons() const { return mouse_buttons_; }; // 获取鼠标按键状态
    void setScore(int score);                                                // 设置得分
    void setHighScore(int high_score) { high_score_ = high_score; }          // 设置最高分
    int getScore() const { return score_; }                                  // 获取得分
    int getHighScore() const { return high_score_; }                         // 获取最高分

    void addScore(int score);                                   // 增加得分
    void quit() { is_running_ = false; }                        // 退出游戏
    void safeChangeScene(Scene *scene) { next_scene_ = scene; } // 安全切换场景
    void changeScene(Scene *scene);                             // 切换场景

    // 渲染函数
    void renderTexture(const Texture &texture, const glm::vec2 &position, const glm::vec2 &size, const glm::vec2 &mask = glm::vec2(1.0f)); // 渲染纹理
    void renderFillCircle(const glm::vec2 &position, const glm::vec2 &size, float alpha);
    void renderHBar(const glm::vec2 &position, const glm::vec2 &size, float percent, SDL_FColor color);               // 渲染水平条形进度条
    void drawGrid(const glm::vec2 &top_left, const glm::vec2 &bottom_right, float grid_width, SDL_FColor fcolor);     // 绘制网格
    void drawBoundary(const glm::vec2 &top_left, const glm::vec2 &bottom_right, float grid_width, SDL_FColor fcolor); // 绘制边界
    void drawPoint(const std::vector<glm::vec2>& points, glm::vec2 render_pos, SDL_FColor fcolor); // 绘制点

    // 文字函数
    TTF_Text *creatTTF_Text(const std::string &text, const std::string &font_path, int font_size = 16);

    // 工具函数
    bool isMouseInRect(const glm::vec2 &top_left, const glm::vec2 &bottom_right); // 判断鼠标是否在矩形内
    std::string loadTextFile(const std::string &path);                            // 读取文本文件

    // 音频函数
    void playMusic(const std::string &music_path, int loops = -1) { Mix_PlayMusic(asset_store_->getMusic(music_path), loops); } // 播放音乐
    void playSound(const std::string &sound_path) { Mix_PlayChannel(-1, asset_store_->getSound(sound_path), 0); }               // 播放音效
    void stopMusic() { Mix_HaltMusic(); }                                                                                       // 停止音乐
    void stopSound() { Mix_HaltChannel(-1); }                                                                                   // 停止音效
    void pauseMusic() { Mix_PauseMusic(); }                                                                                     // 暂停音乐
    void pauseSound() { Mix_Pause(-1); }                                                                                        // 暂停音效
    void resumeMusic() { Mix_ResumeMusic(); }                                                                                   // 恢复音乐
    void resumeSound() { Mix_Resume(-1); }                                                                                      // 恢复音效

    // 随机数生成函数
    float randomFloat(float min, float max) { return std::uniform_real_distribution<float>(min, max)(gen_); } // 生成随机浮点数
    int randomInt(int min, int max) { return std::uniform_int_distribution<int>(min, max)(gen_); }            // 生成随机整数

    glm::vec2 randomVec2(const glm::vec2 &top_left, const glm::vec2 &bottom_right)
    {
        return glm::vec2(randomFloat(top_left.x, bottom_right.x), randomFloat(top_left.y, bottom_right.y));
    }
    glm::ivec2 randomIVec2(const glm::ivec2 &top_left, const glm::ivec2 &bottom_right)
    {
        return glm::ivec2(randomInt(top_left.x, bottom_right.x), randomInt(top_left.y, bottom_right.y));
    }

private:
    void updateMouse();
};

#endif // GAME_H