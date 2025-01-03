#pragma once

#include <SDL3\SDL.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <memory>

#include "TextureComponent.h"
#include "GameEntity.h"
#include "EnemyGameEntity.h"
#include "ComponentType.h"
#include "Component.h"


struct Scene {
Scene();
~Scene();

void StartUp(SDL_Renderer* renderer);
void Shutdown();
void Input(float deltaTime);
void Update(SDL_Renderer* renderer, float deltaTime);
void Render();
void SetScenceActiveStatus(bool status);
bool IsSceneActive() const;
void ResetEnemyPositions();

private:
    std::vector<std::shared_ptr<EnemyGameEntity>> enemies;
    std::shared_ptr<GameEntity> mainCharacter;

    int mPoints{ 0 };
    int mLife{ 3 };
    int mEnemyKilled{ 0 };
    int mPlayerLevel{ 1 };
    bool mSceneIsActive{ false };
    bool leveledUp{ false };
    SDL_Renderer* mRenderer;
};

