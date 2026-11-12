#include "Caja.h"
#include <iostream>

Caja::Caja(double ancho, double alto, double epsilon){
    this->ancho = ancho;
    this->alto = alto;
    this->epsilon = epsilon;
    this->tiempo = 0;
    this->siguienteId = 1;
    this->salida = nullptr;
}

static const char *nombreLado(Lado lado){
    if (lado == IZQUIERDA) return "IZQUIERDA";
    if (lado == DERECHA)   return "DERECHA";
    if (lado == ABAJO)     return "ABAJO";
    if (lado == ARRIBA)    return "ARRIBA";
    return "NINGUNO";
}

void Caja::agregarObstaculo(double x, double y, double ancho, double alto){
    obstaculos.push_back(new Obstaculo(x, y, ancho, alto));
}

ErrorCaja Caja::agregarParticula(Particula *p){
    if (p == nullptr){
        return CAJA_MASA_O_RADIO;
    }

    double r = p->getRadio();

    if (p->getMasa() <= 0 || r <= 0){
        return CAJA_MASA_O_RADIO;
    }

    if (p->getX() - r < 0 || p->getX() + r > ancho ||
        p->getY() - r < 0 || p->getY() + r > alto){
        return CAJA_FUERA_DE_CAJA;
    }

    for (Obstaculo *o : obstaculos){
        if (o->ladoDeChoque(*p) != NINGUNO){
            return CAJA_TRASLAPE_OBSTACULO;
        }
    }

    for (Particula *q : particulas){
        if (q->estaActiva() && q->colisionaCon(*p)){
            return CAJA_TRASLAPE_PARTICULA;
        }
    }

    particulas.push_back(p);
    if (p->getId() >= siguienteId){
        siguienteId = p->getId() + 1;
    }
    return CAJA_OK;
}

void Caja::setSalida(std::ofstream *archivo){
    salida = archivo;
}

void Caja::setTiempo(double t){
    tiempo = t;
}

void Caja::actualizar(double dt){
    for (Particula *p : particulas){
        if (p == nullptr || !p->estaActiva()) continue;

        p->mover(dt);
        procesarParedes(p);

        int intentos = 0;
        while (rebotarObstaculos(p) && intentos < 3){
            procesarParedes(p);
            intentos++;
        }
    }

    colisionesEntreParticulas();
}

bool Caja::comprobarParedes(Particula *p){
    double r = p->getRadio();
    double x = p->getX();
    double y = p->getY();
    double vx = p->getVx();
    double vy = p->getVy();
    bool rebote = false;

    if (x - r <= 0 && vx < 0)     { vx = -vx; x = r;         rebote = true; }
    if (x + r >= ancho && vx > 0) { vx = -vx; x = ancho - r; rebote = true; }
    if (y - r <= 0 && vy < 0)     { vy = -vy; y = r;         rebote = true; }
    if (y + r >= alto && vy > 0)  { vy = -vy; y = alto - r;  rebote = true; }

    if (rebote){
        p->setPosicion(x, y);
        p->setVelocidad(vx, vy);
    }
    return rebote;
}

void Caja::procesarParedes(Particula *p){
    double vxAntes = p->getVx();
    double vyAntes = p->getVy();

    if (comprobarParedes(p) && salida != nullptr){
        *salida << "COL_PARED_ELASTICA " << tiempo << " " << p->getId() << " "
                << p->getX() << " " << p->getY() << " "
                << vxAntes << " " << vyAntes << " "
                << p->getVx() << " " << p->getVy() << "\n";
    }
}

