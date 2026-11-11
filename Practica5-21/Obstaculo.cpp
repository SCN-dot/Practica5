#include "Obstaculo.h"
#include <QGraphicsScene>
#include <Qpen>
#include <QBrush>

obstaculo::obstaculo(double x, double y, double ancho, double alto){
    this -> x = x;
    this -> y= y;
    this ->ancho = ancho;
    this ->alto= alto;

    rectangulo=nullptr;
}

void obstaculo::dibujar(QGraphicsScene * escena){
    rectangulo = new QGraphicsRectItem(x,y,ancho, alto);
    rectangulo -> setPen(QPen(Qt::blue));
    rectangulo -> setBrush(QBrush(Qt::gray));
    escena ->addItem(rectangulo);

}

double obstaculo::obtenerX()const{
    return x;
}
double obstaculo::obtenerY()const{
    return y;
}
double obstaculo::obtenerAncho()const{
    return ancho;
}
double obstaculo::obtenerAlto()const{
    return alto;
}

