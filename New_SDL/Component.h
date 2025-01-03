#pragma once
#include <SDL3\SDL.h>
#include "ComponentType.h"
#include <memory>

//Forward declaration of GameEntity which is inlcuded in the Components
struct GameEntity;

//Components must know about the gameEntity that they are associaated with

struct Component
{
	Component() {}
	virtual ~Component() {}

	virtual void Update(float deltaTime) {}
	virtual void Input(float deltaTime) {}
	virtual void Render(SDL_Renderer* renderer) {}

	//Components must have a type
	virtual ComponentType GetType() = 0;

	void SetGameEntity(std::shared_ptr<GameEntity> g) {
		mGameEntity = g;
	}
	std::shared_ptr<GameEntity> GetGameEntity() {
		return mGameEntity;
	}
private:
	std::shared_ptr<GameEntity> mGameEntity;
};

