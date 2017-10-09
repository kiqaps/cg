#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Utils.h"

#ifndef _INFO_PANEL_H
#define _INFO_PANEL_H

class InfoPanel {
public:
    std::vector<SDL_Rect> texturesRect;
    
    InfoPanel(SDL_Renderer* render, TTF_Font* font)
    {
        this->time = 0;
        this->render = render;
        this->font = font;
    }

    ~InfoPanel()
    {
        for (int i = 0; i < textures.size(); i++)
            SDL_DestroyTexture(textures[i]);
    }

    void addInfo(const char* info)
    {
        int y = 1;
        int last = textures.size() - 1;

        if (last >= 0)
            y = texturesRect[last].h + texturesRect[last].y + 1;
        
        SDL_Texture* nt = NULL;
        SDL_Rect nr;

        Utils::CreateText(this->render, this->font, info, {0x0,0x0,0x0,0xFF}, &nt, &nr);
        nr.x = 1;
        nr.y = y;

        this->textures.push_back(nt);
        this->texturesRect.push_back(nr);
        this->collapsed.push_back(false);
    }

    void showCollapsed(Uint32 time)
    {
        this->ticks = SDL_GetTicks();
        this->time = time;
    }

    void addInfo(const char* info, bool collapsed)
    {
        this->addInfo(info);
        this->collapsed[this->collapsed.size() - 1] = collapsed;
    }

    void draw()
    {
        Uint32 ticks = SDL_GetTicks();

        for (int i = 0; i < textures.size(); i++)
            if ((ticks - this->ticks) <= time || !collapsed[i])
                SDL_RenderCopy(this->render, textures[i], NULL, &(texturesRect[i]));
    }
    
private:
    std::vector<bool> collapsed;
    std::vector<SDL_Texture*> textures;
    Uint32 time, ticks;
    SDL_Renderer* render;
    TTF_Font* font;
};

#endif