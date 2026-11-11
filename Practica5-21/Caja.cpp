#include "Caja.h"
#include <QPen>
#include <QBrush>
#include <cmath>

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
    reloj.start();
    QObject::connect(&timer, &QTimer::timeout,[this](){
        actualizar();
    });
    timer.start(16);


}
void Rectangulo::agregarParticula(Particula *p){
    if(p==nullptr){
        return;
    }
    particulas.push_back(p);
    p->dibujar(Escena);
}
void Rectangulo::mostrar(){
    vista->show();
}
Rectangulo::~Rectangulo(){
    delete vista;
    delete Escena;

    for(Particula *p:particulas){
        delete p;
    }
    particulas.clear();
}
void Rectangulo::agregarObstaculo(double x, double y, double ancho, double alto){
    obstaculo *nuevo= new obstaculo(x,y,ancho,alto);
    nuevo ->dibujar(Escena);
    obstaculos.push_back(nuevo);
}
void Rectangulo::actualizar(){
    double dt=reloj.restart()/1000.0;
    for(Particula *p: particulas){
        if (p !=nullptr && p -> estaActiva()){
            p -> mover(dt);
            comprobarParedes(p);
        }
    }
}
void Rectangulo::comprobarParedes(Particula *p){
    if (p==nullptr){
        return;
    }
    double r = p->getRadio();
    double x = p->getX();
    double y = p->getY();
    double vx = p->getVx();
    double vy=p->getVy();

    if(x+r > ancho){
        x=ancho-r;
        vx=abs(vy);
    }
    if(x-r < 0){
        x=r;
        vx=abs(vx);
    }
    if(y-r <0){
        y=r;
        vy=abs(vy);

    }
    if(y+r>alto){
        y=alto-r;
        vy=abs(vy);
    }
    p->setPosicion(x,y);
    p->setVelocidad(vx,vy);

}