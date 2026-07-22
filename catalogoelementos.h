#ifndef CATALOGOELEMENTOS_H
#define CATALOGOELEMENTOS_H

#include "elemento.h"


class CatalogoElementos
{
public:
    CatalogoElementos();

    static Elemento crearElementoAleatorio();

private:
    struct DatosElemento
    {
        QString nombre;
        TipoElemento ataque;
        TipoElemento defensa;
    };

    static const DatosElemento elementos[11];

};

#endif // CATALOGOELEMENTOS_H
