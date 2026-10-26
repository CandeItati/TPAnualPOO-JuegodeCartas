#include "elemento.h" // Incluye la definición de la clase Elemento.

// =========================
// Constructor por defecto
// =========================
Elemento::Elemento()
{
    nombre = "";         // El nombre comienza vacío.
    vida = 100;          // Todos los elementos comienzan con 100 de vida.
    tipoAtaque = FUEGO;  // Tipo de ataque por defecto.
    tipoDefensa = FUEGO; // Tipo de defensa por defecto.
}

// =========================
// Constructor con parámetros
// =========================
Elemento::Elemento(std::string nombre,TipoElemento ataque,TipoElemento defensa)
{
    this->nombre = nombre;
    this->vida = 100;
    this->tipoAtaque = ataque;
    this->tipoDefensa = defensa;
}

// Devuelve la vida actual.
int Elemento::obtenerVida() const
{
    return vida;
}

// Devuelve el nombre.
std::string Elemento::obtenerNombre() const
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
    vida -= danio; // Equivale a: vida = vida - danio;

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

void Elemento::setVida(
    int nuevaVida)
{
    vida = nuevaVida;
}