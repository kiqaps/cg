#include "Objeto3D.h"
#include "Utils.h"
#include "config.h"

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
    else if (type == OBJ_PIRAMIDE)
    {
        obj.addNewPoint({0, 1, 0});
        obj.addNewLine({1, -1, 1}, {1, -1, -1});
        obj.addNewLine({-1, -1, -1}, {-1, -1, 1});
        obj.addNewLine(2, 3);
        obj.addNewLine(4, 1);
        obj.addNewLine(0, 1);
        obj.addNewLine(0, 2);
        obj.addNewLine(0, 3);
        obj.addNewLine(0, 4);
    }
    return obj;
}

void Objeto3D::draw(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
{
    Uint8 before[4];
    SDL_GetRenderDrawColor(renderer, &before[0], &before[1], &before[2], &before[3]);
    SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);

    this->resetTransformations();
    this->applyScale();
    this->applyRotation();
    this->applyTranslocation();

    for (int i = 0; i < this->linhas.size(); i++)
    {
        Ponto p1 = this->pontos_T[this->linhas[i].first], p2 = this->pontos_T[this->linhas[i].second];
        Ponto real1 = { (int) ((OBJ_MAX_X + p1.x) + (OBJ_MAX_Z - p1.z) * OBJ_Z_CONTRIBUITION), (int) ((OBJ_MAX_Y - p1.y) + (OBJ_MAX_Z - p1.z) * OBJ_Z_CONTRIBUITION) },
            real2 = { (int) ((OBJ_MAX_X + p2.x) + (OBJ_MAX_Z - p2.z) * OBJ_Z_CONTRIBUITION), (int) ((OBJ_MAX_Y - p2.y) + (OBJ_MAX_Z - p2.z) * OBJ_Z_CONTRIBUITION) };

        real1.x = (int) (WINDOW_WIDTH * ((double) real1.x / (2.0 * OBJ_MAX_X)));
        real1.y = (int) (WINDOW_HEIGHT * ((double) real1.y / (2.0 * OBJ_MAX_Y)));
        real2.x = (int) (WINDOW_WIDTH * ((double) real2.x / (2.0 * OBJ_MAX_X)));
        real2.y = (int) (WINDOW_HEIGHT * ((double) real2.y / (2.0 * OBJ_MAX_Y)));

        Utils::linhaDDA(renderer, real1, real2);
    }

    SDL_SetRenderDrawColor(renderer, before[0], before[1], before[2], before[3]);
}

void Objeto3D::resetTransformations()
{
    this->pontos_T = this->pontos;
}

void Objeto3D::applyTranslocation()
{
    this->pontos_T = Utils::Multiplica(this->pontos_T, this->Translocation);
}

void Objeto3D::applyScale()
{
    this->pontos_T = Utils::Multiplica(this->pontos_T, this->Scale);
}

void Objeto3D::applyRotation()
{
    std::vector< std::vector<double> > RotX = { 
        {cos(rad(rx)), sin(rad(rx)), 0, 0},
        {-sin(rad(rx)), cos(rad(rx)), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    this->pontos_T = Utils::Multiplica(this->pontos_T, RotX);

    std::vector< std::vector<double> > RotY = { 
        {1, 0, 0, 0},
        {0, cos(rad(ry)), sin(rad(ry)), 0},
        {0, -sin(rad(ry)), cos(rad(ry)), 0},
        {0, 0, 0, 1}
    };
    this->pontos_T = Utils::Multiplica(this->pontos_T, RotY);

    std::vector< std::vector<double> > RotZ = { 
        {cos(rad(rz)), 0, -sin(rad(rz)), 0},
        {0, 1, 0, 0},
        {sin(rad(rz)), 0, cos(rad(rz)), 0},
        {0, 0, 0, 1}
    };
    this->pontos_T = Utils::Multiplica(this->pontos_T, RotZ);
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

void Objeto3D::addNewPoint(Ponto p)
{
    this->pontos.push_back(p);
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