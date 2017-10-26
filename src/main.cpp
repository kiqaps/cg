#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <ctime>
#include <cstdlib>
#include "config.h"
#include "Ponto.h"
#include "Objeto3D.h"
#include "Menu.h"
#include "Poligono.h"

using namespace std;

int init();
void setup();
void loop();
void ProcessInput();
void Draw();
void Update();
void quit();

void CreateText(SDL_Renderer* render, TTF_Font* font, const char* text, SDL_Color color, SDL_Texture** texture, SDL_Rect* rect);

int gMode = 0;
char mode_name[][25] = {
    "Translação em X", "Translação em Y", "Translação em Z",
    "Escala em X", "Escala em Y", "Escala em Z",
    "Rotação entorno de X", "Rotação entorno de Y", "Rotação entorno de Z"
};

SDL_Texture* gModeInfoTex = NULL;
SDL_Texture* gModeText = NULL;
SDL_Rect gModeRect, gModeInfoRect;

bool bRunning = true;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRender = NULL;
TTF_Font* gFont = NULL;

Menu* gMenu = NULL;
Objeto3D* gObj = NULL;

int main (int argc, char** argv)
{
    if (init() != 0)
    {
        cout << "Não foi possível inicializar o SDL: " << SDL_GetError() << endl;
        return 1;
    }

    // Configura os objetos e menus
    setup();

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
        else if (evt.type == SDL_MOUSEBUTTONDOWN && evt.button.button == SDL_BUTTON_RIGHT)
        {
            gMenu->Show(evt.button.x, evt.button.y);
        }
        else if (evt.type == SDL_KEYDOWN)
        {
            if (evt.key.keysym.sym == SDLK_r)
            {
                
            }
            else if (evt.key.keysym.sym == SDLK_q)
                gMode = 0;
            else if (evt.key.keysym.sym == SDLK_w)
                gMode = 1;
            else if (evt.key.keysym.sym == SDLK_e)
                gMode = 2;
            else if (evt.key.keysym.sym == SDLK_a)
                gMode = 3;
            else if (evt.key.keysym.sym == SDLK_s)
                gMode = 4;
            else if (evt.key.keysym.sym == SDLK_d)
                gMode = 5;
            else if (evt.key.keysym.sym == SDLK_z)
                gMode = 6;
            else if (evt.key.keysym.sym == SDLK_x)
                gMode = 7;
            else if (evt.key.keysym.sym == SDLK_c)
                gMode = 8;
            else if (evt.key.keysym.sym == SDLK_UP || evt.key.keysym.sym == SDLK_DOWN)
            {
                int sinal = -1;

                if (evt.key.keysym.sym == SDLK_UP)
                    sinal = 1;

                if (gMode == 0)
                    gObj->Translocation[3][0] += sinal * QTD_TRANSLACAO;
                else if (gMode == 1)
                    gObj->Translocation[3][1] += sinal * QTD_TRANSLACAO;
                else if (gMode == 2)
                    gObj->Translocation[3][2] += sinal * QTD_TRANSLACAO;

                else if (gMode == 3)
                    gObj->Scale[0][0] += sinal * QTD_ESCALA;
                else if (gMode == 4)
                    gObj->Scale[1][1] += sinal * QTD_ESCALA;
                else if (gMode == 5)
                    gObj->Scale[2][2] += sinal * QTD_ESCALA;

                else if (gMode == 6) {
                    gObj->rx += sinal * QTD_ROTACAO;
                    if (gObj->rx < 0)
                        gObj->rx = 360;
                    else if (gObj->rx > 360)
                        gObj->rx = 0;
                }
                else if (gMode == 7) {
                    gObj->ry += sinal * QTD_ROTACAO;
                    if (gObj->ry < 0)
                        gObj->ry = 360;
                    else if (gObj->ry > 360)
                        gObj->ry = 0;
                }
                else if (gMode == 8) {
                    gObj->rz += sinal * QTD_ROTACAO;
                    if (gObj->rz < 0)
                        gObj->rz = 360;
                    else if (gObj->rz > 360)
                        gObj->rz = 0;
                }
            }
        }
    }
}

void Draw()
{  
    SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRender);    

    Utils::CreateText(gRender, gFont, mode_name[gMode], {0x0, 0x0, 0xFF}, &gModeText, &gModeRect);
    gModeRect.x = gModeInfoRect.x + gModeInfoRect.w;
    gModeRect.y = gModeInfoRect.y;

    SDL_RenderCopy(gRender, gModeInfoTex, NULL, &gModeInfoRect);
    SDL_RenderCopy(gRender, gModeText, NULL, &gModeRect);

    gObj->draw(gRender, 0xFF, 0x0, 0x0);
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

    if (TTF_Init() != 0) return -1;

    gFont = TTF_OpenFont("assets/fonts/Verdana.ttf", FONT_SIZE);
    if (!gFont) return -1;
    return 0;
}

void setup()
{
    gObj = Objeto3D::create(OBJ_CUBO);

    gMenu = new Menu(gRender, gFont);
    gMenu->AddNewEntry("Resetar Objeto", [] {
        gObj->Translocation[3][0] = 1;
        gObj->Translocation[3][1] = 1;
        gObj->Translocation[3][2] = 1;
        gObj->Scale[0][0] = 50;
        gObj->Scale[1][1] = 50;
        gObj->Scale[2][2] = 50;
        gObj->rx = 0;
        gObj->ry = 0;
        gObj->rz = 0;
    });
    gMenu->AddNewEntry("Modo");
    gMenu->AddNewEntry("Menu Item 3");
    gMenu->AddNewEntry("Menu Item 4");

    Utils::CreateText(gRender, gFont, "MODO: ", {0x0, 0x0, 0x0}, &gModeInfoTex, &gModeInfoRect);
    gModeInfoRect.x = 1;
    gModeInfoRect.y = 1;
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

        Uint32 espera = 30 - (SDL_GetTicks() - sTicks);
        SDL_Delay(espera > 30 ? 30 : espera);
    }
}

void quit()
{
    delete gObj;
    delete gMenu;
    SDL_DestroyTexture(gModeInfoTex);
    SDL_DestroyTexture(gModeText);
    SDL_DestroyRenderer(gRender);
    SDL_DestroyWindow(gWindow);
    TTF_CloseFont(gFont);
    TTF_Quit();
    SDL_Quit();
}