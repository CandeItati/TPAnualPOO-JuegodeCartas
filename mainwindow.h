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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onCartaJugadorClickeada(CartaGraphicsItem* carta);
    void onBtnAtacarClicked();
    void resolverCambioDeCartaIA();

private:
    Ui::MainWindow *ui;

    Juego *juego;
    Jugador *jugador1;
    Jugador *jugador2;

    QGraphicsScene *escena;
    std::vector<CartaGraphicsItem*> cartasJugador;
    std::vector<CartaGraphicsItem*> cartasIA;
    CartaGraphicsItem* cartaActivaJugador = nullptr;
    CartaGraphicsItem* cartaActivaIA = nullptr;

    QPushButton *btnAtacarCircular;
    QGraphicsProxyWidget *proxyBtnAtacar;
    QGraphicsTextItem *lblVS;

    const int anchoEscena = 980;
    const int alturaEscena = 700;

    void iniciarEscena();
    void colocarManoJugador();
    void mostrarDanioFlotante(int danio, QPointF posicion);
    void colocarManoIA();
    void actualizarPantalla();
    void mostrarFinDePartida();
    int indiceDeElemento(const std::vector<Elemento>& elementos, Elemento* buscado);
    bool retrasarSalidaCartaJugador = false;

    QWidget *overlayResultado = nullptr;
    QLabel  *lblResultadoTitulo = nullptr;
    QLabel  *lblResultadoSubtitulo = nullptr;
    QLabel *lblImagenResultado = nullptr;
    void crearOverlayResultado();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;

};

#endif