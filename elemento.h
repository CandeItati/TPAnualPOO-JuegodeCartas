#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <QString>
#include "enums.h"

class Elemento
{
public:
    Elemento();
    Elemento(QString nombre, TipoElemento Ataque, TipoElemento Defensa);

    int obtenerVida() const;
    QString obtenerNombre() const;
    TipoElemento obtenerAtaque() const;
    TipoElemento obtenerDefensa() const;
    void recibirDanio(int danio);
    bool estaVivo() const;
    bool esMixto() const;

private:
    QString nombre;
    int vida;
    TipoElemento tipoAtaque;
    TipoElemento tipoDefensa;
};


#endif // ELEMENTO_H
