#pragma once
#include <SDL3\SDL.h>
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "Component.h"
#include "ComponentType.h"
#include "InputComponent.h"
#include "TextureComponent.h"
#include "Collision2DComponent.h"
#include <map>
#include <memory>
#include <vector>



struct GameEntity: public std::enable_shared_from_this<GameEntity> {

    GameEntity(); 

    virtual ~GameEntity();

    std::shared_ptr<GameEntity> GetThisPtr() {
        return shared_from_this();
    }

    virtual void Input(float deltaTime);
    virtual void Update(float deltaTime);
    virtual void Render(SDL_Renderer* renderer);


    template<typename T>
    void AddComponent(std::shared_ptr<T> c);

    template<typename T>
    std::shared_ptr<T> GetComponent(ComponentType type);

    void AddDefaultTransform();

    /// Could make this const
    ///This is a special case of GetComponent because
    /// every GameEntity will have a TransformComponent
    std::shared_ptr<TransformComponent> GetTransform();

    void AddChildGameEntity(std::shared_ptr<GameEntity> child);
    std::shared_ptr<GameEntity> GetChildGameEntityAtIndex(size_t index);

    void SetRenderable(bool value);
    bool IsRenderable() const;
    bool Intersects(std::shared_ptr<GameEntity> e);

protected:
    std::map<ComponentType, std::shared_ptr<Component>> mComponents;
    bool mRenderable{ true };

    // Game Entity Children
    std::vector<std::shared_ptr<GameEntity>> mGameEntities;
};


