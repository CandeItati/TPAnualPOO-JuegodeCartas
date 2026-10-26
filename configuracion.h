#ifndef CONFIGURACION_H
#define CONFIGURACION_H

#include <string>
#include <map>

#include "enums.h"


class Configuracion
{
public:
    Configuracion();

    int getCantidadCartas() const;
    std::string getTipoIA() const;

    int getDanio(const std::string& atacante,const std::string& defensor) const;

    int getDanio(TipoElemento atacante,TipoElemento defensor) const;

    void setCantidadCartas(int cantidad);
    void setTipoIA(const std::string& tipo);
    void setDanio(const std::string& clave,int valor);

private:
    int cantidadCartas;

    std::string tipoIA;
    std::map<std::string,int> tablaDanios;

};

#endif // CONFIGURACION_H
