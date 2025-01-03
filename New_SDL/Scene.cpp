#include "Scene.h"
#include "Application.h"
#include "InputComponent.h"

Scene::Scene(){
    SDL_Log("Starting at Level: %d", mPlayerLevel);
    SDL_Log("Health: %i", mLife);
}

Scene::~Scene() {
    Shutdown();
}

void Scene::StartUp(SDL_Renderer* renderer) {

    mRenderer = renderer;
    // Initializing all the enemies
    int row = 1;
    int column = 1;
    for (int i = 0; i < 36; i++) {
        std::shared_ptr<EnemyGameEntity> e = std::make_shared<EnemyGameEntity>(mRenderer);
        e->AddDefaultTransform();

        //Adding a texture component to each enemy
        std::shared_ptr<TextureComponent> tex = std::make_shared<TextureComponent>();
        tex->CreateTextureComponent(mRenderer, "enemy.bmp");
        e->AddComponent(tex);

        std::shared_ptr<Collision2DComponent> col = std::make_shared< Collision2DComponent>();
        e->AddComponent(col);

        //Calculating position for enemies
        if (i % 12 == 0) {
            ++row;
            column = 0;
        }

        column++;
        e->GetTransform()->SetXY(column * 40 + 50, row * 40);
        //Adding a child game object to the enemies
        // Create a texture and a collider for the projectile
        std::shared_ptr<TextureComponent> mProjectile_texture = std::make_shared<TextureComponent>();
        mProjectile_texture->CreateTextureComponent(renderer, "test.bmp");
        std::shared_ptr<Collision2DComponent> mProjectile_col = std::make_shared<Collision2DComponent>();
        std::shared_ptr<Projectile>mProjectile = std::make_shared<Projectile>();

        mProjectile->AddDefaultTransform();
        mProjectile->GetTransform()->SetW(10.0f);
        mProjectile->AddComponent(mProjectile_texture);
        mProjectile->AddComponent(mProjectile_col);
        e->AddChildGameEntity(mProjectile);

        //Add  each enemy to the collection of GameEntities
        enemies.push_back(std::move(e));
    }

    mainCharacter = std::make_shared<GameEntity>();
    mainCharacter->AddDefaultTransform();

    std::shared_ptr<TextureComponent> characterTexture = std::make_shared<TextureComponent>();
    characterTexture->CreateTextureComponent(mRenderer, "hero.bmp");
    mainCharacter->AddComponent(characterTexture);

    mainCharacter->GetTransform()->SetXY(640 / 2 - (32 / 2), 440);

    std::shared_ptr<InputComponent> inputController = std::make_shared<InputComponent>();
    mainCharacter->AddComponent(inputController);

    std::shared_ptr<Collision2DComponent> col = std::make_shared< Collision2DComponent>();
    mainCharacter->AddComponent(col);

    // For the main character, adding one child component
    // Create a texture and a collider for the maincharacter projectile
    std::shared_ptr<TextureComponent> mainCharacterProjectileTexture = std::make_shared<TextureComponent>();
    mainCharacterProjectileTexture->CreateTextureComponent(renderer, "test.bmp");
    std::shared_ptr<Collision2DComponent> mainCharacterProjectileCollider = std::make_shared<Collision2DComponent>();
    std::shared_ptr<Projectile>mainCharacterProjectile = std::make_shared<Projectile>();
    mainCharacterProjectile->AddDefaultTransform();
    mainCharacterProjectile->GetTransform()->SetW(10.0f);
    mainCharacterProjectile->AddComponent(mainCharacterProjectileTexture);
    mainCharacterProjectile->AddComponent(mainCharacterProjectileCollider);
    mainCharacter->AddChildGameEntity(mainCharacterProjectile);
}

void Scene::Shutdown() {}

void Scene::Input(float deltaTime) {
    // Handle SDL_GetKeyboardState after -- SDL_PollEvent
    mainCharacter->Input(deltaTime);
}

