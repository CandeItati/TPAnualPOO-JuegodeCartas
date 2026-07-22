#ifndef SISTEMACOMBATE_H
#define SISTEMACOMBATE_H

#include "elemento.h"

class SistemaCombate
{
public:
    SistemaCombate();

    int calcularDanio(const Elemento &atacante, const Elemento &defensor);

    void aplicarDanio(Elemento &atacante, Elemento &defensor);

private:
    int matrizDanios[5][5];
};

#endif // SISTEMACOMBATE_H
