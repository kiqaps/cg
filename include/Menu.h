#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Poligono.h"
#include "Utils.h"

#ifndef _MENU_H
#define _MENU_H

class MenuEntry;

class Menu {
public:
    Menu(SDL_Renderer* render, TTF_Font* font);
    void AddNewEntry(MenuEntry entry);
    void Draw(int x, int y);

private:
    int height, width;
    Menu* parent;
    std::vector<MenuEntry> entries;
    SDL_Renderer* render;
    TTF_Font* font;
    std::vector<SDL_Texture*> _textures;
    std::vector<SDL_Rect> _rects;
};

class MenuEntry {
public:
    MenuEntry (Menu* menu, std::string text);
    std::string getText();
private:
    Menu* menu;
    Menu* child;
    bool hasChild;
    std::string text;
};

#endif