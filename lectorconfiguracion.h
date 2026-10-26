#ifndef LECTORCONFIGURACION_H
#define LECTORCONFIGURACION_H

#include <QString>

class Configuracion;

class LectorConfiguracion
{
public:
    bool cargarArchivo(
        const QString& nombreArchivo,
        Configuracion& configuracion);
};

#endif
