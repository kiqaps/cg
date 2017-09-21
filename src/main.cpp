#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Ponto.h"

using namespace std;

#define WINDOW_TITLE            "Trabalho de CG"
#define WINDOW_WIDTH            640
#define WINDOW_HEIGHT           480

int init();
void loop();
void ProcessInput();
void Redraw();
void Update();
void quit();

bool bRunning = true;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRender = NULL;


int main (int argc, char** argv)
{
    if (init() != 0)
    {
        cout << "Não foi possível inicializar o SDL: " << SDL_GetError() << endl;
        return 1;
    }

    loop();

    quit();
    return 0;
}


void ProcessInput()
{
    SDL_Event evt;
    while (SDL_PollEvent(&evt))
    {
        if (evt.type == SDL_QUIT || (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE))
        {
            bRunning = false;
            break;
        }
    }
}

void Redraw()
{

}

void Update()
{
    SDL_RenderPresent(gRender);
}

int init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
        return -1;

    gWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!gWindow) return -1;

    gRender = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!gRender) return -1;

    SDL_RenderClear(gRender);

    return 0;
}

void loop()
{
    Uint32 sTicks;
    while (bRunning)
    {
        sTicks = SDL_GetTicks();

        ProcessInput();
        Redraw();
        Update();

        SDL_Delay(16 - (SDL_GetTicks() - sTicks));
    }
}

void quit()
{
    SDL_DestroyRenderer(gRender);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}