void Scene::Update(SDL_Renderer* renderer, float deltaTime) {
    // Updating the main character
    mainCharacter->Update(deltaTime);

    // Updating all enemies
    for (int i = 0; i < enemies.size(); i++) {
        
        enemies[i]->Update(deltaTime);

        std::shared_ptr<Projectile> enemyProjectile = dynamic_pointer_cast<Projectile>(enemies[i]->GetChildGameEntityAtIndex(0));
        std::shared_ptr<Projectile> mainProjectile = dynamic_pointer_cast<Projectile>(mainCharacter->GetChildGameEntityAtIndex(0));

        bool enemyIsHit = enemies[i]->Intersects(mainProjectile);
        if (true == enemyIsHit) {
            auto textureComponent = enemies[i]->GetComponent<TextureComponent>(ComponentType::TextureComponent);
            if (textureComponent) {
                textureComponent->UpdateTextureComponent(mRenderer, "damaged.bmp"); 
            }
            enemies[i]->SetDamaged(true);

            int currentHealth = enemies[i]->GetEnemyHealth();

            if (currentHealth > 0) {
                currentHealth--;
                enemies[i]->SetEnemyHealth(currentHealth);
                mainProjectile->Launch(500.0f, 500.0f, true, 0);
            }
            else {
            }
        }
        
        bool GameOver = false;
        bool GotKilled = mainCharacter->Intersects(enemyProjectile);
   
        if (enemies[i]->GetEnemyHealth() == 0 && enemies[i]->IsRenderable() == true) {
            enemies[i]->SetRenderable(false);
            mEnemyKilled += 1;
            mPoints += 1;
            mainProjectile->Launch(500.0f, 500.0f, true, 0);
            enemies[i]->SetEnemyDead();
            SDL_Log("Score: %i", mPoints);
           }
         
        if (enemies[i]->IsRenderable() && GotKilled) {
            if (mLife > 0 ){
                mLife--;
                SDL_Log("You lost a life. Your health: %i", mLife);
                mainProjectile->Launch(500.0f, 500.0f, true, 0);
                ResetEnemyPositions();
                break;
            }
            else if (mLife==0) {
                GameOver = true;
            }
        }
        if (true == GameOver) {
            SDL_Log("YOU DIED!");
            SDL_Log("Your score is %i", mPoints);
            SDL_Log("Enemy %i got you", i);
            mSceneIsActive = false;
            break;
        }
        
        if (mEnemyKilled == enemies.size()) {
            SDL_Log("You've been leveled up!");
            
            mEnemyKilled = 0;
            mPlayerLevel++;
            leveledUp = true;
            
            SDL_Log("Now, enemies are stronger, each will be killed after getting hit %i times!", mPlayerLevel);
            SDL_Log("player level is %i", mPlayerLevel);
            for (int i = 0; i < enemies.size(); i++) {
                enemies[i]->SetEnemyHealth(mPlayerLevel);
            }

            ResetEnemyPositions();
        }
    }
}

void Scene::Render() {
    SDL_SetRenderDrawColor(mRenderer, 32, 32, 64, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(mRenderer);

    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    // Render  enemies
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i]->Render(mRenderer);
    }
    // Render main character
    mainCharacter->Render(mRenderer);
    SDL_RenderPresent(mRenderer);
}

void Scene::SetScenceActiveStatus(bool status) {
    mSceneIsActive = status;
}

bool Scene::IsSceneActive() const {
    return mSceneIsActive;
}

void Scene::ResetEnemyPositions() {
    for (int i = 0; i < enemies.size(); i++) {
        auto textureComponent = enemies[i]->GetComponent<TextureComponent>(ComponentType::TextureComponent);

        if (enemies[i]->GetEnemyHealth() > 0) {
            enemies[i]->SetRenderable(true);
            // If leveled up, reset texture to default
            if (leveledUp) {
                enemies[i]->SetDamaged(false);
                if (textureComponent) {
                    textureComponent->UpdateTextureComponent(mRenderer, "enemy.bmp");
                }
            }
            else if (enemies[i]->IsDamaged() && textureComponent) {
                // Only set damaged texture if it's already damaged and not leveled up
                textureComponent->UpdateTextureComponent(mRenderer, "damaged.bmp");
            }
        }

        // Reset the enemy's projectile position
        int randomDelay = rand() % 1000 + 300;
        std::shared_ptr<Projectile> enemyProjectile = dynamic_pointer_cast<Projectile>(enemies[i]->GetChildGameEntityAtIndex(0));
        if (enemyProjectile) {
            enemyProjectile->GetTransform()->SetXY(500,500); // Reset to a default position relative to the enemy
            enemyProjectile->Launch(500, 500, false, randomDelay);
        }
    }

    // Reset player position
    mainCharacter->GetTransform()->SetXY(640 / 2 - (32 / 2), 440);

    // Reset leveledUp after processing all enemies
    leveledUp = false;
}

