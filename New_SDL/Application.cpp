#include "Application.h"
#include "InputComponent.h"

Application::Application(int argc, char* argv[]) {
    StartUp();
}
Application::~Application() {
    Shutdown();
}

// Initialized the game
void Application::StartUp() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    }
    // Create a window
    SDL_Window* mWindow = SDL_CreateWindow("Space Invaders", 640, 480,
        SDL_WINDOW_OPENGL);
     
    mRenderer = SDL_CreateRenderer(mWindow, NULL);
    if (nullptr == mRenderer) {
        SDL_Log("Error creating renderer");
    }
    //Start setting up my scene with appropriate renderer
    mScene.StartUp(mRenderer);
    mScene.SetScenceActiveStatus(true);
}

// Shuts down the game
void Application::Shutdown() {
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

//Handles input loop
void Application::Input(float deltaTime) {
    SDL_Event event;
    // Processing input
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            mScene.SetScenceActiveStatus(false);
        }
    }
    // Handle SDL_GetKeyboardState after -- SDL_PollEvent
    mScene.Input(deltaTime);
}

//Handles update events in the game
void Application::Update(SDL_Renderer* renderer, float deltaTime) {
    mScene.Update(renderer, deltaTime);
}

//Handles the drawing
void Application::Render() {
    mScene.Render();
}

//Main game loop
void Application::Loop(float targetFPS) {
    // infinite game/application loop
    Uint64 lastTime, currentTime;

    // Record the 'starting time'
    lastTime = SDL_GetTicks();
    Uint64 framesElapsed = 0;
    float deltaTime = 1.0f / targetFPS;
    while (mScene.IsSceneActive()) {
        Uint64 startOfFrame = SDL_GetTicks();
        // input/update/render should take 16ms
        Input(deltaTime);
        Update(mRenderer, deltaTime);
        Render();
        Uint64 elapsedTime = SDL_GetTicks() - startOfFrame;
        framesElapsed++;

        // Time keeping code - for frames elapsed
        currentTime = SDL_GetTicks();
        // Inserting a 'frame cap' so that the program does not run too fast.
        if (elapsedTime < (1000 / targetFPS)) {
            Uint64 delay = (1000 / targetFPS) - elapsedTime;
            SDL_Delay(delay);
        }
        // If 1 second passes, report how many frames have been executed.
        if (currentTime > lastTime + 1000) {
            deltaTime = 1.0f / framesElapsed;
            framesElapsed = 0;
            lastTime = SDL_GetTicks();
        }
    }
}

