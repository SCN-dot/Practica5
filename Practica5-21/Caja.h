#ifndef CAJA_H
#define CAJA_H
using namespace std;
#include <vector>
#include "Obstaculo.h"
#include "Particula.h"

class Rectangulo
{
private:
    double ancho;
    double alto;
    vector<obstaculo*> obstaculos;
    vector<Particula*> particulas;
    void actualizar(double dt);
    void comprobarParedes(Particula *p);

public:
    Rectangulo(double ancho, double alto);
    void agregarObstaculo(double x, double y, double ancho, double alto);
    void agregarParticula(Particula *p);
    void simular(double dt);
    void mostrarEstado() const;
    ~Rectangulo();
};

#endif // CAJA_H
