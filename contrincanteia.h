#ifndef CONTRINCANTEIA_H
#define CONTRINCANTEIA_H

#include "jugador.h"
#include "sistemacombate.h"


class ContrincanteIA : public Jugador
{
public:

    ContrincanteIA();


    virtual Elemento& seleccionarElemento() override = 0;

    virtual Elemento& seleccionarContra(const Elemento &enemigo) override = 0;


protected:

    SistemaCombate sistema;

};


#endif