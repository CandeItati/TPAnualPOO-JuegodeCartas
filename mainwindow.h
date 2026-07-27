#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <vector>
#include <QLabel>

#include "juego.h"
#include "cartagraphicsitem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// La clase MainWindow es la ventana principal del juego.
// Se encarga de conectar la lógica del juego (clase Juego) con la interfaz gráfica, manejando la escena donde se dibujan las cartas y las animaciones.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor. Prepara la ventana, inicializa la lógica del juego y configura la interfaz inicial.
    explicit MainWindow(QWidget *parent = nullptr);
    // Destructor. Libera la memoria de los punteros y objetos creados para evitar fugas de memoria.
    ~MainWindow() override;

private slots:
    // Funciones que se ejecutan automáticamente en respuesta a una "señal" (como hacer clic en algo).

    // Se ejecuta cuando el jugador hace clic sobre una de sus cartas para enviarla a pelear.
    void onCartaJugadorClickeada(CartaGraphicsItem* carta);
    // Se ejecuta cuando el jugador presiona el botón central de "Atacar".
    void onBtnAtacarClicked();
    // Se ejecuta para procesar lógicamente y animar el momento en que la Inteligencia Artificial cambia su carta.
    void resolverCambioDeCartaIA();

private:
    // Puntero a los elementos de la interfaz creados visualmente.
    Ui::MainWindow *ui;

    Juego *juego; // Instancia principal que controla el reglamento, turnos y cálculos.
    Jugador *jugador1; // Referencia al jugador humano (sus datos, no sus gráficos).
    Jugador *jugador2; // Referencia a la Inteligencia Artificial.

    // Elementos gráficos.
    QGraphicsScene *escena; // Escena donde se colocan y animan todas las cartas.
    std::vector<CartaGraphicsItem*> cartasJugador; // Lista gráfica de las cartas en la mano del jugador humano.
    std::vector<CartaGraphicsItem*> cartasIA; // Lista gráfica de las cartas en la mano de la ia.

    CartaGraphicsItem* cartaActivaJugador = nullptr; // Puntero a la carta que el jugador eligio para combate.
    CartaGraphicsItem* cartaActivaIA = nullptr; // Puntero a la carta que la IA eligio para combate.

    QPushButton *btnAtacarCircular; // Botón visual para confirmar el ataque.
    QGraphicsProxyWidget *proxyBtnAtacar;
    QGraphicsTextItem *lblVS; // Texto decorativo "VS" que aparece en el centro cuando hay dos cartas en combate.

    // Constantes que definen el tamaño de la escena.
    const int anchoEscena = 980;
    const int alturaEscena = 700;

    void iniciarEscena();
    void colocarManoJugador();
    void mostrarDanioFlotante(int danio, QPointF posicion); // Crea una animación temporal de texto para mostrar cuánto daño se hizo.
    void colocarManoIA();
    void actualizarPantalla(); // Refresca la información general de la interfaz.
    void mostrarFinDePartida(); // Se encarga de detener el juego y mostrar la pantalla de victoria o derrota.
    // Método auxiliar que busca en una lista lógica de elementos cuál es el índice de un elemento.
    int indiceDeElemento(const std::vector<Elemento>& elementos, Elemento* buscado);
    // Bandera para crear una pausa o demora visual y evitar que las cartas y animaciones se sobrepongan.
    bool retrasarSalidaCartaJugador = false;

    // Se crea el mensaje de fin de partida.
    QWidget *overlayResultado = nullptr;
    QLabel  *lblResultadoTitulo = nullptr;
    QLabel  *lblResultadoSubtitulo = nullptr;
    QLabel *lblImagenResultado = nullptr;
    void crearOverlayResultado();

protected:
    // Se usa si el usuario o el sistema intenta cambiar el tamaño de la ventana.
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;

};

#endif