#include "iaaleatoria.h" // Incluye la definición de la clase.

#include <cstdlib> // Permite utilizar la función rand().
#include <vector>  // Permite utilizar std::vector.

// ==========================
// Constructor
// ==========================
IAAleatoria::IAAleatoria()
{
    // No realiza ninguna acción.
}

// ==========================
// Selecciona un elemento para combatir.
// ==========================
Elemento &IAAleatoria::seleccionarContra(const Elemento &enemigo)
{
    // Indica que el parámetro enemigo no será utilizado.
    (void) enemigo;

    // Como esta IA es completamente aleatoria, simplemente llama al método que selecciona un elemento al azar.
    return seleccionarElemento();
}

// ==========================
// Selecciona un elemento vivo al azar.
// ==========================
Elemento &IAAleatoria::seleccionarElemento()
{
    // Vector donde se guardarán las posiciones de los elementos que todavía están vivos.
    std::vector<int> disponibles;

    // Recorre todos los elementos del jugador.
    for (int i = 0; i < elementos.size(); i++) {
        // Si el elemento sigue vivo...
        if (elementos[i].estaVivo()) {
            // ...guarda su posición.
            disponibles.push_back(i);
        }
    }

    // Genera un número aleatorio entre 0 y disponibles.size() - 1.
    int posicion = rand() % disponibles.size();

    // Devuelve el elemento ubicado en esa posición.
    return elementos[disponibles[posicion]];
}