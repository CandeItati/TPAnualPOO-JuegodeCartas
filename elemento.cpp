#include "elemento.h"      // Incluye la definición de la clase Elemento.

// =========================
// Constructor por defecto
// =========================
Elemento::Elemento()
{
    nombre = "";           // El nombre comienza vacío.
    vida = 100;            // Todos los elementos comienzan con 100 de vida.
    tipoAtaque = FUEGO;    // Tipo de ataque por defecto.
    tipoDefensa = FUEGO;   // Tipo de defensa por defecto.
}

// =========================
// Constructor con parámetros
// =========================
Elemento::Elemento(QString nombre, TipoElemento Ataque, TipoElemento Defensa)
{
    this->nombre = nombre;         // Guarda el nombre recibido.

    this->vida = 100;              // Siempre comienza con 100 de vida.

    this->tipoAtaque = Ataque;     // Guarda el tipo de ataque recibido.
    this->tipoDefensa = Defensa;   // Guarda el tipo de defensa recibido.
}

// Devuelve la vida actual.
int Elemento::obtenerVida() const
{
    return vida;
}

// Devuelve el nombre.
QString Elemento::obtenerNombre() const
{
    return nombre;
}

// Devuelve el tipo de ataque.
TipoElemento Elemento::obtenerAtaque() const
{
    return tipoAtaque;
}

// Devuelve el tipo de defensa.
TipoElemento Elemento::obtenerDefensa() const
{
    return tipoDefensa;
}

// Resta la cantidad de daño recibida.
void Elemento::recibirDanio(int danio)
{
    vida -= danio;          // Equivale a: vida = vida - danio;

    // Si la vida quedó negativa, se deja en 0.
    if (vida < 0) {
        vida = 0;
    }
}

// Devuelve true si el elemento todavía tiene vida.
bool Elemento::estaVivo() const
{
    return vida > 0;
}

// Devuelve true si el tipo de ataque y defensa son diferentes.
bool Elemento::esMixto() const
{
    return tipoAtaque != tipoDefensa;
}