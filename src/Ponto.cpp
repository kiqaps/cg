#include "Ponto.h"

Ponto::Ponto(int x, int y)
{
    this->x = x;
    this->y = y;
    this->m = 1;
    this->xyz = false;
}

Ponto::Ponto(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->m = 1;
    this->xyz = true;
}

int Ponto::operator[] (int idx)
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
    strm << ")";
    return strm;
}
