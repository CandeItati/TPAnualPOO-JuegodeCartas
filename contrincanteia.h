#ifndef CONTRINCANTEIA_H          // Evita que el archivo se incluya más de una vez.
#define CONTRINCANTEIA_H

#include "jugador.h"             // Hereda de la clase Jugador.
#include "sistemacombate.h"      // Necesita el sistema de combate para analizar ataques.


// La clase ContrincanteIA representa cualquier jugador controlado
// por inteligencia artificial.
class ContrincanteIA : public Jugador
{
public:

    ContrincanteIA();            // Constructor.

    // Método virtual puro.
    // Cada tipo de IA decidirá cómo seleccionar su elemento.
    // El '= 0' indica que esta clase NO implementa el método.
    virtual Elemento &seleccionarElemento() override = 0;

    // También es un método virtual puro.
    // Cada IA decidirá cuál es el mejor elemento
    // para enfrentar al enemigo.
    virtual Elemento &seleccionarContra(const Elemento &enemigo) override = 0;

protected:

    // Objeto que contiene toda la lógica para calcular daños.
    // Las futuras IAs podrán usarlo para tomar decisiones.
    SistemaCombate sistema;
};

#endif