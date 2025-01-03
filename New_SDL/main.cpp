#include "Application.h"
#include <iostream>
#include <SDL3\SDL.h>
//#include <SDL3/SDL_main.h>

int main(int argc, char* argv[]) {
    
    Application app(argc, argv);
    app.Loop(120.0f);

   
    return 0;
}