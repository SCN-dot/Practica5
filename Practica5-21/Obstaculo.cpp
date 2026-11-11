#include "Obstaculo.h"

Obstaculo::Obstaculo(double x, double y, double ancho, double alto){
    this->x = x;
    this->y = y;
    this->ancho = ancho;
    this->alto = alto;
}

double Obstaculo::obtenerX() const { return x; }
double Obstaculo::obtenerY() const { return y; }
double Obstaculo::obtenerAncho() const { return ancho; }
double Obstaculo::obtenerAlto() const { return alto; }

Lado Obstaculo::ladoDeChoque(const Particula &p) const {
    double xMin = x, xMax = x + ancho;
    double yMin = y, yMax = y + alto;

    double px = p.getX();
    double py = p.getY();
    double r = p.getRadio();

    double cx = px;
    if (cx < xMin) cx = xMin;
    if (cx > xMax) cx = xMax;

    double cy = py;
    if (cy < yMin) cy = yMin;
    if (cy > yMax) cy = yMax;

    double dx = px - cx;
    double dy = py - cy;
    if (dx * dx + dy * dy > r * r) {
        return NINGUNO;
    }

    if (dx != 0 && dy != 0) {
        Lado ladoX = (dx < 0) ? IZQUIERDA : DERECHA;
        Lado ladoY = (dy < 0) ? ABAJO : ARRIBA;

        bool seAcercaX = (ladoX == IZQUIERDA && p.getVx() > 0) || (ladoX == DERECHA && p.getVx() < 0);
        bool seAcercaY = (ladoY == ABAJO && p.getVy() > 0) || (ladoY == ARRIBA && p.getVy() < 0);

        if (seAcercaX && !seAcercaY) return ladoX;
        if (seAcercaY && !seAcercaX) return ladoY;
        return (dx * dx > dy * dy) ? ladoX : ladoY;
    }

    if (dx != 0) {
        return (dx < 0) ? IZQUIERDA : DERECHA;
    }
    if (dy != 0) {
        return (dy < 0) ? ABAJO : ARRIBA;
    }

    double dIzq = px - xMin;
    double dDer = xMax - px;
    double dAba = py - yMin;
    double dArr = yMax - py;

    Lado lado = IZQUIERDA;
    double menor = dIzq;
    if (dDer < menor) { menor = dDer; lado = DERECHA; }
    if (dAba < menor) { menor = dAba; lado = ABAJO; }
    if (dArr < menor) { menor = dArr; lado = ARRIBA; }
    return lado;
}

void Obstaculo::sacarParticula(Particula &p, Lado lado) const {
    double r = p.getRadio();
    if (lado == IZQUIERDA) p.setPosicion(x - r, p.getY());
    if (lado == DERECHA)   p.setPosicion(x + ancho + r, p.getY());
    if (lado == ABAJO)     p.setPosicion(p.getX(), y - r);
    if (lado == ARRIBA)    p.setPosicion(p.getX(), y + alto + r);
}

Obstaculo::~Obstaculo()
{
}
