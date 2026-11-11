QT += core gui widgets

TEMPLATE = app
TARGET = Practica5-21

CONFIG += c++17
CONFIG -= console
CONFIG -= app_bundle

SOURCES += \
    Caja.cpp \
    Obstaculo.cpp \
    Particula.cpp \
    main.cpp

HEADERS += \
    Caja.h \
    Obstaculo.h \
    Particula.h

FORMS +=