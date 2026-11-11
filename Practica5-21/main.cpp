#include <QApplication>
#include "Caja.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Rectangulo Rectangulo(500,500);
    Rectangulo.mostrar();
    return app.exec();
}
