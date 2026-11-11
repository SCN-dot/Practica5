#include "Caja.h"
#include <QPen>
#include <QBrush>

Rectangulo::Rectangulo(double ancho, double alto): ancho(ancho), alto(alto)
{
    Escena= new QGraphicsScene();
    _rectangulo= new QGraphicsRectItem();

    _rectangulo->setRect(0,0,ancho, alto);
    _rectangulo ->setPen(QPen(Qt::black,3));
    _rectangulo ->setBrush(Qt::NoBrush);

    Escena->addItem(_rectangulo);
    vista = new QGraphicsView(Escena);
    Escena->setSceneRect(0,0,ancho,alto);

    vista ->setWindowTitle("Simulador de particulas");
    vista ->resize(ancho + 30, alto + 30);


}
void Rectangulo::mostrar(){
    vista->show();
}
Rectangulo::~Rectangulo(){
    delete vista;
    delete Escena;
}
void Rectangulo::agregarObstaculo(double x, double y, double ancho, double alto){
    obstaculo *nuevo= new obstaculo(x,y,ancho,alto);
    nuevo ->dibujar(Escena);
    obstaculos.push_back(nuevo);
}