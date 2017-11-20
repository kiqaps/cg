#include "Ponto.h"

Ponto::Ponto(double x, double y)
{
    this->x = x;
    this->y = y;
    this->m = 1;
    this->xyz = false;
}

Ponto::Ponto(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->m = 1;
    this->xyz = true;
}

Ponto::Ponto(double x, double y, double z, double m)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->m = m;
    this->xyz = true;
}

double& Ponto::operator[] (int idx)
{
    if (idx == 0) return this->x;
    else if (idx == 1) return this->y;
    else if (idx == 2) return this->z;
    else if (idx == 3) return this->m;
}

std::ostream& operator<< (std::ostream& strm, const Ponto& p)
{
    strm << "Ponto(" << p.x << ", " << p.y;
    if (p.xyz) strm << ", " << p.z;
    strm << ", " << p.m << ")";
    return strm;
}
