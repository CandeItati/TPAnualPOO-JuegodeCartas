#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <string>
#include "enums.h"

class Elemento
{
public:
    Elemento();

    Elemento(std::string nombre,TipoElemento ataque,TipoElemento defensa);

    std::string obtenerNombre() const;

    TipoElemento obtenerAtaque() const;
    TipoElemento obtenerDefensa() const;

    int obtenerVida() const;

    void recibirDanio(int danio);

    bool estaVivo() const;
    bool esMixto() const;

    void setVida(int nuevaVida);

private:
    std::string nombre;

    int vida;

    TipoElemento tipoAtaque;
    TipoElemento tipoDefensa;
};

#endif