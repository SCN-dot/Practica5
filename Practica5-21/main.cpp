#include <iostream>
#include "Caja.h"

using namespace std;

int main()
{
    cout << "INICIANDO SIMULACION" << endl;

    Rectangulo caja(100, 100);

    Particula *p1 = new Particula(
        1,
        50, 50,
        10, 5,
        2, 5
        );

    caja.agregarParticula(p1);

    cout << "PARTICULA CREADA" << endl;

    for (int i = 0; i < 10; i++)
    {
        caja.simular(1.0);

        cout << "Iteracion: " << i + 1 << endl;

        caja.mostrarEstado();
    }

    cout << "SIMULACION FINALIZADA" << endl;

    return 0;
}