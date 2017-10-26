#include <functional>
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
    Menu();
    ~Menu();
    Menu(SDL_Renderer* render, TTF_Font* font);
    void AddNewEntry(std::string text);
    void AddNewEntry(std::string text, std::function<void()> callback);
    
    void Show(int x, int y);

    SDL_Renderer* getRender();
    TTF_Font* getFont();

    bool showing = false;

private:
    void ProcessInput();
    void Draw();
    void Update();
    
    bool clicked = false;
    int clickedX, clickedY, curX, curY, x, y, height, width;
    Menu* parent;
    std::vector<MenuEntry*> entries;
    SDL_Renderer* render;
    TTF_Font* font;
};

class MenuEntry {
public:
    ~MenuEntry();
    MenuEntry (Menu* menu, std::string text);
    MenuEntry (Menu* menu, std::string text, std::function<void()> callback);
    std::string getText();

    SDL_Texture* getTexture();
    SDL_Rect getRect();

    std::function<void()> callback;

private:
    SDL_Texture* texture = NULL;
    SDL_Rect rect;
    Menu* menu = NULL;
    Menu* child = NULL;
    bool hasChild;
    std::string text;
};

#endif