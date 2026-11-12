#include "Simulacion.h"

const char *mensajeError(Error e) {
    if (e == ERR_ENTRADA_INVALIDA)    return "entrada invalida: se esperaba un numero";
    if (e == ERR_POCAS_PARTICULAS)    return "se necesitan al menos 4 particulas";
    if (e == ERR_MASA_O_RADIO)        return "la masa y el radio deben ser mayores que 0";
    if (e == ERR_FUERA_DE_CAJA)       return "la particula se sale de la caja o toca una pared";
    if (e == ERR_TRASLAPE_OBSTACULO)  return "la particula empieza traslapada con un obstaculo";
    if (e == ERR_TRASLAPE_PARTICULA)  return "la particula empieza traslapada con otra particula";
    if (e == ERR_ARCHIVO)             return "no se pudo crear el archivo salida.txt";
    return "sin error";
}

Simulacion::Simulacion(double ancho, double alto, double dt, double epsilon)
    : caja(ancho, alto, epsilon), dt(dt), tiempo(0) { }

void Simulacion::agregarObstaculo(double x, double y, double ancho, double alto) {
    caja.agregarObstaculo(x, y, ancho, alto);
}

Error Simulacion::agregarParticula(double x, double y, double vx, double vy, double masa, double radio) {
    int id = caja.getSiguienteId();
    Particula *p = new Particula(id, x, y, vx, vy, masa, radio);

    ErrorCaja e = caja.agregarParticula(p);
    if (e == CAJA_OK) {
        return SIN_ERROR;
    }

    delete p;
    if (e == CAJA_MASA_O_RADIO)        return ERR_MASA_O_RADIO;
    if (e == CAJA_FUERA_DE_CAJA)       return ERR_FUERA_DE_CAJA;
    if (e == CAJA_TRASLAPE_OBSTACULO)  return ERR_TRASLAPE_OBSTACULO;
    return ERR_TRASLAPE_PARTICULA;
}

void Simulacion::escribirEncabezado(double duracion) {
    archivo << "# FORMATO: una etiqueta al inicio de cada linea\n";
    archivo << "# CAJA ancho alto\n";
    archivo << "# PARAM dt epsilon duracion\n";
    archivo << "# OBSTACULO numero x_min y_min ancho alto\n";
    archivo << "# POS t id x y vx vy masa radio\n";
    archivo << "# COL_PARED_ELASTICA t id x y vx_antes vy_antes vx_despues vy_despues\n";
    archivo << "# COL_OBSTACULO_INELASTICA t id obstaculo lado epsilon x y vx_antes vy_antes vx_despues vy_despues\n";
    archivo << "# FUSION_COMPLETAMENTE_INELASTICA t id1 id2 idNueva x y m1 vx1 vy1 m2 vx2 vy2 mNueva vxNueva vyNueva radioNueva\n";
    archivo << "# FIN estado t_final particulas_activas\n";

    archivo << "CAJA " << caja.getAncho() << " " << caja.getAlto() << "\n";
    archivo << "PARAM " << dt << " " << caja.getEpsilon() << " " << duracion << "\n";

    const std::vector<Obstaculo*> &obs = caja.getObstaculos();
    for (size_t k = 0; k < obs.size(); k++) {
        archivo << "OBSTACULO " << (k + 1) << " "
                << obs[k]->obtenerX() << " " << obs[k]->obtenerY() << " "
                << obs[k]->obtenerAncho() << " " << obs[k]->obtenerAlto() << "\n";
    }
}

void Simulacion::escribirParticulas() {
    const std::vector<Particula*> &ps = caja.getParticulas();
    for (size_t i = 0; i < ps.size(); i++) {
        const Particula *p = ps[i];
        if (!p->estaActiva()) continue;

        archivo << "POS " << tiempo << " " << p->getId() << " "
                << p->getX() << " " << p->getY() << " "
                << p->getVx() << " " << p->getVy() << " "
                << p->getMasa() << " " << p->getRadio() << "\n";
    }
}

Error Simulacion::ejecutar(double duracion, const char *nombreArchivo) {
    archivo.open(nombreArchivo);
    if (!archivo.is_open()) {
        return ERR_ARCHIVO;
    }

    caja.setSalida(&archivo);
    escribirEncabezado(duracion);

    int pasos = (int)(duracion / dt + 0.5);

    tiempo = 0;
    caja.setTiempo(tiempo);
    escribirParticulas();

    for (int i = 1; i <= pasos; i++) {
        tiempo = i * dt;
        caja.setTiempo(tiempo);
        caja.simular(dt);
        escribirParticulas();
    }

    int activas = 0;
    const std::vector<Particula*> &ps = caja.getParticulas();
    for (size_t i = 0; i < ps.size(); i++) {
        if (ps[i]->estaActiva()) activas++;
    }
    archivo << "FIN EXITO " << tiempo << " " << activas << "\n";

    caja.setSalida(nullptr);
    archivo.close();
    return SIN_ERROR;
}