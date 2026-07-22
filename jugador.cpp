#include "jugador.h"


Jugador::Jugador()
{

}



void Jugador::repartirElementos()
{
    elementos.clear();


    for(int i = 0; i < 5; i++)
    {
        elementos.push_back(
            CatalogoElementos::crearElementoAleatorio()
            );
    }
}
const vector<Elemento>& Jugador::getElementos() const
{
    return elementos;
}
bool Jugador::tieneElementosVivos() const
{
    for (const Elemento &elemento : elementos)
    {
        if (elemento.estaVivo())
        {
            return true;
        }
    }

    return false;
}