#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <ctime>
#include <cstdlib>
#include "config.h"
#include "Ponto.h"
#include "Objeto3D.h"
#include "InfoPanel.h"

using namespace std;

int init();
void loop();
void ProcessInput();
void Draw();
void Update();
void quit();

void CreateText(SDL_Renderer* render, TTF_Font* font, const char* text, SDL_Color color, SDL_Texture** texture, SDL_Rect* rect);

int gMode = 0;
bool bRunning = true;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRender = NULL;
TTF_Font* gFont = NULL;
InfoPanel* gInfoPanel = NULL;
SDL_Rect modeText;
SDL_Texture *modeTexture = NULL;

char modes_names[][25] = {
    "Translação em X",
    "Translação em Y",
    "Translação em Z",
    "Escalar X",
    "Escalar Y",
    "Escalar Z",
    "Rotação em torno de X",
    "Rotação em torno de Y",
    "Rotação em torno de Z"
};

Objeto3D obj;

int main (int argc, char** argv)
{
    if (init() != 0)
    {
        cout << "Não foi possível inicializar o SDL: " << SDL_GetError() << endl;
        return 1;
    }

    obj = Objeto3D::create(OBJ_QUADRADO);

    gInfoPanel = new InfoPanel(gRender, gFont);
    gInfoPanel->addInfo("Aperte F1 para ver todos comandos");
    gInfoPanel->addInfo("MODO ATUAL:");
    gInfoPanel->addInfo("Aperte q para translação em X", true);
    gInfoPanel->addInfo("Aperte w para translação em Y", true);
    gInfoPanel->addInfo("Aperte e para translação em Z", true);
    gInfoPanel->addInfo("Aperte a para escalar X", true);
    gInfoPanel->addInfo("Aperte s para escalar Y", true);
    gInfoPanel->addInfo("Aperte d para escalar Z", true);
    gInfoPanel->addInfo("Aperte z para rotacionar em torno de X", true);
    gInfoPanel->addInfo("Aperte x para rotacionar em torno de Y", true);
    gInfoPanel->addInfo("Aperte c para rotacionar em torno de Z", true);
    gInfoPanel->addInfo(" ", true);
    gInfoPanel->addInfo("Use as setas (cima e baixo) para", true);
    gInfoPanel->addInfo("aplicar a transformação deseja", true);

    modeText.y = gInfoPanel->texturesRect[0].h + gInfoPanel->texturesRect[0].y + 1;
    modeText.x = gInfoPanel->texturesRect[1].w + FONT_SIZE; 

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
        else if (evt.type == SDL_KEYDOWN)
        {
            if (evt.key.keysym.sym == SDLK_F1)
                gInfoPanel->showCollapsed(3000);
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
                    obj.Translocation[3][0] += sinal * QTD_TRANSLACAO;
                else if (gMode == 1)
                    obj.Translocation[3][1] += sinal * QTD_TRANSLACAO;
                else if (gMode == 2)
                    obj.Translocation[3][2] += sinal * QTD_TRANSLACAO;

                else if (gMode == 3)
                    obj.Scale[0][0] += sinal * QTD_ESCALA;
                else if (gMode == 4)
                    obj.Scale[1][1] += sinal * QTD_ESCALA;
                else if (gMode == 5)
                    obj.Scale[2][2] += sinal * QTD_ESCALA;
            }
        }
    }
}

void Draw()
{  
    SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRender);

    obj.draw(gRender, 0xFF, 0x0, 0x0);
    
    Utils::CreateText(gRender, gFont, modes_names[gMode], {0x42, 0x44, 0xF8, 0xFF}, &modeTexture, &modeText);
    SDL_RenderCopy(gRender, modeTexture, NULL, &modeText);
    gInfoPanel->draw();
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

void loop()
{
    Uint32 sTicks;
    while (bRunning)
    {
        sTicks = SDL_GetTicks();

        ProcessInput();
        Draw();
        Update();

        SDL_Delay(30 - (SDL_GetTicks() - sTicks));
    }
}

void quit()
{
    delete gInfoPanel;
    SDL_DestroyTexture(modeTexture);
    SDL_DestroyRenderer(gRender);
    SDL_DestroyWindow(gWindow);
    TTF_CloseFont(gFont);
    TTF_Quit();
    SDL_Quit();
}