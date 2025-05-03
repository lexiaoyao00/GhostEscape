#ifndef ASSET_STORE_H
#define ASSET_STORE_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <unordered_map>
#include <string>

class AssetStore
{
    SDL_Renderer* renderer_ = nullptr;
    std::unordered_map<std::string, SDL_Texture*> textures_;
    std::unordered_map<std::string, Mix_Music*> musics_;
    std::unordered_map<std::string, Mix_Chunk*> sounds_;
    std::unordered_map<std::string, TTF_Font*> fonts_;

public:
    AssetStore() = default;
    AssetStore(SDL_Renderer* renderer) : renderer_(renderer) {};
    ~AssetStore() = default;

    SDL_Texture* getTexture(const std::string& path);
    Mix_Music* getMusic(const std::string& path);
    Mix_Chunk* getSound(const std::string& path);
    TTF_Font* getFont(const std::string& path, int size);

    void loadTexture(const std::string& path);
    void loadMusic(const std::string& path);
    void loadSound(const std::string& path);
    void loadFont(const std::string& path, int size);

    void clean();
};



#endif // ASSET_STORE_H