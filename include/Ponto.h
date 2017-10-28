#include <ostream>

#ifndef _PONTO_H
#define _PONTO_H

class Ponto {
public:
    double x, y, z, m;
    Ponto(double x, double y);
    Ponto(double x, double y, double z);
    Ponto(double x, double y, double z, double m);

    double& operator[] (int idx);
    friend std::ostream& operator<< (std::ostream& strm, const Ponto& p);

private:
    bool xyz;
};

#endif // _PONTO_H
