#ifndef OBSTACULO_H
#define OBSTACULO_H
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>

class obstaculo{
private:
    double x;
    double y;
    double ancho;
    double alto;
    QGraphicsRectItem * rectangulo;
public:
    obstaculo(double x, double y, double ancho, double alto);
    void dibujar(QGraphicsScene * escena);
    double obtenerX() const;
    double obtenerY() const;
    double obtenerAlto() const;
    double obtenerAncho() const;


};

#endif // OBSTACULO_H
