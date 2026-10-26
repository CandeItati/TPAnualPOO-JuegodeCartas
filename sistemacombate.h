#ifndef SISTEMACOMBATE_H // Evita que este archivo se incluya más de una vez.
#define SISTEMACOMBATE_H

#include "elemento.h" // Se necesita la clase Elemento porque los métodos trabajan con ella.
#include "configuracion.h"

class SistemaCombate
{
public:               // Métodos accesibles desde otras clases.
    SistemaCombate();
    SistemaCombate(Configuracion* config);

    // Calcula cuánto daño le hace un elemento atacante a un defensor.
    // Se reciben por referencia constante (&) para no copiarlos y para asegurar que no serán modificados.
    int calcularDanio(const Elemento &atacante, const Elemento &defensor);

    // Aplica el daño al defensor.
    // El atacante se pasa por referencia porque no hace falta copiarlo.
    // El defensor también se pasa por referencia porque su vida será modificada.
    void aplicarDanio(Elemento &atacante, Elemento &defensor);

private: // Solo la propia clase puede acceder a estos datos.

    Configuracion* configuracion = nullptr;

    int matrizDanios[5][5];
};

#endif // SISTEMACOMBATE_H