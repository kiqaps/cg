#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "Ponto.h"
#include "config.h"

#ifndef _UTILS_H
#define _UTILS_H

#define rad(grau)       (grau * M_PI / 180.0)

using namespace std;

class Utils {
public:

    static void putPixel(SDL_Renderer* render, int x, int y, int z, vector< vector<double> >& zbuf)
    {
        SDL_RenderDrawPoint(render, x, y);
    }

    static void linhaDDA (SDL_Renderer* render, Ponto pi, Ponto pf)
    {
        int dx = rint(pf.x - pi.x), dy = rint(pf.y - pi.y), passos;
        double incX, incY, x = pi.x, y = pi.y;
    
        if (abs(dx) > abs(dy))
            passos = abs(dx);
        else
            passos = abs(dy);
    
        incX = dx / (double) passos;
        incY = dy / (double) passos;
    
        SDL_RenderDrawPoint(render, (int) rint(x), (int) rint(y));
        for (int k = 0; k < passos; k++)
        {
            x += incX;
            y += incY;
            SDL_RenderDrawPoint(render, (int) rint(x), (int) rint(y));
        }
    }

    static void linhaDDA (SDL_Renderer* render, Ponto pi, Ponto pf, int figura, vector< vector<double> >& zbuf)
    {
        int dx = rint(pf.x - pi.x), dy = rint(pf.y - pi.y), passos;
        double incX, incY, x = pi.x, y = pi.y;
    
        if (abs(dx) > abs(dy))
            passos = abs(dx);
        else
            passos = abs(dy);
    
        incX = dx / (double) passos;
        incY = dy / (double) passos;

        if ((figura == 0 && x < WINDOW_WIDTH / 2) || (figura == 1 && x > WINDOW_WIDTH / 2))    
            putPixel(render, (int) rint(x), (int) rint(y), (int) rint((pi.z + pf.z) / 2), zbuf);
        for (int k = 0; k < passos; k++)
        {
            x += incX;
            y += incY;
            if ((figura == 0 && x < WINDOW_WIDTH / 2) || (figura == 1 && x > WINDOW_WIDTH / 2)) 
                putPixel(render, (int) rint(x), (int) rint(y), (int) rint((pi.z + pf.z) / 2), zbuf);
        }
    }
    
    static std::vector<Ponto> Multiplica(std::vector<Ponto> pontos, std::vector< std::vector<int> > mat)
    {
        std::vector<Ponto> ret (pontos.size(), Ponto(0,0,0,0));
    
        for (int i = 0; i < pontos.size(); i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    ret[i][j] += pontos[i][k] * mat[k][j];
                }
            }
        }
        return ret;
    }

    static std::vector<Ponto> Multiplica(std::vector<Ponto> pontos, std::vector< std::vector<double> > mat)
    {
        std::vector<Ponto> ret (pontos.size(), Ponto(0,0,0,0));
    
        for (int i = 0; i < pontos.size(); i++) {
            for (int j = 0; j < 4; j++) {
                double soma = 0;
                for (int k = 0; k < 4; k++) {
                    soma +=  pontos[i][k] * mat[k][j];
                }
                ret[i][j] = soma;
            }
        }
        return ret;
    }

    static std::vector< std::vector<double> > Multiplica(std::vector< std::vector<double> > mat1, std::vector< std::vector<double> > mat2)
    {
        std::vector< std::vector<double> > ret (mat1.size(), std::vector<double>(mat1[0].size()));

        for (int i = 0; i < mat1.size(); i++) {
            for (int j = 0; j < mat2[0].size(); j++) {
                double soma = 0;
                for (int k = 0; k < mat1[0].size(); k++) {
                    soma +=  mat1[i][k] * mat2[k][j];
                }
                ret[i][j] = soma;
            }
        }
        return ret;
    }

    static void CreateText(SDL_Renderer* render, TTF_Font* font, const char* text, SDL_Color color, SDL_Texture** texture, SDL_Rect* rect)
    {
        if (*texture) SDL_DestroyTexture(*texture);
        *texture = SDL_CreateTextureFromSurface(render, TTF_RenderUTF8_Solid(font, text, color));
        SDL_QueryTexture(*texture, NULL, NULL, &(rect->w), &(rect->h));
    }

};

#endif