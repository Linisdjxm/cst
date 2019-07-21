TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
    func.c \
    equation.c \
    sprog.c

QMAKE_CFLAGS += -std=c11 -Wall -O4

HEADERS += \
    func.h \
    equation.h \
    sprog.h