bool Caja::rebotarObstaculos(Particula *p){
    bool hubo = false;

    for (size_t k = 0; k < obstaculos.size(); k++){
        Lado lado = obstaculos[k]->ladoDeChoque(*p);
        if (lado == NINGUNO) continue;

        double vx = p->getVx();
        double vy = p->getVy();

        bool seAcerca = false;
        if (lado == IZQUIERDA && vx > 0) seAcerca = true;
        if (lado == DERECHA   && vx < 0) seAcerca = true;
        if (lado == ABAJO     && vy > 0) seAcerca = true;
        if (lado == ARRIBA    && vy < 0) seAcerca = true;
        if (!seAcerca) continue;

        double nvx = vx;
        double nvy = vy;
        if (lado == IZQUIERDA || lado == DERECHA){
            nvx = -epsilon * vx;
        } else {
            nvy = -epsilon * vy;
        }
        p->setVelocidad(nvx, nvy);
        obstaculos[k]->sacarParticula(*p, lado);
        hubo = true;

        if (salida != nullptr){
            *salida << "COL_OBSTACULO_INELASTICA " << tiempo << " " << p->getId() << " "
                    << (k + 1) << " " << nombreLado(lado) << " " << epsilon << " "
                    << p->getX() << " " << p->getY() << " "
                    << vx << " " << vy << " " << nvx << " " << nvy << "\n";
        }
    }
    return hubo;
}

void Caja::ubicarDentro(Particula *p){
    for (int i = 0; i < 4; i++){
        double r = p->getRadio();
        double x = p->getX();
        double y = p->getY();

        if (x < r) x = r;
        if (x > ancho - r) x = ancho - r;
        if (y < r) y = r;
        if (y > alto - r) y = alto - r;
        p->setPosicion(x, y);

        bool movida = false;
        for (Obstaculo *o : obstaculos){
            Lado lado = o->ladoDeChoque(*p);
            if (lado != NINGUNO){
                o->sacarParticula(*p, lado);
                movida = true;
            }
        }
        if (!movida) break;
    }

    double r = p->getRadio();
    double x = p->getX();
    double y = p->getY();
    if (x < r) x = r;
    if (x > ancho - r) x = ancho - r;
    if (y < r) y = r;
    if (y > alto - r) y = alto - r;
    p->setPosicion(x, y);
}

void Caja::colisionesEntreParticulas(){
    for (size_t i = 0; i < particulas.size(); i++){
        if (!particulas[i]->estaActiva()) continue;

        for (size_t j = i + 1; j < particulas.size(); j++){
            if (!particulas[j]->estaActiva()) continue;

            if (particulas[i]->colisionaCon(*particulas[j])){
                int idNueva = siguienteId++;
                Particula *nueva = new Particula(
                    particulas[i]->fusionarCon(*particulas[j], idNueva));
                ubicarDentro(nueva);

                const Particula *a = particulas[i];
                const Particula *b = particulas[j];

                if (salida != nullptr){
                    *salida << "FUSION_COMPLETAMENTE_INELASTICA " << tiempo << " "
                            << a->getId() << " " << b->getId() << " " << idNueva << " "
                            << nueva->getX() << " " << nueva->getY() << " "
                            << a->getMasa() << " " << a->getVx() << " " << a->getVy() << " "
                            << b->getMasa() << " " << b->getVx() << " " << b->getVy() << " "
                            << nueva->getMasa() << " " << nueva->getVx() << " " << nueva->getVy() << " "
                            << nueva->getRadio() << "\n";
                }

                particulas[i]->desactivar();
                particulas[j]->desactivar();
                particulas.push_back(nueva);

                break;
            }
        }
    }
}

void Caja::simular(double dt){
    actualizar(dt);
}

void Caja::mostrarEstado() const{
    for (const Particula *p : particulas){
        if (p != nullptr && p->estaActiva()){
            std::cout << "Particula " << p->getId() << " | X: " << p->getX()
            << " | Y: " << p->getY() << " | Vx: " << p->getVx()
            << " | Vy: " << p->getVy() << std::endl;
        }
    }
}

double Caja::getAncho() const { return ancho; }
double Caja::getAlto() const { return alto; }
double Caja::getEpsilon() const { return epsilon; }
int Caja::getSiguienteId() const { return siguienteId; }
const std::vector<Obstaculo*> &Caja::getObstaculos() const { return obstaculos; }
const std::vector<Particula*> &Caja::getParticulas() const { return particulas; }

Caja::~Caja(){
    for (Particula *p : particulas){
        delete p;
    }
    for (Obstaculo *o : obstaculos){
        delete o;
    }
    particulas.clear();
    obstaculos.clear();
}
