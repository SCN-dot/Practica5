#include "Caja.h"
#include <iostream>
#include <cmath>
using namespace std;

Rectangulo::Rectangulo(double ancho, double alto){
    this->ancho = ancho;
    this->alto = alto;
}

void Rectangulo::agregarParticula(Particula *p){
    if (p == nullptr){
        return;
    }

    particulas.push_back(p);
}

void Rectangulo::agregarObstaculo(double x, double y, double ancho, double alto){
    obstaculo *nuevo = new obstaculo(x, y, ancho, alto);
    obstaculos.push_back(nuevo);
}

void Rectangulo::actualizar(double dt){
    for (Particula *p : particulas){
        if (p != nullptr && p->estaActiva()){
            p->mover(dt);
            comprobarParedes(p);
        }
    }
}

void Rectangulo::comprobarParedes(Particula *p){
    if (p == nullptr){
        return;
    }

    double r = p->getRadio();
    double x = p->getX();
    double y = p->getY();
    double vx = p->getVx();
    double vy = p->getVy();

    if (x - r < 0){
        x = r;
        vx = abs(vx);
    }

    if (x + r > ancho){
        x = ancho - r;
        vx = abs(vx);
    }

    if (y - r < 0){
        y = r;
        vy = abs(vy);
    }

    if (y + r > alto){
        y = alto - r;
        vy = abs(vy);
    }

    p->setPosicion(x, y);
    p->setVelocidad(vx, vy);
}

void Rectangulo::simular(double dt){
    actualizar(dt);
}

void Rectangulo::mostrarEstado() const{
    for (const Particula *p : particulas){
        if (p != nullptr && p->estaActiva()){
            std::cout << "Particula " << p->getId()
            << " | X: " << p->getX()
            << " | Y: " << p->getY()
            << " | Vx: " << p->getVx()
            << " | Vy: " << p->getVy()
            << '\n';
        }
    }
}

Rectangulo::~Rectangulo(){
    for (Particula *p : particulas){
        delete p;
    }

    for (obstaculo *o : obstaculos){
        delete o;
    }

    particulas.clear();
    obstaculos.clear();
}