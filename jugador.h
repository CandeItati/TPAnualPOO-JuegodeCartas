#ifndef JUGADOR_H
#define JUGADOR_H

#include <vector>
#include "elemento.h"
#include "catalogoelementos.h"

using namespace std;


class Jugador
{
public:

    Jugador();

    virtual ~Jugador() = default;


    void repartirElementos();

    const vector<Elemento>& getElementos() const;
    bool tieneElementosVivos() const;


    virtual Elemento& seleccionarElemento() = 0;

    virtual Elemento& seleccionarContra(const Elemento &enemigo) = 0;


protected:

    vector<Elemento> elementos;

};


#endif