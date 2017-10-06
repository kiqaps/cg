#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Utils.h"

#ifndef _INFO_PANEL_H
#define _INFO_PANEL_H

class InfoPanel {
public:
    std::vector<SDL_Texture*> textures;
    std::vector<SDL_Rect> texturesRect;

    InfoPanel(SDL_Renderer* render, TTF_Font* font)
    {
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
    }

    void draw()
    {
        for (int i = 0; i < textures.size(); i++)
            SDL_RenderCopy(this->render, textures[i], NULL, &(texturesRect[i]));
    }
    
private:
    SDL_Renderer* render;
    TTF_Font* font;
};

#endif