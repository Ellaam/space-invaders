#pragma once
#include <SDL3\SDL.h>
#include "GameEntity.h"
#include "Projectile.h"
#include "TextureComponent.h"


struct EnemyGameEntity : public GameEntity {

    EnemyGameEntity(SDL_Renderer* renderer);

    virtual ~EnemyGameEntity();

    virtual void Input(float deltaTime) override;
    virtual void Update(float deltaTime) override;
    virtual void Render(SDL_Renderer* renderer);
    void SetEnemyHealth(int life);
    int GetEnemyHealth() const;
    void SetEnemySpeed(float speed);
    bool EnemyIsAlive();
    void SetEnemyDead();
    void SetDamaged(bool damaged);
    bool IsDamaged() const;


private:

    float offset{ 0.0f };
    float mSpeed{ 80.0f };
    float mMinLaunchTime{ 5000.0f };
    int mEnemyLife{ 1 };
    bool xPositiveDirection{ true };
    bool mIsAlive{ true };
    bool isDamaged{ false };

};

