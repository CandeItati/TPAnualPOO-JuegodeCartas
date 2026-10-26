#ifndef SUPERIA_H
#define SUPERIA_H

#include "contrincanteia.h"

class SuperIA : public ContrincanteIA
{
public:
    SuperIA();

    Elemento& seleccionarElemento() override;

    Elemento& seleccionarContra(
        const Elemento& enemigo) override;

    bool recalcularAnteCambio() const override;
};

#endif
