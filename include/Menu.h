#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Utils.h"

#ifndef _INFO_PANEL_H
#define _INFO_PANEL_H

class Menu {
public:
    Menu(SDL_Renderer* render, TTF_Font* font)
    {
        this->render = render;
        this->font = font;
    }

private:
    std::vector<MenuEntry> entries;
    SDL_Renderer* render;
    TTF_Font* font;
};

class MenuEntry {

};

#endif