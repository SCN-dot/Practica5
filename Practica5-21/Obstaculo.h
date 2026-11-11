#ifndef OBSTACULO_H
#define OBSTACULO_H

class obstaculo
{
private:
    double x;
    double y;
    double ancho;
    double alto;

public:
    obstaculo(double x, double y, double ancho, double alto);
    double obtenerX() const;
    double obtenerY() const;
    double obtenerAncho() const;
    double obtenerAlto() const;
    ~obstaculo();
};

#endif // OBSTACULO_H