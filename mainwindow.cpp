#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "iaaleatoria.h"
#include "jugadorhumano.h"
#include <QGraphicsTextItem>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    jugador1 = new JugadorHumano();
    jugador2 = new IAAleatoria();
    juego = new Juego(jugador1, jugador2);

    iniciarEscena();
    crearOverlayResultado();
    actualizarPantalla();

    ui->textEdit->append("--- ¡Comienza la partida! Elegí tu primera carta ---");
}

MainWindow::~MainWindow()
{
    delete juego;
    delete jugador1;
    delete jugador2;
    delete ui;
}

// Busca en qué posición del vector está el Elemento apuntado por 'buscado'
int MainWindow::indiceDeElemento(const std::vector<Elemento>& elementos, Elemento* buscado)
{
    for (size_t i = 0; i < elementos.size(); i++) {
        if (&elementos[i] == buscado) return (int)i;
    }
    return -1;
}

void MainWindow::iniciarEscena()
{
    escena = new QGraphicsScene(this);
    escena->setSceneRect(0, 0, anchoEscena, alturaEscena);

    QPixmap fondo(":/new/prefix1/Imagenes/Tablero3_ajustado.png");
    QGraphicsPixmapItem* fondoItem = new QGraphicsPixmapItem(
        fondo.scaled(anchoEscena, alturaEscena, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    fondoItem->setZValue(-100);
    escena->addItem(fondoItem);

    ui->graphicsViewMesa->setScene(escena);
    ui->graphicsViewMesa->setRenderHint(QPainter::Antialiasing);

    colocarManoJugador();
    colocarManoIA();

    btnAtacarCircular = new QPushButton("ATACAR");
    btnAtacarCircular->setFixedSize(80, 80);
    btnAtacarCircular->setStyleSheet(
        "QPushButton { background-color: #c0392b; color: white; border-radius: 40px; font-weight: bold; }"
        "QPushButton:hover { background-color: #e74c3c; }");
    proxyBtnAtacar = escena->addWidget(btnAtacarCircular);
    proxyBtnAtacar->setPos(anchoEscena / 2.0 + CartaGraphicsItem::ANCHO + 80,
                           alturaEscena / 2.0 - CartaGraphicsItem::ALTO / 2.0 + 50);
    proxyBtnAtacar->setVisible(false);

    connect(btnAtacarCircular, &QPushButton::clicked, this, &MainWindow::onBtnAtacarClicked);

    // Texto "VS" en el medio, entre las dos cartas que se enfrentan
    lblVS = new QGraphicsTextItem("VS");
    QFont fuenteVS("Arial", 22, QFont::Black);
    lblVS->setFont(fuenteVS);
    lblVS->setDefaultTextColor(QColor(0xf1, 0xc4, 0x0f));
    lblVS->setZValue(4);
    lblVS->setPos(anchoEscena / 2.0 - 25, alturaEscena / 2.0 - CartaGraphicsItem::ALTO / 2.0 + 65);
    lblVS->setVisible(false);
    escena->addItem(lblVS);
}

void MainWindow::crearOverlayResultado()
{
    overlayResultado = new QWidget(ui->centralwidget);
    overlayResultado->setObjectName("overlayResultado");
    overlayResultado->setStyleSheet(
        "QWidget#overlayResultado { background-color: rgba(0, 0, 0, 170); }");
    overlayResultado->setGeometry(ui->centralwidget->rect());
    overlayResultado->hide();

    auto* panel = new QWidget(overlayResultado);
    panel->setObjectName("panelResultado");
    panel->setFixedSize(420, 320);

    lblImagenResultado = new QLabel(panel);
    lblImagenResultado->setAlignment(Qt::AlignCenter);
    lblImagenResultado->setFixedSize(110, 110);

    panel->setStyleSheet(
        "QWidget#panelResultado {"
        "  background-color: #1c1f2e;"
        "  border: 3px solid #f1c40f;"
        "  border-radius: 16px;"
        "}");

    lblResultadoTitulo = new QLabel(panel);
    lblResultadoTitulo->setAlignment(Qt::AlignCenter);
    lblResultadoTitulo->setFont(QFont("Arial", 34, QFont::Black));

    lblResultadoSubtitulo = new QLabel(panel);
    lblResultadoSubtitulo->setAlignment(Qt::AlignCenter);
    lblResultadoSubtitulo->setFont(QFont("Arial", 14));
    lblResultadoSubtitulo->setStyleSheet("color: white;");

    auto* btnCerrar = new QPushButton("Cerrar", panel);
    btnCerrar->setFixedSize(110, 34);
    btnCerrar->setStyleSheet(
        "QPushButton { background-color: #f1c40f; color: #1c1f2e; border-radius: 6px; font-weight: bold; }"
        "QPushButton:hover { background-color: #f7dc6f; }");
    connect(btnCerrar, &QPushButton::clicked, overlayResultado, &QWidget::hide);

    auto* layout = new QVBoxLayout(panel);
    layout->addStretch();
    layout->addWidget(lblResultadoTitulo);
    layout->addWidget(lblResultadoSubtitulo);
    layout->addWidget(lblImagenResultado, 0, Qt::AlignCenter);
    layout->addSpacing(12);
    layout->addWidget(btnCerrar, 0, Qt::AlignCenter);
    layout->addStretch();

    auto* layoutOverlay = new QVBoxLayout(overlayResultado);
    layoutOverlay->addWidget(panel, 0, Qt::AlignCenter);
}

void MainWindow::colocarManoJugador()
{
    const std::vector<Elemento>& elementos = jugador1->getElementos();
    int espaciado = CartaGraphicsItem::ANCHO + 30;
    int anchoTotal = espaciado * (int)elementos.size();
    int xInicial = ((anchoEscena - anchoTotal) / 2) + 16;
    int y = alturaEscena - CartaGraphicsItem::ALTO - 20;

    for (int i = 0; i < (int)elementos.size(); i++) {
        auto* carta = new CartaGraphicsItem(elementos[i]);
        QPointF posicion(xInicial + i * espaciado, y);   // 1) declarás la variable
        carta->setPos(posicion);                          // 2) usás la variable acá (antes tenías los números sueltos)
        carta->establecerPosicionFila(posicion);
        connect(carta, &CartaGraphicsItem::clickeada, this, &MainWindow::onCartaJugadorClickeada);
        escena->addItem(carta);
        cartasJugador.push_back(carta);
    }
}

void MainWindow::colocarManoIA()
{
    const std::vector<Elemento>& elementos = jugador2->getElementos();
    int espaciado = CartaGraphicsItem::ANCHO + 30;
    int anchoTotal = espaciado * (int)elementos.size();
    int xInicial = ((anchoEscena - anchoTotal) / 2) + 16;
    int y = 20;

    for (int i = 0; i < (int)elementos.size(); i++) {
        auto* carta = new CartaGraphicsItem(elementos[i]);
        QPointF posicion(xInicial + i * espaciado, y);
        carta->setPos(posicion);
        carta->establecerPosicionFila(posicion);
        carta->establecerSeleccionable(false);
        escena->addItem(carta);
        cartasIA.push_back(carta);
    }
}

void MainWindow::onCartaJugadorClickeada(CartaGraphicsItem* carta)
{

    if (juego->termino()) return;

    int indice = -1;
    for (size_t i = 0; i < cartasJugador.size(); i++) {
        if (cartasJugador[i] == carta) { indice = (int)i; break; }
    }
    if (indice == -1) return;

    juego->seleccionarElemento(indice);
    ui->textEdit->append(QString("<span style='color:#3498db;'>➤ Elegiste: <b>%1</b></span>").arg(jugador1->getElementos()[indice].obtenerNombre()));

    actualizarPantalla();
}

void MainWindow::onBtnAtacarClicked()
{

    if (juego->termino()) return;

    Elemento* elemJugador = juego->getElementoActivoJugador();
    Elemento* elemIA = juego->getElementoActivoIA();
    int vidaJugadorAntes = elemJugador ? elemJugador->obtenerVida() : 0;
    int vidaIAAntes = elemIA ? elemIA->obtenerVida() : 0;

    juego->resolverTurno();

    ui->textEdit->append("<hr>");
    QStringList lineas = juego->getMensajeEstado().split("\n");
    for (const QString& linea : std::as_const(lineas)) {
        if (!linea.trimmed().isEmpty())
            ui->textEdit->append("<span style='color:#2c3e50;'>⚔ " + linea.toHtmlEscaped() + "</span>");
    }

    if (elemJugador) {
        int danio = vidaJugadorAntes - elemJugador->obtenerVida();
        if (danio > 0 && cartaActivaJugador)
            mostrarDanioFlotante(danio, cartaActivaJugador->pos() + QPointF(CartaGraphicsItem::ANCHO / 2 - 15, 10));
    }
    if (elemIA) {
        int danio = vidaIAAntes - elemIA->obtenerVida();
        if (danio > 0 && cartaActivaIA)
            mostrarDanioFlotante(danio, cartaActivaIA->pos() + QPointF(CartaGraphicsItem::ANCHO / 2 - 15, 10));
    }

    actualizarPantalla();

    if (juego->iaNecesitaCambiarYAtacar()) {
        // La carta de la IA murió: le damos una pausa visual antes de que
        // elija una nueva y ataque, para que se note con claridad que es
        // OTRA carta la que está golpeando (y no la que acaba de morir).
        QTimer::singleShot(700, this, &MainWindow::resolverCambioDeCartaIA);
    } else {
        btnAtacarCircular->setEnabled(!juego->termino());
    }
}

void MainWindow::resolverCambioDeCartaIA()
{
    Elemento* elemJugadorAntes = juego->getElementoActivoJugador();
    int vidaJugadorAntes = elemJugadorAntes ? elemJugadorAntes->obtenerVida() : 0;

    QPointF posJugadorAntes = cartaActivaJugador ? cartaActivaJugador->pos() : QPointF();
    bool teniaCartaJugador = (cartaActivaJugador != nullptr);

    juego->resolverCambioIA();

    QStringList lineas = juego->getMensajeEstado().split("\n");
    for (const QString& linea : std::as_const(lineas)) {
        if (!linea.trimmed().isEmpty())
            ui->textEdit->append("<span style='color:#e67e22;'>🔄 " + linea.toHtmlEscaped() + "</span>");
    }

    // Si la carta del jugador murió con este golpe, le pedimos a
    // actualizarPantalla() que todavía NO la saque del centro: primero
    // queremos que se vea el número de daño sobre ella, y recién
    // después dejarla retirarse.
    retrasarSalidaCartaJugador = true;
    actualizarPantalla();

    QTimer::singleShot(380, this, [this, elemJugadorAntes, vidaJugadorAntes, posJugadorAntes, teniaCartaJugador]() {
        if (elemJugadorAntes) {
            int danio = vidaJugadorAntes - elemJugadorAntes->obtenerVida();
            if (danio > 0 && teniaCartaJugador)
                mostrarDanioFlotante(danio, posJugadorAntes + QPointF(CartaGraphicsItem::ANCHO / 2 - 15, 10));
        }

        // Un ratito más para que dé tiempo a leer el número antes de
        // que la carta derrotada recién ahí se retire del centro.
        QTimer::singleShot(600, this, [this]() {
            retrasarSalidaCartaJugador = false;
            actualizarPantalla();
            btnAtacarCircular->setEnabled(!juego->termino());
        });
    });
}

void MainWindow::actualizarPantalla()
{
    const std::vector<Elemento>& elementosJugador = jugador1->getElementos();
    const std::vector<Elemento>& elementosIA = jugador2->getElementos();

    for (size_t i = 0; i < cartasJugador.size(); i++)
        cartasJugador[i]->actualizarVida(elementosJugador[i].obtenerVida());
    for (size_t i = 0; i < cartasIA.size(); i++)
        cartasIA[i]->actualizarVida(elementosIA[i].obtenerVida());

    if (juego->hayElementosSeleccionados()) {
        Elemento* activoJugador = juego->getElementoActivoJugador();
        Elemento* activoIA = juego->getElementoActivoIA();

        int idxJ = indiceDeElemento(elementosJugador, activoJugador);
        int idxIA = indiceDeElemento(elementosIA, activoIA);

        CartaGraphicsItem* nuevaActivaJugador = (idxJ != -1) ? cartasJugador[idxJ] : nullptr;
        CartaGraphicsItem* nuevaActivaIA = (idxIA != -1) ? cartasIA[idxIA] : nullptr;

        QPointF centro(anchoEscena / 2.0, alturaEscena / 2.0 - CartaGraphicsItem::ALTO / 2.0);
        qreal separacion = 90;
        QPointF posJugadorCentro(centro.x() - CartaGraphicsItem::ANCHO - separacion / 2.0, centro.y());
        QPointF posIACentro(centro.x() + separacion / 2.0, centro.y());

        if (nuevaActivaJugador != cartaActivaJugador) {
            if (cartaActivaJugador) {
                cartaActivaJugador->volverAFila();
                cartaActivaJugador->establecerEnCombate(false);
                if (!cartaActivaJugador->estaDerrotada())
                    cartaActivaJugador->establecerSeleccionable(true);
            }
            cartaActivaJugador = nuevaActivaJugador;
            if (cartaActivaJugador) {
                cartaActivaJugador->setZValue(5);
                cartaActivaJugador->moverA(posJugadorCentro);
                cartaActivaJugador->establecerSeleccionable(false);
                cartaActivaJugador->establecerEnCombate(true);
            }
        }

        if (nuevaActivaIA != cartaActivaIA) {
            if (cartaActivaIA) {
                cartaActivaIA->volverAFila();
                cartaActivaIA->establecerEnCombate(false);
            }
            cartaActivaIA = nuevaActivaIA;
            if (cartaActivaIA) {
                cartaActivaIA->setZValue(5);
                cartaActivaIA->moverA(posIACentro);
                cartaActivaIA->establecerEnCombate(true);
            }
        }

        if (cartaActivaJugador && cartaActivaJugador->estaDerrotada() && !retrasarSalidaCartaJugador) {
            cartaActivaJugador->volverAFila();
            cartaActivaJugador->establecerEnCombate(false);
            cartaActivaJugador = nullptr;
        }
        if (cartaActivaIA && cartaActivaIA->estaDerrotada()) {
            cartaActivaIA->volverAFila();
            cartaActivaIA->establecerEnCombate(false);
            cartaActivaIA = nullptr;
        }

        QRectF vsRect = lblVS->boundingRect();
        lblVS->setPos(centro.x() - vsRect.width() / 2.0,
                      centro.y() + CartaGraphicsItem::ALTO / 2.0 - vsRect.height() / 2.0);
        lblVS->setVisible(!juego->termino());

    } else {
        lblVS->setVisible(false);
    }

    bool mostrarBoton = !juego->termino() && juego->hayElementosSeleccionados()
                        && !juego->jugadorDebeCambiar();
    proxyBtnAtacar->setVisible(mostrarBoton);

    if (juego->termino()) {
        mostrarFinDePartida();
    }
}

void MainWindow::mostrarFinDePartida()
{
    proxyBtnAtacar->setVisible(false);
    btnAtacarCircular->setEnabled(false);

    for (auto* carta : cartasJugador)
        carta->establecerSeleccionable(false);
    for (auto* carta : cartasIA)
        carta->establecerSeleccionable(false);

    bool gano = juego->ganoJugador();

    if (gano) {
        ui->textEdit->append("<b style='color:#2ecc71; font-size:16px;'>¡GANASTE LA PARTIDA!</b>");
        lblResultadoTitulo->setText("VICTORIA");
        lblResultadoTitulo->setStyleSheet("color: #2ecc71;");
        lblResultadoSubtitulo->setText("Ganaste la partida");
    } else {
        ui->textEdit->append("<b style='color:#e74c3c; font-size:16px;'>LA IA HA GANADO LA PARTIDA</b>");
        lblResultadoTitulo->setText("DERROTA");
        lblResultadoTitulo->setStyleSheet("color: #e74c3c;");
        lblResultadoSubtitulo->setText("La IA ganó la partida");
        lblImagenResultado->setPixmap(
            QPixmap(":/new/prefix1/Imagenes/Derrota.png")
                .scaled(110, 110, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    overlayResultado->setGeometry(ui->centralwidget->rect());
    overlayResultado->raise();
    overlayResultado->show();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    if (escena)
        ui->graphicsViewMesa->fitInView(escena->sceneRect(), Qt::KeepAspectRatio);
    if (overlayResultado)
        overlayResultado->setGeometry(ui->centralwidget->rect());
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    if (escena)
        ui->graphicsViewMesa->fitInView(escena->sceneRect(), Qt::KeepAspectRatio);
}
void MainWindow::mostrarDanioFlotante(int danio, QPointF posicion)
{
    auto* texto = new QGraphicsTextItem(QString("-%1").arg(danio));
    texto->setDefaultTextColor(QColor(0xe7, 0x4c, 0x3c));
    QFont f = texto->font();
    f.setPointSize(18);
    f.setBold(true);
    texto->setFont(f);
    texto->setPos(posicion);
    texto->setZValue(50);
    escena->addItem(texto);

    auto* animPos = new QPropertyAnimation(texto, "pos");
    animPos->setDuration(900);
    animPos->setStartValue(posicion);
    animPos->setEndValue(posicion - QPointF(0, 50));
    animPos->setEasingCurve(QEasingCurve::OutCubic);

    auto* animOpacidad = new QPropertyAnimation(texto, "opacity");
    animOpacidad->setDuration(900);
    animOpacidad->setStartValue(1.0);
    animOpacidad->setEndValue(0.0);

    auto* grupo = new QParallelAnimationGroup(this);
    grupo->addAnimation(animPos);
    grupo->addAnimation(animOpacidad);
    connect(grupo, &QParallelAnimationGroup::finished, texto, &QGraphicsTextItem::deleteLater);
    grupo->start(QAbstractAnimation::DeleteWhenStopped);
}