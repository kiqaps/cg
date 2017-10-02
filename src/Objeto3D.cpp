#include "Objeto3D.h"
#include "Utils.h"

Objeto3D Objeto3D::create(int type)
{
    Objeto3D obj;
    if (type == OBJ_QUADRADO)
    {
        obj.addNewLine({1, 1, 1}, {-1, 1, 1});
        obj.addNewLine({1, -1, 1}, {-1, -1, 1});
        obj.addNewLine({1, 1, -1}, {-1, 1, -1});
        obj.addNewLine({1, -1, -1}, {-1, -1, -1});
        obj.addNewLine(0, 2);
        obj.addNewLine(0, 4);
        obj.addNewLine(1, 3);
        obj.addNewLine(1, 5);
        obj.addNewLine(2, 6);
        obj.addNewLine(3, 7);
        obj.addNewLine(4, 6);
        obj.addNewLine(5, 7);
    }
    return obj;
}

void Objeto3D::draw(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
{
    Uint8 before[4];
    SDL_GetRenderDrawColor(renderer, &before[0], &before[1], &before[2], &before[3]);
    SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);

    for (int i = 0; i < this->linhas.size(); i++)
    {
        Ponto p1 = this->pontos[this->linhas[i].first], p2 = this->pontos[this->linhas[i].second];
        Ponto real1 = p1, real2 = p2;
        linhaDDA(renderer, real1, real2);
    }

    SDL_SetRenderDrawColor(renderer, before[0], before[1], before[2], before[3]);
}

void Objeto3D::resetTrasformations()
{
    this->pontos_T = this->pontos;
}

void Objeto3D::applyTranslocation()
{

}

int Objeto3D::getPontosCount()
{
    return this->pontos.size();
}

int Objeto3D::getLinhasCount()
{
    return this->linhas.size();
}

void Objeto3D::addNewLine(int p1, int p2)
{
    this->linhas.push_back(std::make_pair(p1, p2));
}

void Objeto3D::addNewLine(Ponto p1, Ponto p2)
{
    int pos = this->pontos.size();
    this->pontos.push_back(p1);
    this->pontos.push_back(p2);
    this->linhas.push_back(std::make_pair(pos, pos + 1));
}

Ponto& Objeto3D::operator[] (int idx)
{
    if (idx >= 0 && idx < this->pontos.size())
        return this->pontos[idx];
}

std::ostream& operator<< (std::ostream& strm, const Objeto3D& p)
{
    strm << "Objeto3D: " << p.pontos.size() << " ponto(s) e " << p.linhas.size() << " linhas" << std::endl;

    if (p.pontos.size() > 0) {
        strm << "\tPontos:\t\t" << p.pontos[0] << std::endl;
        for (int i = 1; i < p.pontos.size(); i++)
            strm << "\t\t\t" << p.pontos[i] << std::endl;
        strm << std::endl << "\tLinhas:\t\t" << p.linhas[0].first << " - " << p.linhas[0].second << std::endl;
        for(int i = 1; i < p.linhas.size(); i++)
            strm << "\t\t\t" << p.linhas[i].first << " - " << p.linhas[i].second << std::endl;
    }

    return strm;
}