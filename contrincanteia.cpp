#include "contrincanteia.h"


ContrincanteIA::ContrincanteIA()
{

}



Elemento& ContrincanteIA::seleccionarElemento()
{
    return elementos[0];
}



Elemento& ContrincanteIA::seleccionarContra(const Elemento &enemigo)
{
    Q_UNUSED(enemigo);

    return elementos[0];
}