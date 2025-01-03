#include "EnemyGameEntity.h"

EnemyGameEntity::EnemyGameEntity(SDL_Renderer* renderer) {

    // Set a random launch time for the enemies
    mMinLaunchTime += std::rand() % 30000;
}

EnemyGameEntity::~EnemyGameEntity() {
}

void EnemyGameEntity::Input(float deltaTime) {
    for (auto& [key, value] : mComponents) {
        mComponents[key]->Input(deltaTime);
    }
    for (auto& childern : mGameEntities) {
        childern->Input(deltaTime);
    }
}

void EnemyGameEntity::Update(float deltaTime) {
    // Zero is my projectile
    std::shared_ptr<Projectile> mProjectile = dynamic_pointer_cast<Projectile>(GetChildGameEntityAtIndex(0));

    if (offset > 80) {
        xPositiveDirection = false;
    }
    if (offset < -80) {
        xPositiveDirection = true;
    }

    // Keeping track of the projectile game logic
    auto transform = GetComponent<TransformComponent>(ComponentType::TransformComponent);

    if (xPositiveDirection) {
        transform->SetX(transform->GetX() + mSpeed * deltaTime);
        offset += mSpeed * deltaTime;
    }
    else {
        transform->SetX(transform->GetX() - mSpeed * deltaTime);
        offset -= mSpeed * deltaTime;
    }

    if (mRenderable) {
        mProjectile->Launch(transform->GetX(), transform->GetY(), false, mMinLaunchTime);
    }

    for (auto& [key, value] : mComponents) {
        mComponents[key]->Update(deltaTime);
    }
    for (auto& childern : mGameEntities) {
        childern->Update(deltaTime);
    }
}

void EnemyGameEntity::Render(SDL_Renderer* renderer) {
    std::shared_ptr<Projectile> mProjectile = dynamic_pointer_cast<Projectile>(GetChildGameEntityAtIndex(0));
    if (mRenderable) {
        mProjectile->Render(renderer);
    }
    else {
        // Do nothing;
        mProjectile->SetRenderable(false);
        return;
    }
    for (auto& [key, value] : mComponents) {
        mComponents[key]->Render(renderer);
    }
    for (auto& childern : mGameEntities) {
        childern->Render(renderer);
    }
}

void EnemyGameEntity::SetEnemyHealth(int life) {
    mEnemyLife = life;
}

int EnemyGameEntity::GetEnemyHealth() const{
    return mEnemyLife;
}

void EnemyGameEntity::SetEnemySpeed(float speed) {
    mSpeed = mSpeed * speed;
}

bool EnemyGameEntity::EnemyIsAlive() {
    return mIsAlive;
}

void EnemyGameEntity::SetEnemyDead() {
    mIsAlive = false;
}
void EnemyGameEntity::SetDamaged(bool damaged) {
    isDamaged = damaged;
}

bool EnemyGameEntity::IsDamaged() const {
    return isDamaged;
}