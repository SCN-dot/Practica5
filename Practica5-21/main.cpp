#include <QApplication>
#include "Caja.h"
#include "Particula.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Rectangulo Rectangulo(500,500);
    Particula *p1 = new Particula(1,100,100,20,40,5,10);
    Rectangulo.agregarObstaculo(100,100,100,100);
    Particula *p2 = new Particula(2,200,150,-25,6,3,15);
    Particula *p3 = new Particula(3,300,250,34,-40,8,12);
    Rectangulo.agregarObstaculo(300,150,30,120);
    Rectangulo.agregarObstaculo(150,350,150,25);
    Rectangulo.agregarParticula(p1);
    Rectangulo.agregarParticula(p2);
    Rectangulo.agregarParticula(p3);
    Rectangulo.mostrar();
    return app.exec();
}
