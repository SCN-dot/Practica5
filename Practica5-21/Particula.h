#ifndef PARTICULA_H
#define PARTICULA_H

class Particula
{
private:
    int id;          // identificador (para el archivo de salida)
    double x, y;     // posicion del centro
    double vx, vy;   // velocidad
    double masa;
    double radio;
    bool activa;     // false si fue absorbida por otra al fusionarse

public:
    Particula(int id, double x, double y, double vx, double vy, double masa, double radio);

    // Getters
    int getId() const;
    double getX() const;
    double getY() const;
    double getVx() const;
    double getVy() const;
    double getMasa() const;
    double getRadio() const;
    bool estaActiva() const;

    void setPosicion(double nx, double ny);
    void setVelocidad(double nvx, double nvy);

    void mover(double dt);

    bool colisionaCon(const Particula &otra) const;

    void fusionar(Particula &otra);
};

#endif // PARTICULA_H
