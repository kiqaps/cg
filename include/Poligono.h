#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <SDL2/SDL.h>
#include "Ponto.h"

#ifndef _POLIGONO_H
#define _POLIGONO_H

class Poligono
{
public:
    Poligono(int quantidade_pontos);
    int getPontosSize();
    int getLinhasSize();
    std::pair<int, int>* getLinha(int id);
    void draw(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void fill(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    
    Ponto& operator[] (int idx);
    friend std::ostream& operator<< (std::ostream& strm, const Poligono& p);

private:
    std::vector<Ponto> pontos;
    std::vector< std::pair<int, int> > linhas;
};

#endif
