#pragma once
#include <SDL3\SDL.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <memory>
#include "Scene.h"


// Handles the main game loop
struct Application {
    Application(int argc, char* argv[]);
    ~Application();

    // will call these two in the constructor and desstructor, to provide more control
    void StartUp();
    void Shutdown();


    void Input(float deltaTime);
    void Update(SDL_Renderer* renderer, float deltaTime);
    void Render();

    void Loop(float targetFPS);

private:
    
    // For now, I have just one scence
    Scene mScene;
    // creating a member variable for windows so other parts of the program can access it
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
};

