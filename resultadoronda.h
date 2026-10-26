#ifndef RESULTADORONDA_H
#define RESULTADORONDA_H

#include <vector>
#include "resultadoataque.h"

class ResultadoRonda
{
public:
    void agregarAtaque(const ResultadoAtaque& ataque);

    const std::vector<ResultadoAtaque>& getAtaques() const;

    void limpiar();

private:
    std::vector<ResultadoAtaque> ataques;
};

#endif
