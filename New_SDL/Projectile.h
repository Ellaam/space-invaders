#pragma once
#include <SDL3\SDL.h>
#include "TextureComponent.h"
#include "GameEntity.h"


struct Projectile : public GameEntity {

    Projectile();

    void Launch(float x, float y, bool yDirectionIsUp, int minlaunchtime = 300);

    void Input(float deltaTime) override;
    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) override;

private:
    float mSpeed{200.0f};
    bool mIsFiring{ false };
    bool mYDirectionUp{ true };
    Uint64 timeSinceLastLaunch;
};

