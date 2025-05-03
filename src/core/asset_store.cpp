#include "asset_store.h"

SDL_Texture *AssetStore::getTexture(const std::string &path)
{
    auto it = textures_.find(path);
    if (it == textures_.end())
    {
        loadTexture(path);
        it = textures_.find(path);
    }
    if (it == textures_.end())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load texture: %s", path.c_str());
        return nullptr;
    }
    return it->second;
}

Mix_Music *AssetStore::getMusic(const std::string &path)
{
    auto it = musics_.find(path);
    if (it == musics_.end())
    {
        loadMusic(path);
        it = musics_.find(path);
    }
    if (it == musics_.end())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load music: %s", path.c_str());
        return nullptr;
    }
    return it->second;
}

Mix_Chunk *AssetStore::getSound(const std::string &path)
{
    auto it = sounds_.find(path);
    if (it == sounds_.end())
    {
        loadSound(path);
        it = sounds_.find(path);
    }
    if (it == sounds_.end())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load sound: %s", path.c_str());
        return nullptr;
    }
    return it->second;
}

TTF_Font *AssetStore::getFont(const std::string &path, int size)
{
    auto it = fonts_.find(path + std::to_string(size));
    if (it == fonts_.end())
    {
        loadFont(path,size);
        it = fonts_.find(path + std::to_string(size));
    }
    if (it == fonts_.end())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load font: %s", path.c_str());
        return nullptr;
    }
    return it->second;
}


void AssetStore::loadTexture(const std::string &path)
{
    SDL_Texture *texture = IMG_LoadTexture(renderer_, path.c_str());
    if (texture == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load texture: %s", path.c_str());
        return;
    }
    // textures_[path] = texture;
    textures_.emplace(path, texture);   // 不覆盖
}

void AssetStore::loadMusic(const std::string &path)
{
    Mix_Music *music = Mix_LoadMUS(path.c_str());
    if (music == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load music: %s", path.c_str());
        return;
    }
    // musics_[path] = music;
    musics_.emplace(path, music);
}

void AssetStore::loadSound( const std::string &path)
{
    Mix_Chunk *sound = Mix_LoadWAV(path.c_str());
    if (sound == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load sound: %s", path.c_str());
        return;
    }
    // sounds_[path] = sound;
    sounds_.emplace(path, sound);
}

void AssetStore::loadFont(const std::string &path, int size)
{
    TTF_Font *font = TTF_OpenFont(path.c_str(), size);
    if (font == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load font: %s", path.c_str());
        return;
    }
    // fonts_[path] = font;
    fonts_.emplace(path + std::to_string(size), font);
}

void AssetStore::clean()
{
    for (auto &texture : textures_)
    {
        SDL_DestroyTexture(texture.second);
    }
    textures_.clear();

    for (auto &music : musics_)
    {
        Mix_FreeMusic(music.second);
    }
    musics_.clear();

    for (auto &sound : sounds_)
    {
        Mix_FreeChunk(sound.second);
    }
    sounds_.clear();

    for (auto &font : fonts_)
    {
        TTF_CloseFont(font.second);
    }
    fonts_.clear();
}
