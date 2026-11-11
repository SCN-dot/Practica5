#ifndef CAJA_H
#define CAJA_H

#include <vector>
#include <fstream>
#include "Obstaculo.h"
#include "Particula.h"

enum ErrorCaja {
    CAJA_OK,
    CAJA_MASA_O_RADIO,
    CAJA_FUERA_DE_CAJA,
    CAJA_TRASLAPE_OBSTACULO,
    CAJA_TRASLAPE_PARTICULA
};

class Caja
{
private:
    double ancho;
    double alto;
    double epsilon;
    double tiempo;
    int siguienteId;
    std::ofstream *salida;
    std::vector<Obstaculo*> obstaculos;
    std::vector<Particula*> particulas;

    void actualizar(double dt);
    bool comprobarParedes(Particula *p);
    void procesarParedes(Particula *p);
    bool rebotarObstaculos(Particula *p);
    void colisionesEntreParticulas();
    void ubicarDentro(Particula *p);

public:
    Caja(double ancho, double alto, double epsilon);

    void agregarObstaculo(double x, double y, double ancho, double alto);
    ErrorCaja agregarParticula(Particula *p);

    void setSalida(std::ofstream *archivo);
    void setTiempo(double t);

    void simular(double dt);
    void mostrarEstado() const;

    double getAncho() const;
    double getAlto() const;
    double getEpsilon() const;
    int getSiguienteId() const;
    const std::vector<Obstaculo*> &getObstaculos() const;
    const std::vector<Particula*> &getParticulas() const;

    Caja(const Caja &) = delete;
    Caja &operator=(const Caja &) = delete;

    ~Caja();
};

#endif
