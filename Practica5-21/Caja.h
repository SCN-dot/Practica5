#ifndef CAJA_H
#define CAJA_H
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <qgraphicsview>
#include "Obstaculo.h"
using namespace std;
#include <vector>

class Rectangulo
{
private:
    QGraphicsScene *Escena;
    QGraphicsView *vista;
    QGraphicsRectItem * _rectangulo;

    double ancho;
    double alto;
    vector<obstaculo*> obstaculos;

public:
    Rectangulo(double ancho, double alto);
    void mostrar();
    void agregarObstaculo(double x, double y, double ancho, double alto);
    ~Rectangulo();
};


#endif // CAJA_H
