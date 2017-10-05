#include <SDL2/SDL.h>
#include "Ponto.h"

#ifndef _UTILS_H
#define _UTILS_H

void linhaDDA (SDL_Renderer* render, Ponto pi, Ponto pf)
{
    int dx = pf.x - pi.x, dy = pf.y - pi.y, passos;
    float incX, incY, x = pi.x, y = pi.y;

    if (abs(dx) > abs(dy))
        passos = abs(dx);
    else
        passos = abs(dy);

    incX = dx / (float) passos;
    incY = dy / (float) passos;

    SDL_RenderDrawPoint(render, (int) x, (int) y);
    for (int k = 0; k < passos; k++)
    {
        x += incX;
        y += incY;
        SDL_RenderDrawPoint(render, (int) x, (int) y);
    }
}

std::vector<Ponto> Multiplica(std::vector<Ponto> pontos, std::vector< std::vector<int> > mat)
{
    std::vector<Ponto> ret (pontos.size(), Ponto(0,0,0));

    for (int i = 0; i < pontos.size(); i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                ret[i][j] += pontos[i][k] * mat[k][j];
            }
        }
    }
    return ret;
}

#endif