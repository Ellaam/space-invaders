#include "Collision2DComponent.h"
#include "GameEntity.h"

Collision2DComponent::Collision2DComponent() {}
Collision2DComponent::~Collision2DComponent() {}

void Collision2DComponent::Input(float deltaTime) {}

void Collision2DComponent::Update(float deltaTime) {
    // Default behavior will be to just update the
    // Collision2DComponent with the objects transform.
    auto transform = GetGameEntity()->GetTransform();
    SetWH(transform->GetW(), transform->GetH());
    SetXY(transform->GetX(), transform->GetY());
}

void Collision2DComponent::Render(SDL_Renderer* renderer) {
    // Useful for debugging purposes
    //SDL_RenderRect(renderer, &mRectangle);
}

ComponentType Collision2DComponent::GetType() {
    return ComponentType::Collision2DComponent;
}

void Collision2DComponent::SetW(float w) {
    mRectangle.w = w;
}

void Collision2DComponent::SetH(float h) {
    mRectangle.h = h;
}

void Collision2DComponent::SetWH(float w, float h) {
    mRectangle.w = w;
    mRectangle.h = h;
}

float Collision2DComponent::GetW() const {
    return mRectangle.w;
}

float Collision2DComponent::GetH() const {
    return mRectangle.h;
}

void Collision2DComponent::SetX(float x) {
    mRectangle.x = x;
}

void Collision2DComponent::SetY(float y) {
    mRectangle.y = y;
}

void Collision2DComponent::SetXY(float x, float y) {
    mRectangle.x = x;
    mRectangle.y = y;
}

float Collision2DComponent::GetX() const {
    return mRectangle.x;
}

float Collision2DComponent::GetY() const {
    return mRectangle.y;
}

SDL_FRect Collision2DComponent::GetRectangle() const {
    return mRectangle;
}
