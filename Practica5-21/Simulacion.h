#ifndef SIMULACION_H
#define SIMULACION_H

#include <fstream>
#include "Caja.h"


enum Error {
    SIN_ERROR,
    ERR_ENTRADA_INVALIDA,
    ERR_POCAS_PARTICULAS,
    ERR_MASA_O_RADIO,
    ERR_FUERA_DE_CAJA,
    ERR_TRASLAPE_OBSTACULO,
    ERR_TRASLAPE_PARTICULA,
    ERR_ARCHIVO
};

const char *mensajeError(Error e);

class Simulacion
{
private:
    Caja caja;
    double dt;
    double tiempo;
    std::ofstream archivo;

    void escribirParticulas();
    void escribirEncabezado(double duracion);

public:
    Simulacion(double ancho, double alto, double dt, double epsilon);
    void agregarObstaculo(double x, double y, double ancho, double alto);
    Error agregarParticula(double x, double y, double vx, double vy, double masa, double radio);
    Error ejecutar(double duracion, const char *nombreArchivo);
};

#endif
