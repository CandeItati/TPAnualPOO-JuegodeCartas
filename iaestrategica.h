#ifndef IAESTRATEGICA_H
#define IAESTRATEGICA_H

#include "contrincanteia.h"

class IAEstrategica : public ContrincanteIA
{
public:
    IAEstrategica();

    Elemento& seleccionarContra(const Elemento &enemigo) override;

};

#endif // IAESTRATEGICA_H
