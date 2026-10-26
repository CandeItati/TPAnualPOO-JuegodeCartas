#include "jugador.h" // Incluye la definición de la clase.

// ==========================
// Constructor
// ==========================
Jugador::Jugador()
{
    // No hace nada porque el vector se inicializa automáticamente.
}


void Jugador::setNombre(const std::string& nombre)
{
    this->nombre = nombre;
}

std::string Jugador::getNombre() const
{
    return nombre;
}
// ==========================
// Reparte los elementos.
// ==========================
void Jugador::repartirElementos(int cantidad)
{
    elementos.clear();

    for (int i = 0; i < cantidad; i++)
    {
        elementos.push_back(
            CatalogoElementos::crearElementoAleatorio());
    }
}

// ==========================
// Devuelve los elementos.
// ==========================
const std::vector<Elemento> & Jugador::getElementos() const
{
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

    // Si terminó el recorrido y ninguno estaba vivo, devuelve falso.
    return false;
}

void Jugador::agregarElemento(
    const Elemento& elemento)
{
    elementos.push_back(
        elemento);
}

void Jugador::limpiarElementos()
{
    elementos.clear();
}

void Jugador::cargarDesdeEstado(
    const std::vector<DatosCarta>& cartas)
{
    limpiarElementos();

    for(const DatosCarta& carta
         : cartas)
    {
        Elemento elemento =
            CatalogoElementos
            ::crearElementoPorNombre(
                carta.nombre);

        elemento.setVida(
            carta.vida);

        agregarElemento(
            elemento);
    }
}