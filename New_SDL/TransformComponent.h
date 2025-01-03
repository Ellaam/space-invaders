#pragma once

#include <SDL3\SDL.h>
#include <memory>
#include <string>
#include "Component.h"

struct TransformComponent : public Component {
    TransformComponent();
    ~TransformComponent();

    ComponentType GetType() override;

    void Input(float deltaTime) override;
    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) override;

    void SetW(float w);
    void SetH(float h);
    void SetWH(float w, float h);

    void SetX(float x);
    void SetY(float y);
    void SetXY(float x, float y);

    float GetW() const;
    float GetH() const;

    float GetX() const;
    float GetY() const;

    SDL_FRect GetRectangle() const;

private:
    SDL_FRect mRectangle{ 20.0f,20.0f,32.0f,32.0f };
};
