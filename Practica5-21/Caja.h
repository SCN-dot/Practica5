#ifndef CAJA_H
#define CAJA_H
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <qgraphicsview>
#include "Obstaculo.h"
#include "Particula.h"
#include <Qtimer>
#include <QElapsedTimer>
#include <QObject>
#include <vector>

using namespace std;
#include <vector>


class Rectangulo
{
private:
    QGraphicsScene *Escena;
    QGraphicsView *vista;
    QGraphicsRectItem * _rectangulo;
    QTimer timer;
    QElapsedTimer reloj;
    void actualizar();
    void comprobarParedes(Particula *p);

    double ancho;
    double alto;
    vector<obstaculo*> obstaculos;
    vector<Particula*> particulas;
public:
    Rectangulo(double ancho, double alto);
    void mostrar();
    void agregarObstaculo(double x, double y, double ancho, double alto);
    void agregarParticula(Particula *p);
    ~Rectangulo();
};


#endif // CAJA_H
