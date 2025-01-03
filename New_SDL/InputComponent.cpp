#include "InputComponent.h"
#include "GameEntity.h"
#include "Projectile.h"

InputComponent::InputComponent() {}
InputComponent::~InputComponent() {}

ComponentType InputComponent::GetType() {
    return ComponentType::InputComponent;
}

void InputComponent::Input(float deltaTime) {
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    // Keeping a reference to our first sprite
    auto ge = GetGameEntity();
    auto transform = ge->GetComponent<TransformComponent>(ComponentType::TransformComponent);

    // Getting the current position of the main character
    float currentX = transform->GetX();
    float currentY = transform->GetY();
    int characterWidth = 32;  // Setting the width of the character here
    int screenWidth = 640;    // Screen width
    int screenHeight = 480;   // Screen height

    if (state[SDL_SCANCODE_LEFT]) {
        currentX -= mSpeed * deltaTime;
        // Ensuring the character doesn't move beyond the left boundary
        if (currentX < 0) {
            currentX = 0;
        }
    }
    else if (state[SDL_SCANCODE_RIGHT]) {
        currentX += mSpeed * deltaTime;
        // Ensuring the character doesn't move beyond the right boundary
        if (currentX > screenWidth - characterWidth) {
            currentX = screenWidth - characterWidth;
        }
    }

    // Updating the character's position after applying boundaries
    transform->SetX(currentX);

    if (state[SDL_SCANCODE_UP]) {
        // Launch a projectile
        std::shared_ptr<Projectile> projectile = dynamic_pointer_cast<Projectile>(ge->GetChildGameEntityAtIndex(0));
        projectile->Launch(currentX, currentY, true);
    }
}


void InputComponent::Update(float deltaTime) {}
void InputComponent::Render(SDL_Renderer* renderer) {}
