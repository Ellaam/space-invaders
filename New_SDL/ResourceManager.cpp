#include "ResourceManager.h"

//Initializing static variable
ResourceManager* ResourceManager::mInstance = nullptr;

ResourceManager& ResourceManager::Instance() {
    if (nullptr == mInstance) {
        mInstance = new ResourceManager;
    }
    return *mInstance;
}

std::shared_ptr<SDL_Texture> ResourceManager::LoadTexture(SDL_Renderer* renderer, std::string filepath) {
    if (!mTextureResources.contains(filepath)) {
        SDL_Surface* pixels = SDL_LoadBMP(filepath.c_str());
        std::shared_ptr<SDL_Texture> texture = make_shared_texture(renderer, pixels);
        mTextureResources.insert({ filepath, texture });
        SDL_DestroySurface(pixels);
    }
    else {
        /*SDL_Log("Reused resource %s", filepath.c_str());*/
    }
    return mTextureResources[filepath];
}

std::shared_ptr<SDL_Texture> make_shared_texture(SDL_Renderer* renderer, SDL_Surface* pixels) {
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(renderer, pixels);

    if (nullptr == pTexture) {
        SDL_Log("Could not load texture from surface");
    }

    return std::shared_ptr<SDL_Texture>(pTexture, TextureFunctorDeleter());
}
