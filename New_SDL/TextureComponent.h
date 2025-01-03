#pragma once
#include <SDL3\SDL.h>
#include <memory>
#include <string>
#include "Component.h"
#include "ComponentType.h"


struct TextureComponent : public Component {
	TextureComponent();
	~TextureComponent();

	void CreateTextureComponent(SDL_Renderer* renderer, std::string filepath);
	void UpdateTextureComponent(SDL_Renderer* renderer, std::string filepath);
	
	ComponentType GetType() override;

	void Input(float deltaTime) override;
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* renderer) override;

private:
	std::shared_ptr<SDL_Texture> mTexture;
};

