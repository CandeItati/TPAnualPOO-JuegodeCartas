#include "sistemacombate.h" // Incluye la definición de la clase.

// ==============================
// Constructor
// ==============================

SistemaCombate::SistemaCombate()
{
    configuracion = nullptr;

    int datos[5][5] = {
        {25, 15, 50, 30, 60},
        {50, 25, 20, 15, 30},
        {30, 50, 25, 60, 15},
        {30, 60, 15, 25, 30},
        {15, 30, 50, 30, 25}
    };

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            matrizDanios[i][j] = datos[i][j];
        }
    }
}

SistemaCombate::SistemaCombate(Configuracion* config)
{
    configuracion = config;
}



// =========================================
// Calcula el daño entre dos elementos.
// =========================================
int SistemaCombate::calcularDanio(const Elemento& atacante,
                                  const Elemento& defensor)
{
    if (configuracion != nullptr)
    {
        return configuracion->getDanio(
            atacante.obtenerAtaque(),
            defensor.obtenerDefensa());
    }

    return matrizDanios[
        atacante.obtenerAtaque()
    ][
        defensor.obtenerDefensa()
    ];
}

// =========================================
// Aplica el daño al defensor.
// =========================================
void SistemaCombate::aplicarDanio(Elemento &atacante, Elemento &defensor)
{
    // Primero calcula cuánto daño corresponde.
    int danio = calcularDanio(atacante, defensor);

    // Luego le resta esa cantidad de vida al defensor.
    defensor.recibirDanio(danio);
}