#include "resultadoronda.h"

void ResultadoRonda::agregarAtaque(
    const ResultadoAtaque& ataque)
{
    ataques.push_back(ataque);
}

const std::vector<ResultadoAtaque>&
ResultadoRonda::getAtaques() const
{
    return ataques;
}

void ResultadoRonda::limpiar()
{
    ataques.clear();
}