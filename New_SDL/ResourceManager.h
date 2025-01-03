#pragma once
#include <SDL3\SDL.h>
#include <unordered_map>
#include <memory>
#include <string>


// Functor
struct TextureFunctorDeleter {
    void operator()(SDL_Texture* texture) const {
        SDL_DestroyTexture(texture);
    }
};

std::shared_ptr<SDL_Texture> make_shared_texture(SDL_Renderer* renderer, SDL_Surface* pixels);

struct ResourceManager {
    static ResourceManager& Instance();
    std::shared_ptr<SDL_Texture> LoadTexture(SDL_Renderer* renderer, std::string filepath);

private:
    ResourceManager() {}
    static ResourceManager* mInstance;
    std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> mTextureResources;
};


