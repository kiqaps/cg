#include "Objeto3D.h"
#include "Utils.h"
#include "config.h"

#include <iostream>

Objeto3D* Objeto3D::create(int type)
{
    Objeto3D* obj = new Objeto3D();

    obj->Translocation[3][0] = 1;
    obj->Translocation[3][1] = 1;
    obj->Translocation[3][2] = 1;
    obj->Scale[0][0] = 50;
    obj->Scale[1][1] = 50;
    obj->Scale[2][2] = 50;
    obj->rx = 0;
    obj->ry = 0;
    obj->rz = 0;

    if (type == OBJ_CUBO)
    {
        obj->addNewLine({1, 1, 1}, {-1, 1, 1});
        obj->addNewLine({1, -1, 1}, {-1, -1, 1});
        obj->addNewLine({1, 1, -1}, {-1, 1, -1});
        obj->addNewLine({1, -1, -1}, {-1, -1, -1});
        obj->addNewLine(0, 2);
        obj->addNewLine(0, 4);
        obj->addNewLine(1, 3);
        obj->addNewLine(1, 5);
        obj->addNewLine(2, 6);
        obj->addNewLine(3, 7);
        obj->addNewLine(4, 6);
        obj->addNewLine(5, 7);
    }
    else if (type == OBJ_PIRAMIDE)
    {
        obj->addNewPoint({0, 1, 0});
        obj->addNewLine({1, -1, 1}, {1, -1, -1});
        obj->addNewLine({-1, -1, -1}, {-1, -1, 1});
        obj->addNewLine(2, 3);
        obj->addNewLine(4, 1);
        obj->addNewLine(0, 1);
        obj->addNewLine(0, 2);
        obj->addNewLine(0, 3);
        obj->addNewLine(0, 4);
    }
    return obj;
}

Objeto3D::Objeto3D()
{
    this->projection = OBJ_PROJ_CAVALEIRA;
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

    // Ajusta as coordenadas para a tela
    for (int i = 0; i < this->pontos_T.size(); i++)
    {
        this->pontos_T[i][0] += OBJ_MAX_X;
        this->pontos_T[i][1] = OBJ_MAX_Y - this->pontos_T[i][1];
        this->pontos_T[i][2] += OBJ_MAX_Z;
    }

    this->applyProjection();

    for (int i = 0; i < this->linhas.size(); i++)
    {
        Ponto p1 = this->pontos_T[this->linhas[i].first], p2 = this->pontos_T[this->linhas[i].second];
        
        p1.x = p1.x / p1.m;
        p1.y = p1.y / p1.m;
        p2.x = p2.x / p2.m;
        p2.y = p2.y / p2.m;
        
        p1.x = (WINDOW_WIDTH * (p1.x / (2.0 * OBJ_MAX_X)));
        p1.y = (WINDOW_HEIGHT * (p1.y / (2.0 * OBJ_MAX_Y)));
        p2.x = (WINDOW_WIDTH * (p2.x / (2.0 * OBJ_MAX_X)));
        p2.y = (WINDOW_HEIGHT * (p2.y / (2.0 * OBJ_MAX_Y)));

        Utils::linhaDDA(renderer, p1, p2);
    }

    SDL_SetRenderDrawColor(renderer, before[0], before[1], before[2], before[3]);
}

void Objeto3D::applyProjection()
{
    std::vector< std::vector<double> > projMat;
    if (this->projection == OBJ_PROJ_CAVALEIRA)
    {
        projMat = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {cos(rad(45)), sin(rad(45)), 0, 0},
            {0, 0, 0, 1}
        };
    }
    else if (this->projection == OBJ_PROJ_CABINET)
    {
        projMat = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0.5 * cos(rad(63.4)), 0.5 * sin(rad(63.4)), 0, 0},
            {0, 0, 0, 1}
        };
    }
    else if (this->projection == OBJ_PROJ_1PTFUGA)
    {
        projMat = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 0, -1.0/90.0},
            {0, 0, 0, 1}
        };
    }
    this->pontos_T = Utils::Multiplica(this->pontos_T, projMat);
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
    std::vector< std::vector<double> > RotZ = { 
        {cos(rad(rz)), sin(rad(rz)), 0, 0},
        {-sin(rad(rz)), cos(rad(rz)), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    this->pontos_T = Utils::Multiplica(this->pontos_T, RotZ);

    std::vector< std::vector<double> > RotX = { 
        {1, 0, 0, 0},
        {0, cos(rad(rx)), sin(rad(rx)), 0},
        {0, -sin(rad(rx)), cos(rad(rx)), 0},
        {0, 0, 0, 1}
    };
    this->pontos_T = Utils::Multiplica(this->pontos_T, RotX);

    std::vector< std::vector<double> > RotY = { 
        {cos(rad(ry)), 0, -sin(rad(ry)), 0},
        {0, 1, 0, 0},
        {sin(rad(ry)), 0, cos(rad(ry)), 0},
        {0, 0, 0, 1}
    };
    this->pontos_T = Utils::Multiplica(this->pontos_T, RotY);
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