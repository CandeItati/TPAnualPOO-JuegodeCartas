#ifndef IAESTRATEGICA_H
#define IAESTRATEGICA_H

#include "contrincanteia.h"

class IAEstrategica
    : public ContrincanteIA
{
public:
    IAEstrategica();

    Elemento& seleccionarElemento() override;

    Elemento& seleccionarContra(
        const Elemento& enemigo) override;

    bool recalcularAnteCambio() const override;
};

#endif
