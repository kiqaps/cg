#include <iostream>
#include <SDL2/SDL.h>
#include <ctime>
#include <cstdlib>
#include "config.h"
#include "Ponto.h"
#include "Objeto3D.h"

using namespace std;

int init();
void loop();
void ProcessInput();
void Draw();
void Update();
void quit();

bool bRunning = true;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRender = NULL;
Objeto3D obj;

int main (int argc, char** argv)
{
    if (init() != 0)
    {
        cout << "Não foi possível inicializar o SDL: " << SDL_GetError() << endl;
        return 1;
    }

    obj = Objeto3D::create(OBJ_QUADRADO);

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

void Draw()
{
    obj.draw(gRender, 0xFF, 0x0, 0x0);

    SDL_SetRenderDrawColor(gRender, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderDrawPoint(gRender, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

void Update()
{
    SDL_RenderPresent(gRender);
}

int init()
{
    srand(time(NULL));
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
        return -1;

    gWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!gWindow) return -1;

    gRender = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!gRender) return -1;

    SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
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
        Draw();
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