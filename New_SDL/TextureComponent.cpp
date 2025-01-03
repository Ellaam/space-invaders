#include "TextureComponent.h"
#include "TransformComponent.h"
#include "ResourceManager.h"
#include "GameEntity.h"


TextureComponent::TextureComponent() {}

void TextureComponent::CreateTextureComponent(SDL_Renderer* renderer, std::string filepath) {
    mTexture = ResourceManager::Instance().LoadTexture(renderer, filepath);
}

TextureComponent::~TextureComponent() {}

ComponentType TextureComponent::GetType() {
    return ComponentType::TextureComponent;
}

void TextureComponent::Input(float deltaTime) {}
void TextureComponent::Update(float deltaTime) {}
void TextureComponent::Render(SDL_Renderer* renderer) {
    if (nullptr == mTexture) {
        auto ge = GetGameEntity();
        auto transform = ge->GetTransform()->GetRectangle();
        SDL_RenderRect(renderer, &transform);
    }
    else {
        auto ge = GetGameEntity();
        auto transform = ge->GetTransform()->GetRectangle();

        SDL_RenderTexture(renderer, mTexture.get(), nullptr, &transform);
    }
}

void TextureComponent::UpdateTextureComponent(SDL_Renderer* renderer, std::string filepath) {
    mTexture = ResourceManager::Instance().LoadTexture(renderer, filepath);
}




