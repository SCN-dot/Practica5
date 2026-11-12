#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "Particula.h"

enum Lado { NINGUNO, IZQUIERDA, DERECHA, ABAJO, ARRIBA };

class Obstaculo
{
private:
    double x;
    double y;
    double ancho;
    double alto;

public:
    Obstaculo(double x, double y, double ancho, double alto);
    double obtenerX() const;
    double obtenerY() const;
    double obtenerAncho() const;
    double obtenerAlto() const;
    Lado ladoDeChoque(const Particula &p) const;
    void sacarParticula(Particula &p, Lado lado) const;
    ~Obstaculo();
};

#endif
