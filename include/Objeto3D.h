#include "Ponto.h"
#include <ostream>
#include <vector>
#include <SDL2/SDL.h>

#ifndef _OBJETO3D_H
#define _OBJETO3D_H

class Objeto3D {
public:
    std::vector< std::vector<int> > Translocation = { 
        {1, 0, 0, 0}, 
        {0, 1, 0, 0}, 
        {0, 0, 1, 0}, 
        {1, 1, 1, 1} 
    };

    std::vector< std::vector<int> > Scale = { 
        {50, 0, 0, 0}, 
        {0, 50, 0, 0}, 
        {0, 0, 50, 0}, 
        {0, 0, 0, 1} 
    };
    
    static Objeto3D create(int type);
    int getPontosCount();
    int getLinhasCount();
    
    void addNewPoint(Ponto p);
    void addNewLine(int p1, int p2);
    void addNewLine(Ponto p1, Ponto p2);

    void draw(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);

    Ponto& operator[] (int idx);
    friend std::ostream& operator<< (std::ostream& strm, const Objeto3D& p);

    
private:
    void resetTransformations();
    void applyTranslocation();
    void applyScale();
    void applyRotation();
    std::vector<Ponto> pontos_T;
    std::vector<Ponto> pontos;
    std::vector< std::pair<int, int> > linhas;
};

#endif