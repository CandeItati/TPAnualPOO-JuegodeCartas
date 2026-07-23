#include "sistemacombate.h" // Incluye la definición de la clase.

// ==============================
// Constructor
// ==============================
SistemaCombate::SistemaCombate()
{
    // Matriz auxiliar con los daños ya definidos.
    // Cada fila representa un tipo de ataque.
    // Cada columna representa un tipo de defensa.
    int datos[5][5] = {{25, 15, 50, 30, 60},
                       {50, 25, 20, 15, 30},
                       {30, 50, 25, 60, 15},
                       {30, 60, 15, 25, 30},
                       {15, 30, 50, 30, 25}};

    // Recorre todas las filas de la matriz.
    for (int i = 0; i < 5; i++) {
        // Recorre todas las columnas.
        for (int j = 0; j < 5; j++) {
            // Copia cada valor de la matriz auxiliar
            // hacia la matriz de la clase.
            matrizDanios[i][j] = datos[i][j];
        }
    }
}

// =========================================
// Calcula el daño entre dos elementos.
// =========================================
int SistemaCombate::calcularDanio(const Elemento &atacante, const Elemento &defensor)
{
    // Obtiene el tipo de ataque del atacante.
    // Obtiene el tipo de defensa del defensor.
    // Esos valores se utilizan como índices de la matriz.
    // Devuelve el daño correspondiente.

    return matrizDanios[atacante.obtenerAtaque()][defensor.obtenerDefensa()];
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