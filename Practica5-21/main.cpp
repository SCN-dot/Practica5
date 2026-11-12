#include "Simulacion.h"

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <cstdlib>
using namespace std;

const double ANCHO_CAJA = 100.0;
const double ALTO_CAJA = 100.0;
const double DT = 0.01;
const double EPSILON = 0.7;
const double DURACION = 20.0;
const int MIN_PARTICULAS = 4;

const double RADIO_MAXIMO = min(ANCHO_CAJA, ALTO_CAJA) / 10.0;

const double obstaculos[4][4] = {
    {20, 20, 10, 10},
    {70, 20, 10, 10},
    {20, 70, 10, 10},
    {70, 70, 10, 10}
};

double leerNumero(const string &mensaje){
    string linea;
    double valor;

    while (true) {
        cout << mensaje;
        if (!getline(cin, linea)) {
            cout << "Entrada finalizada." << endl;
            exit(EXIT_FAILURE);
        }
        stringstream entrada(linea);
        char extra;
        if ((entrada >> valor) && !(entrada >> extra) && isfinite(valor)) {
            return valor;
        }
        cout << "Entrada invalida. Ingrese un numero real valido." << endl;
    }
}

int leerEntero(const string &mensaje){
    string linea;
    int valor;

    while (true) {
        cout << mensaje;

        if (!getline(cin, linea)) {
            cout << "Entrada finalizada." << endl;
            exit(EXIT_FAILURE);
        }
        stringstream entrada(linea);
        char extra;

        if ((entrada >> valor) && !(entrada >> extra)) {
            return valor;
        }
        cout << "Entrada invalida. Ingrese un numero entero." << endl;
    }
}

void mostrarObstaculos()
{
    cout << endl << "Obstaculos de la caja:" << endl;

    for (int i = 0; i < 4; i++) {
        cout << "Obstaculo " << i + 1 << ": ";
        cout << "X [" << obstaculos[i][0] << " - "<< obstaculos[i][0] + obstaculos[i][2] << "] | ";
        cout << "Y [" << obstaculos[i][1] << " - " << obstaculos[i][1] + obstaculos[i][3] << "]" << endl;
    }
}

Error ingresarParticula(Simulacion &sim, int numero, double ancho, double alto)
{
    double masa;
    double radio;
    double vx;
    double vy;
    double x;
    double y;

    cout << endl << "Ingreso de particula " << numero << endl;

    do {
        masa = leerNumero("Masa de la particula: ");

        if (masa <= 0) {
            cout << "La masa debe ser mayor que cero." << endl;
        }

    } while (masa <= 0);

    cout << "Radio permitido: mayor que 0 y menor o igual a " << RADIO_MAXIMO << endl;

    do {
        radio = leerNumero("Radio de la particula: ");

        if (radio <= 0 || radio > RADIO_MAXIMO) {
            cout << "Radio no permitido. Intente nuevamente." << endl;
        }

    }
    while (radio <= 0 || radio > RADIO_MAXIMO);

    cout << endl << "Velocidad inicial" << endl;

    vx = leerNumero("Velocidad horizontal (Vx): ");
    vy = leerNumero("Velocidad vertical (Vy): ");

    double minimoX = radio;
    double maximoX = ancho - radio;
    double minimoY = radio;
    double maximoY = alto - radio;

    while (true) {
        cout << endl << "Posicion de la particula" << endl;
        cout << "Las coordenadas corresponden al centro de la particula." << endl;

        cout << "Rango de X: " << minimoX << " hasta " << maximoX << endl;
        cout << "Rango de Y: " << minimoY << " hasta " << maximoY << endl;

        mostrarObstaculos();

        x = leerNumero("Coordenada X: ");
        y = leerNumero("Coordenada Y: ");

        if (x < minimoX || x > maximoX ||y < minimoY || y > maximoY) {
            cout << "La particula queda fuera de la caja. " << "Ingrese otra posicion." << endl;
            continue;
        }

        Error e = sim.agregarParticula(x, y, vx, vy, masa, radio);

        if (e == SIN_ERROR) {
            cout << "Particula " << numero << " agregada correctamente." << endl;
            cout << "Posicion: (" << x << ", " << y << ")" << endl;
            cout << "Velocidad: (" << vx << ", " << vy << ")" << endl;
            cout << "Masa: " << masa << endl;
            cout << "Radio: " << radio << endl;

            return SIN_ERROR;
        }

        cout << "Posicion no disponible: " << mensajeError(e) << endl;
        cout << "Ingrese otras coordenadas." << endl;
    }
}

int main()
{
    cout << "Simulacion de particulas" << endl;

    cout << endl << "Configuracion de la caja" << endl;
    cout << "Ancho: " << ANCHO_CAJA << endl;
    cout << "Alto: " << ALTO_CAJA << endl;
    cout << "Paso temporal: " << DT << endl;
    cout << "Epsilon: " << EPSILON << endl;
    cout << "Duracion: " << DURACION << endl;

    Simulacion sim(ANCHO_CAJA, ALTO_CAJA, DT, EPSILON);

    cout << endl << "Creando obstaculos..." << endl;

    for (int i = 0; i < 4; i++) {
        sim.agregarObstaculo(
            obstaculos[i][0],
            obstaculos[i][1],
            obstaculos[i][2],
            obstaculos[i][3]
            );

        cout << "Obstaculo " << i + 1 << " agregado." << endl;
    }

    mostrarObstaculos();

    cout << endl << "Numero de particulas" << endl;
    cout << "Minimo requerido: " << MIN_PARTICULAS << endl;

    int n;

    do {
        n = leerEntero("Cantidad de particulas: ");

        if (n < MIN_PARTICULAS) {
            cout << "Debe ingresar al menos "<< MIN_PARTICULAS << " particulas." << endl;
        }

    }
    while (n < MIN_PARTICULAS);

    for (int i = 1; i <= n; i++) {
        Error e = ingresarParticula(sim, i, ANCHO_CAJA, ALTO_CAJA);

        if (e != SIN_ERROR) {
            cout << "No fue posible ingresar la particula." << endl;
            cout << mensajeError(e) << endl;
            return EXIT_FAILURE;
        }
    }

    cout << endl << "Iniciando simulacion..." << endl;
    cout << "Cantidad de particulas: " << n << endl;
    cout << "Duracion: " << DURACION << endl;

    Error resultado = sim.ejecutar(DURACION, "salida.txt");

    if (resultado != SIN_ERROR) {
        cout << "Error en la simulacion: "
             << mensajeError(resultado) << endl;

        return EXIT_FAILURE;
    }

    cout << endl << "Simulacion finalizada correctamente." << endl;
    cout << "Resultados guardados en salida.txt" << endl;

    return EXIT_SUCCESS;
}