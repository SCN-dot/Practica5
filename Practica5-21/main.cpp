#include <QApplication>
#include "Caja.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Rectangulo Rectangulo(500,500);
    Rectangulo.agregarObstaculo(100,100,100,100);
    Rectangulo.agregarObstaculo(300,150,30,120);
    Rectangulo.agregarObstaculo(150,350,150,25);
    Rectangulo.mostrar();
    return app.exec();
}
