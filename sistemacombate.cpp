#include "sistemacombate.h"

SistemaCombate::SistemaCombate()
{
    int datos[5][5] =
        {
            {25,15,50,30,60},
            {50,25,20,15,30},
            {30,50,25,60,15},
            {30,60,15,25,30},
            {15,30,50,30,25}
        };

    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            matrizDanios[i][j]=datos[i][j];
        }
    }
}
int SistemaCombate::calcularDanio(const Elemento &atacante, const Elemento &defensor)
{
    return matrizDanios[atacante.obtenerAtaque()][defensor.obtenerDefensa()];
}
void SistemaCombate::aplicarDanio(Elemento &atacante, Elemento &defensor)
{
    int danio = calcularDanio(atacante, defensor);

    defensor.recibirDanio(danio);
}