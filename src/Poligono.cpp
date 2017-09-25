#include "Poligono.h"
#include "Utils.h"

Poligono::Poligono(int quantidade_pontos)
{
    this->pontos = std::vector<Ponto> (quantidade_pontos, Ponto(0,0));
    this->linhas = std::vector< std::pair<int, int> > (quantidade_pontos);
    
    for (int i = 0; i < quantidade_pontos - 1; i++)
        this->linhas[i] = std::make_pair(i, i + 1);
    this->linhas[quantidade_pontos - 1] = std::make_pair(quantidade_pontos - 1, 0);
}

int Poligono::getLinhasSize()
{
    return this->linhas.size();
}

int Poligono::getPontosSize()
{
    return this->pontos.size();
}

std::pair<int, int>* Poligono::getLinha(int id)
{
    if (id >= 0 && id < this->linhas.size())
    {
        return &(this->linhas[id]);
    }
    return NULL;
}

void Poligono::draw(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    Uint8 before[4];
    SDL_GetRenderDrawColor(renderer, &before[0], &before[1], &before[2], &before[3]);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);

    for (int i = 0; i < this->linhas.size(); i++)
        linhaDDA(renderer, this->pontos[this->linhas[i].first], this->pontos[this->linhas[i].second]);

    SDL_SetRenderDrawColor(renderer, before[0], before[1], before[2], before[3]);
}

void Poligono::fill(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    Uint8 before[4];
    SDL_GetRenderDrawColor(renderer, &before[0], &before[1], &before[2], &before[3]);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);

    int Ymax = INT32_MIN, Ymin = INT32_MAX;

    for (int i = 0; i < this->pontos.size(); i++)
    {
        Ymax = std::max(Ymax, this->pontos[i].y);
        Ymin = std::min(Ymin, this->pontos[i].x);
    }

    for (int Yatual = Ymin + 1; Yatual < Ymax; Yatual++)
    {
        std::vector<Ponto> intersecoes;
        
        for (int i = 0; i < this->linhas.size(); i++)
        {
            int Xatual = ((Yatual - this->pontos[this->linhas[i].first].y) * (this->pontos[this->linhas[i].second].x - this->pontos[this->linhas[i].first].x)) / (this->pontos[this->linhas[i].second].y - this->pontos[this->linhas[i].first].y) + this->pontos[this->linhas[i].first].x;
            if ((Xatual >= this->pontos[this->linhas[i].first].x && Xatual <= this->pontos[this->linhas[i].second].x) ||
            (Xatual >= this->pontos[this->linhas[i].second].x && Xatual <= this->pontos[this->linhas[i].first].x))
            {
                intersecoes.push_back(Ponto(Xatual, Yatual));
            }
        }

        std::sort(intersecoes.begin(), intersecoes.end(), [](const Ponto& lhs, const Ponto& rhs)
            {
                return lhs.x <= rhs.y;
            });

        for (int i = 0; i < intersecoes.size(); i += 2)
        {
            linhaDDA(renderer, intersecoes[i], intersecoes[i+1]);
        }
    }

    SDL_SetRenderDrawColor(renderer, before[0], before[1], before[2], before[3]);
}

Ponto& Poligono::operator[] (int idx)
{
    if (idx >= 0 && idx < this->pontos.size())
        return this->pontos[idx];
}

std::ostream& operator<< (std::ostream& strm, const Poligono& p)
{
    strm << "Poligono: " << p.pontos.size() << " ponto(s) e " << p.linhas.size() << " linhas" << std::endl;
    strm << "\tPontos:\t\t" << p.pontos[0] << std::endl;
    for (int i = 1; i < p.pontos.size(); i++)
        strm << "\t\t\t" << p.pontos[i] << std::endl;
    strm << std::endl << "\tLinhas:\t\t" << p.linhas[0].first << " - " << p.linhas[0].second << std::endl;
    for(int i = 1; i < p.linhas.size(); i++)
        strm << "\t\t\t" << p.linhas[i].first << " - " << p.linhas[i].second << std::endl;

    return strm;
}