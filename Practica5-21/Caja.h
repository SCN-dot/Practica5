#ifndef CAJA_H
#define CAJA_H
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <qgraphicsview>

class Rectangulo
{
private:
    QGraphicsScene *Escena;
    QGraphicsView *vista;
    QGraphicsRectItem * _rectangulo;

    double ancho;
    double alto;

public:
    Rectangulo(double ancho, double alto);
    void mostrar();
    ~Rectangulo();
};


#endif // CAJA_H
