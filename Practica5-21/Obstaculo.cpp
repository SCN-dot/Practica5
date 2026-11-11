#include "Obstaculo.h"

obstaculo::obstaculo(double x, double y, double ancho, double alto){
    this->x = x;
    this->y = y;
    this->ancho = ancho;
    this->alto = alto;
}
double obstaculo::obtenerX() const{
    return x;
}
double obstaculo::obtenerY() const{
    return y;
}
double obstaculo::obtenerAncho() const{
    return ancho;
}
double obstaculo::obtenerAlto() const{
    return alto;
}
obstaculo::~obstaculo()
{
}