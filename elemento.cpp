#include "elemento.h"

Elemento::Elemento()
{
    nombre = "";
    vida = 100;
    tipoAtaque = FUEGO;
    tipoDefensa = FUEGO;

}

Elemento::Elemento(QString nombre, TipoElemento Ataque, TipoElemento Defensa)
{
    this->nombre = nombre;
    this->vida = 100;
    this->tipoAtaque = Ataque;
    this->tipoDefensa = Defensa;
}

int Elemento::obtenerVida() const
{
    return vida;
}
QString Elemento::obtenerNombre() const
{
    return nombre;
}
TipoElemento Elemento::obtenerAtaque() const
{
    return tipoAtaque;
}
TipoElemento Elemento::obtenerDefensa() const
{
    return tipoDefensa;
}
void Elemento::recibirDanio(int danio)
{
    vida -= danio;

    if (vida < 0)
    {
        vida = 0;
    }
}
bool Elemento::estaVivo() const
{
    return vida > 0;
}
bool Elemento::esMixto() const
{
    return tipoAtaque != tipoDefensa;
}
