#include "lectorconfiguracion.h"
#include "configuracion.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>

bool LectorConfiguracion::cargarArchivo(
    const QString& nombreArchivo,
    Configuracion& configuracion)
{
    QFile archivo(nombreArchivo);

    if (!archivo.open(
            QIODevice::ReadOnly |
            QIODevice::Text))
    {
        return false;
    }

    QTextStream entrada(&archivo);

    while (!entrada.atEnd())
    {
        QString linea =
            entrada.readLine().trimmed();

        if (linea.isEmpty())
            continue;

        if (linea.startsWith("#"))
            continue;

        QStringList partes =
            linea.split("=");

        if (partes.size() != 2)
            continue;

        QString clave =
            partes[0].trimmed();

        QString valor =
            partes[1].trimmed();

        if (clave == "cantidad_cartas")
        {
            configuracion.setCantidadCartas(
                valor.toInt());
        }
        else if (clave == "tipo_ia")
        {
            configuracion.setTipoIA(valor.toStdString());
        }
        else
        {
            configuracion.setDanio(clave.toLower().toStdString(),valor.toInt());
        }
    }

    archivo.close();

    return true;
}
