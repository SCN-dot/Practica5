#include "Particula.h"
#include <cmath>
#include <QPen>
#include <QBrush>


Particula::Particula(int id, double x, double y, double vx, double vy, double masa, double radio)
    : id(id), x(x), y(y), vx(vx), vy(vy), masa(masa), radio(radio), activa(true), circulo(nullptr) {
}

int Particula::getId() const { return id; }
double Particula::getX() const { return x; }
double Particula::getY() const { return y; }
double Particula::getVx() const { return vx; }
double Particula::getVy() const { return vy; }
double Particula::getMasa() const { return masa; }
double Particula::getRadio() const { return radio; }
bool Particula::estaActiva() const { return activa; }

void Particula::setPosicion(double nx, double ny) {
    x = nx;
    y = ny;
    actualizarPosicion();
}

void Particula::setVelocidad(double nvx, double nvy) {
    vx = nvx;
    vy = nvy;
}

void Particula::mover(double dt) {
    x += vx * dt;
    y += vy * dt;
    actualizarPosicion();
}

bool Particula::colisionaCon(const Particula &otra) const {
    double dx = otra.x - x;
    double dy = otra.y - y;
    double suma = radio + otra.radio;
    return (dx * dx + dy * dy) <= suma * suma;
}

void Particula::fusionar(Particula &otra) {
    double m1 = masa;
    double m2 = otra.masa;
    double M = m1 + m2;

    // Conservacion del momento: v' = (m1*v1 + m2*v2) / (m1 + m2)
    double nvx = (m1 * vx + m2 * otra.vx) / M;
    double nvy = (m1 * vy + m2 * otra.vy) / M;

    // Centro de masa
    double nx = (m1 * x + m2 * otra.x) / M;
    double ny = (m1 * y + m2 * otra.y) / M;

    // Radio: se conserva el area (pi*R^2 = pi*r1^2 + pi*r2^2)
    double nradio = sqrt(radio * radio + otra.radio * otra.radio);

    masa = M;
    vx = nvx;
    vy = nvy;
    x = nx;
    y = ny;
    radio = nradio;

    otra.activa = false;
}
void Particula::actualizarPosicion(){
    if(circulo!=nullptr){
        circulo ->setRect(0,0,radio*2,radio*2);
        circulo ->setPos(x-radio,y-radio);
    }
}

void Particula::dibujar(QGraphicsScene * escena){
    if(escena== nullptr){
        return;
    }
    circulo = new QGraphicsEllipseItem(0 , 0 ,radio*2 , radio*2);
    circulo ->setBrush(QBrush(Qt::black));
    circulo ->setPen(QPen(Qt::red));
    escena -> addItem(circulo);
    actualizarPosicion();
}