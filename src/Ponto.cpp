#include "Ponto.h"

Ponto::Ponto(int x, int y)
{
    this->x = x;
    this->y = y;
    this->xyz = false;
}

Ponto::Ponto(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->xyz = true;
}

std::ostream& operator<< (std::ostream& strm, const Ponto& p)
{
    strm << "Ponto(" << p.x << ", " << p.y;
    if (p.xyz) strm << ", " << p.z;
    strm << ")";
    return strm;
}
