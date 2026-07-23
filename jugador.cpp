#include "jugador.h" // Incluye la definición de la clase.

// ==========================
// Constructor
// ==========================
Jugador::Jugador()
{
    // No hace nada porque el vector se inicializa automáticamente.
}

// ==========================
// Reparte los elementos.
// ==========================
void Jugador::repartirElementos()
{
    // Borra todos los elementos anteriores.
    // Así evita acumular elementos si se vuelve a repartir.
    elementos.clear();

    // Repite cinco veces.
    for (int i = 0; i < 5; i++) {
        // Crea un elemento aleatorio y lo agrega al final del vector.
        elementos.push_back(CatalogoElementos::crearElementoAleatorio());
    }
}

// ==========================
// Devuelve los elementos.
// ==========================
const vector<Elemento> &Jugador::getElementos() const
{
    // Devuelve una referencia al vector.
    // No hace una copia del mismo.
    return elementos;
}

// ==========================
// Verifica si quedan elementos vivos.
// ==========================
bool Jugador::tieneElementosVivos() const
{
    // Recorre todos los elementos del jugador.
    // "const Elemento &elemento" significa:
    // - No copiar el objeto.
    // - No permitir modificarlo.
    for (const Elemento &elemento : elementos) {
        // Si encuentra uno vivo...
        if (elemento.estaVivo()) {
            // ...ya puede devolver verdadero.
            return true;
        }
    }

    // Si terminó el recorrido y ninguno estaba vivo,
    // devuelve falso.
    return false;
}