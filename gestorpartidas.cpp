#include "gestorpartidas.h"
#include "juego.h"
#include "estadopartida.h"

#include <fstream>
#include <filesystem>
#include <sstream>

GestorPartidas::GestorPartidas()
{
}

bool GestorPartidas::guardarPartida(
    int slot,
    Juego* juego)
{
    if(slot < 1 || slot > 5)
    {
        return false;
    }

    (void)juego;

    if(!std::filesystem::exists("partidas"))
    {
        std::filesystem::create_directory(
            "partidas");
    }

    std::string nombreArchivo =
        "partidas/slot" +
        std::to_string(slot) +
        ".txt";

    std::ofstream archivo(
        nombreArchivo);

    if(!archivo.is_open())
    {
        return false;
    }

    std::ostream& salida = archivo;

    EstadoPartida estado =
        juego->crearEstadoPartida();

    salida
        << "NOMBRE="
        << estado.getNombreJugador()
        << "\n";

    salida
        << "TIPO_IA="
        << estado.getTipoIA()
        << "\n";

    salida << "CANTIDAD_CARTAS="
           << estado.getCantidadCartas()
           << "\n";

    salida << "\n[JUGADOR]\n";

    const auto& cartasJugador =
        estado.getCartasJugador();

    for(const DatosCarta& carta : cartasJugador)
    {
        salida
            << carta.nombre
            << ","
            << carta.vida
            << "\n";
    }

    salida << "\n[IA]\n";

    const auto& cartasIA =
        estado.getCartasIA();

    for(const DatosCarta& carta : cartasIA)
    {
        salida
            << carta.nombre
            << ","
            << carta.vida
            << "\n";
    }

    salida << "\nACTIVO_JUGADOR=";

    if(juego->getElementoActivoJugador())
    {
        salida
            << juego->getElementoActivoJugador()
                   ->obtenerNombre();

    }
    else
    {
        salida << "NINGUNO";
    }

    salida << "\n";

    salida << "\nACTIVO_IA=";

    if(juego->getElementoActivoIA())
    {
        salida
            << juego->getElementoActivoIA()
                   ->obtenerNombre();

    }
    else
    {
        salida << "NINGUNO";
    }

    salida << "\n";

    archivo.close();

    return true;
}

EstadoPartida
GestorPartidas::cargarPartida(
    int slot)
{
    EstadoPartida estado;

    if(slot < 1 || slot > 5)
    {
        return estado;
    }

    std::string nombreArchivo =
        "partidas/slot" +
        std::to_string(slot) +
        ".txt";

    std::ifstream archivo(
        nombreArchivo);

    if(!archivo.is_open())
    {
        return estado;
    }

    std::string linea;

    bool leyendoJugador = false;
    bool leyendoIA = false;

    while(std::getline(
        archivo,
        linea))
    {

        if(linea == "[JUGADOR]")
        {
            leyendoJugador = true;
            leyendoIA = false;
            continue;
        }

        if(linea == "[IA]")
        {
            leyendoJugador = false;
            leyendoIA = true;
            continue;
        }

        if(linea.rfind(
                "NOMBRE=",
                0) == 0)
        {
            estado.setNombreJugador(
                linea.substr(7));
        }

        else if(linea.rfind(
                     "TIPO_IA=",
                     0) == 0)
        {
            estado.setTipoIA(
                linea.substr(8));
        }

        else if(linea.rfind(
                     "CANTIDAD_CARTAS=",
                     0) == 0)
        {
            estado.setCantidadCartas(
                std::stoi(
                    linea.substr(16)));
        }

        else if(
            linea.rfind(
                "ACTIVO_JUGADOR=",
                0) == 0)
        {
            estado.setCartaActivaJugador(
                linea.substr(15));
        }

        else if(
            linea.rfind(
                "ACTIVO_IA=",
                0) == 0)
        {
            estado.setCartaActivaIA(
                linea.substr(10));
        }

        else if(
            leyendoJugador &&
            !linea.empty() &&
            linea.find(',') !=
                std::string::npos)
        {
            std::stringstream ss(
                linea);

            std::string nombre;
            std::string vidaTexto;

            std::getline(
                ss,
                nombre,
                ',');

            std::getline(
                ss,
                vidaTexto);

            DatosCarta carta;

            carta.nombre = nombre;

            carta.vida =
                std::stoi(
                    vidaTexto);

            estado.agregarCartaJugador(
                carta);
        }

        else if(
            leyendoIA &&
            !linea.empty() &&
            linea.find(',') !=
                std::string::npos)
        {
            std::stringstream ss(
                linea);

            std::string nombre;
            std::string vidaTexto;

            std::getline(
                ss,
                nombre,
                ',');

            std::getline(
                ss,
                vidaTexto);

            DatosCarta carta;

            carta.nombre = nombre;

            carta.vida =
                std::stoi(
                    vidaTexto);

            estado.agregarCartaIA(
                carta);
        }

    }

    archivo.close();

    return estado;
}

