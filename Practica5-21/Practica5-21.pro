TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Caja.cpp \
        Obstaculo.cpp \
        Particula.cpp \
        Simulacion.cpp \
        main.cpp

HEADERS += \
    Caja.h \
    Obstaculo.h \
    Particula.h \
    Simulacion.h

DISTFILES += \
    graficar.py
