#ifndef RESULTADOATAQUE_H
#define RESULTADOATAQUE_H

#include <string>

class ResultadoAtaque
{
public:
    ResultadoAtaque();

    bool atacaJugador;

    std::string atacante;
    std::string defensor;

    int danio = 0;

    bool defensorEliminado = false;
};

#endif