bool GestorPartidas::existeSlot(
    int slot)
{
    std::string nombreArchivo =
        "partidas/slot" +
        std::to_string(slot) +
        ".txt";

    return std::filesystem::exists(
        nombreArchivo);
}

bool GestorPartidas::guardarEstadoTemporal(
    const EstadoPartida& estado)
{
    if(!std::filesystem::exists("partidas"))
    {
        std::filesystem::create_directory(
            "partidas");
    }

    std::ofstream archivo(
        "partidas/reintento.txt");

    if(!archivo.is_open())
    {
        return false;
    }

    archivo
        << "NOMBRE="
        << estado.getNombreJugador()
        << "\n";

    archivo
        << "TIPO_IA="
        << estado.getTipoIA()
        << "\n";

    archivo
        << "CANTIDAD_CARTAS="
        << estado.getCantidadCartas()
        << "\n";

    archivo << "\n[JUGADOR]\n";


    for(const DatosCarta& carta :
         estado.getCartasJugador())
    {
        archivo
            << carta.nombre
            << ","
            << carta.vida
            << "\n";
    }

    archivo << "\n[IA]\n";

    for(const DatosCarta& carta :
         estado.getCartasIA())
    {
        archivo
            << carta.nombre
            << ","
            << carta.vida
            << "\n";
    }

    archivo
        << "\nACTIVO_JUGADOR=NINGUNO\n";

    archivo
        << "\nACTIVO_IA=NINGUNO\n";

    archivo.close();

    return true;
}

EstadoPartida
GestorPartidas::cargarEstadoTemporal()
{
    EstadoPartida estado;

    std::ifstream archivo(
        "partidas/reintento.txt");

    if(!archivo.is_open())
    {
        return estado;
    }

    std::string linea;
    bool leyendoJugador = false;
    bool leyendoIA = false;

    while(std::getline(
        archivo,
        linea))
    {
        if(linea == "[JUGADOR]")
        {
            leyendoJugador = true;
            leyendoIA = false;
            continue;
        }

        if(linea == "[IA]")
        {
            leyendoJugador = false;
            leyendoIA = true;
            continue;
        }

        if(linea.rfind(
                "NOMBRE=",
                0) == 0)
        {
            estado.setNombreJugador(
                linea.substr(7));
        }
        else if(linea.rfind(
                     "TIPO_IA=",
                     0) == 0)
        {
            estado.setTipoIA(
                linea.substr(8));
        }
        else if(linea.rfind(
                     "CANTIDAD_CARTAS=",
                     0) == 0)
        {
            estado.setCantidadCartas(
                std::stoi(
                    linea.substr(16)));
        }
        else if(linea.rfind(
                     "ACTIVO_JUGADOR=",
                     0) == 0)
        {
            estado.setCartaActivaJugador(
                linea.substr(15));
        }
        else if(linea.rfind(
                     "ACTIVO_IA=",
                     0) == 0)
        {
            estado.setCartaActivaIA(
                linea.substr(10));
        }
        else if(
            leyendoJugador &&
            linea.find(',') !=
                std::string::npos)
        {
            std::stringstream ss(
                linea);

            DatosCarta carta;
            std::string vidaTexto;

            std::getline(
                ss,
                carta.nombre,
                ',');

            std::getline(
                ss,
                vidaTexto);

            carta.vida =
                std::stoi(
                    vidaTexto);

            estado.agregarCartaJugador(
                carta);
        }
        else if(
            leyendoIA &&
            linea.find(',') !=
                std::string::npos)
        {
            std::stringstream ss(
                linea);

            DatosCarta carta;
            std::string vidaTexto;

            std::getline(
                ss,
                carta.nombre,
                ',');

            std::getline(
                ss,
                vidaTexto);

            carta.vida =
                std::stoi(
                    vidaTexto);

            estado.agregarCartaIA(
                carta);
        }
    }

    return estado;
}