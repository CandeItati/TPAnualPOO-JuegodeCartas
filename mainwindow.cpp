#include "mainwindow.h"
#include "gestorpartidas.h"
#include "./ui_mainwindow.h"

#include "iaaleatoria.h"
#include "iaestrategica.h"
#include "superia.h"
#include "jugadorhumano.h"
#include "resultadoataque.h"
#include "resultadoronda.h"
#include "lectorconfiguracion.h"
#include "menuprincipal.h"

#include <QGraphicsTextItem>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDir>
#include <QCoreApplication>
#include <QFile>
#include <QInputDialog>
#include <QMessageBox>


//Constructor
// Inicializa la ventana principal, crea a los jugadores y el motor del juego.
MainWindow::MainWindow(
    const QString& nombreJugador,
    const QString& tipoIA,
    QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lblCombate->setStyleSheet(
        "QLabel {"
        "background: transparent;"
        "color: rgb(235,220,170);"
        "font-size: 18px;"
        "font-weight: bold;"
        "}");

    ui->lblCombate->setAlignment(
        Qt::AlignCenter);

    ui->textEdit->setStyleSheet(
        "QTextEdit {"
        "background-color: rgb(18,25,40);"
        "color: rgb(235,220,170);"
        "border: 2px solid rgb(180,140,60);"
        "font-size: 14px;"
        "font-weight: bold;"
        "padding: 6px;"
        "}");

    jugador1 = new JugadorHumano();

    jugador1->setNombre(
        nombreJugador.toStdString());

    configuracion = new Configuracion();

    QString rutaConfig =QDir::cleanPath(QCoreApplication::applicationDirPath()+ "/../../config.txt");

    LectorConfiguracion lector;

    lector.cargarArchivo(rutaConfig,*configuracion);

    QString tipoIAFinal =
        tipoIA;

    bool fueSorteo =
        false;

    if(tipoIA == "SORTEO")
    {
        fueSorteo = true;

        int valor =
            rand() % 3;

        if(valor == 0)
        {
            tipoIAFinal =
                "ALEATORIA";
        }
        else if(valor == 1)
        {
            tipoIAFinal =
                "ESTRATEGICA";
        }
        else
        {
            tipoIAFinal =
                "SUPER";
        }
    }

    configuracion->setTipoIA(
        tipoIAFinal.toStdString());

    if(tipoIAFinal == "ALEATORIA")
    {
        jugador2 = new IAAleatoria();
    }
    else if(tipoIAFinal == "ESTRATEGICA")
    {
        jugador2 = new IAEstrategica();
    }
    else if(tipoIAFinal == "SUPER")
    {
        jugador2 = new SuperIA();
    }
    else
    {
        jugador2 = new IAAleatoria();
    }

    ContrincanteIA* ia =
        dynamic_cast<ContrincanteIA*>(
            jugador2);

    if(ia)
    {
        ia->setConfiguracion(
            configuracion);
    }

    juego = new Juego(jugador1, jugador2, configuracion);


    iniciarEscena();
    crearOverlayResultado();
    actualizarPantalla();

    if(fueSorteo)
    {
        ui->textEdit->append(
            QString(
                "🎲 La IA sorteada fue: %1")
                .arg(tipoIAFinal));
    }

    ui->textEdit->append(
        " ¡Comienza la partida! Elegí tu primera carta ");

    ui->btnGuardarPartida->setText("");

    ui->btnGuardarPartida->setFixedSize(
        300,
        70);

    ui->btnGuardarPartida->setStyleSheet(
        "QPushButton {"
        "border:none;"
        "background-color: transparent;"
        "image: url(:/new/prefix1/Imagenes/Guardar_Partida_NORMAL.png);"
        "}"

        "QPushButton:hover {"
        "image: url(:/new/prefix1/Imagenes/Guardar_Partida_HOVER.png);"
        "}");

    ui->btnVolverMenu->setText("");

    ui->btnVolverMenu->setFixedSize(
        300,
        70);

    ui->btnVolverMenu->setStyleSheet(
        "QPushButton {"
        "border:none;"
        "background-color: transparent;"
        "image: url(:/new/prefix1/Imagenes/VolverMenu_Normal.png);"
        "}"

        "QPushButton:hover {"
        "image: url(:/new/prefix1/Imagenes/VolverMenu_Hover.png);"
        "}");
}

MainWindow::MainWindow(
    const EstadoPartida& estado,
    QWidget *parent)
    : MainWindow(
          QString::fromStdString(
              estado.getNombreJugador()),
          QString::fromStdString(
              estado.getTipoIA()),
          parent)
{
    juego->cargarDesdeEstado(
        estado);

    for(auto* carta : cartasJugador)
    {
        escena->removeItem(carta);
        delete carta;
    }

    for(auto* carta : cartasIA)
    {
        escena->removeItem(carta);
        delete carta;
    }

    cartasJugador.clear();
    cartasIA.clear();

    colocarManoJugador();
    colocarManoIA();

    cartaActivaJugador = nullptr;
    cartaActivaIA = nullptr;

    actualizarPantalla();
}

//Destructor
MainWindow::~MainWindow()
{
    delete juego;
    delete configuracion;
    delete jugador1;
    delete jugador2;
    delete ui;
}

EstadoPartida
MainWindow::crearEstadoParaReintento() const
{
    return juego->crearEstadoPartida();
}

// Busca en qué posición del vector está el Elemento apuntado por 'buscado'.
int MainWindow::indiceDeElemento(const std::vector<Elemento>& elementos, Elemento* buscado)
{
    for (size_t i = 0; i < elementos.size(); i++) {
        if (&elementos[i] == buscado) return (int)i;
    }
    return -1;
}

//Crea escena donde estaran las cartas y configura el fondo.
void MainWindow::iniciarEscena()
{
    //Crea escena.
    escena = new QGraphicsScene(this);
    //Le asigno tamanio.
    escena->setSceneRect(0, 0, anchoEscena, alturaEscena);

    //Carga imagen de fondo (el tablero).
    QPixmap fondo(":/new/prefix1/Imagenes/Tablero_SinC.png");
    QGraphicsPixmapItem* fondoItem = new QGraphicsPixmapItem(
        fondo.scaled(anchoEscena, alturaEscena, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    fondoItem->setZValue(-100);
    escena->addItem(fondoItem);

    ui->graphicsViewMesa->setScene(escena);
    ui->graphicsViewMesa->setRenderHint(QPainter::Antialiasing);

    //Dibuja y coloca cartas para ambos jugadores.
    colocarManoJugador();
    colocarManoIA();

    //Crea boton de ataque.
    btnAtacarCircular = new QPushButton();
    btnAtacarCircular->setFixedSize(200, 120);
    btnAtacarCircular->setStyleSheet(
        "QPushButton {"
        "border:none;"
        "background-color: transparent;"
        "image: url(:/new/prefix1/Imagenes/Atacar_Normal.png);"
        "}"

        "QPushButton:hover {"
        "image: url(:/new/prefix1/Imagenes/Atacar_Hover.png);"
        "}"

        "QPushButton:disabled {"
        "image: url(:/new/prefix1/Imagenes/Atacar_Pressed.png);"
        "}");
    proxyBtnAtacar = escena->addWidget(btnAtacarCircular);
    proxyBtnAtacar->setPos(anchoEscena / 2.0 + CartaGraphicsItem::ANCHO + 60,alturaEscena / 2.0 - CartaGraphicsItem::ALTO / 2.0 + 35);
    proxyBtnAtacar->setVisible(true);

    //Permite interactuar con el boton.
    connect(btnAtacarCircular, &QPushButton::clicked, this, &MainWindow::onBtnAtacarClicked);

    // Texto "VS" en el medio, entre las dos cartas que se enfrentan.
    lblVS = new QGraphicsTextItem("VS");
    QFont fuenteVS("Arial", 22, QFont::Black);
    lblVS->setFont(fuenteVS);
    lblVS->setDefaultTextColor(QColor(0xf1, 0xc4, 0x0f));
    lblVS->setZValue(4);
    lblVS->setPos(anchoEscena / 2.0 - 25, alturaEscena / 2.0 - CartaGraphicsItem::ALTO / 2.0 + 65);
    lblVS->setVisible(false);
    escena->addItem(lblVS);
}

//Crea mensaje de resultado de partida.
void MainWindow::crearOverlayResultado()
{
    //Se crean las etiquetas para victoria y derrota.
    overlayResultado = new QWidget(ui->centralwidget);
    overlayResultado->setObjectName("overlayResultado");
    overlayResultado->setStyleSheet(
        "QWidget#overlayResultado { background-color: rgba(0, 0, 0, 170); }");
    overlayResultado->setGeometry(ui->centralwidget->rect());
    overlayResultado->hide();

    auto* panel = new QWidget(overlayResultado);
    lblFondoResultado =
        new QLabel(panel);
    lblFondoResultado->setStyleSheet(
        "background: transparent;");
    lblFondoResultado->setAlignment(
        Qt::AlignCenter);
    panel->setObjectName("panelResultado");
    panel->setFixedSize(900, 600);
    panel->setStyleSheet(
        "QWidget#panelResultado {"
        "background-color: transparent;"
        "border: none;"
        "}");

    lblTituloResultado = new QLabel(panel);
    lblTituloResultado->setStyleSheet(
        "background: transparent;");
    lblTituloResultado->setAlignment(Qt::AlignCenter);
    lblResultadoSubtitulo = new QLabel(panel);
    lblResultadoSubtitulo->setAlignment(Qt::AlignCenter);
    lblResultadoSubtitulo->setFont(QFont("Arial", 14));
    lblResultadoSubtitulo->setStyleSheet(
        "background: transparent;"
        "color: white;"
        "font-size: 22px;"
        "font-weight: bold;");

    btnResultadoPrincipal =
        new QPushButton(panel);

    btnResultadoSecundario =
        new QPushButton(panel);

    btnResultadoPrincipal->setFixedSize(
        350,
        160);

    btnResultadoSecundario->setFixedSize(
        350,
        160);

    connect(
        btnResultadoPrincipal,
        &QPushButton::clicked,
        this,
        &MainWindow::onResultadoPrincipal);

    connect(
        btnResultadoSecundario,
        &QPushButton::clicked,
        this,
        &MainWindow::onResultadoSecundario);

    /*
    //Organiza capas del mensaje final.
    auto* layout = new QVBoxLayout(panel);
    layout->addWidget(
        lblFondoResultado);
    layout->addStretch();
    layout->addSpacing(12);
    ///layout->addWidget(lblTituloResultado);
    ///layout->addWidget(lblResultadoSubtitulo);

    auto* layoutBotones = new QHBoxLayout();
    layoutBotones->addWidget(btnResultadoPrincipal);
    layoutBotones->addWidget(btnResultadoSecundario);
    layout->addLayout(layoutBotones);
    btnResultadoPrincipal->setStyleSheet("QPushButton {"" background-color: #f1c40f;"" color: #1c1f2e;"" border-radius: 6px;"
        " font-weight: bold;""}""QPushButton:hover {"" background-color: #f7dc6f;""}");

    btnResultadoSecundario->setStyleSheet(btnResultadoPrincipal->styleSheet());

    layout->addStretch();

    */

    lblFondoResultado->setGeometry(
        0,
        0,
        900,
        600);

    lblTituloResultado->setGeometry(
        50,
        0,
        800,
        350);

    lblResultadoSubtitulo->setGeometry(
        200,
        310,
        500,
        140);

    btnResultadoPrincipal->setGeometry(
        100,
        460,
        150,
        40);

    btnResultadoSecundario->setGeometry(
        450,
        460,
        150,
        40);


    auto* layoutOverlay = new QVBoxLayout(overlayResultado);
    layoutOverlay->addWidget(panel, 0, Qt::AlignCenter);
}

//Crea las representaciones graficas de las cartas del jugador, que se colocan en la parte inferior.
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

//Crea las representaciones graficas de las cartas de la ia, que se colocan en la parte superior.
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

//Cuando se clickea una carta esta funcion la busca y manda un mensaje confirmando la eleccion en el apartado de 'combates'.
void MainWindow::onCartaJugadorClickeada(CartaGraphicsItem* carta)
{

    if (juego->termino()) return;

    int indice = -1;
    for (size_t i = 0; i < cartasJugador.size(); i++) {
        if (cartasJugador[i] == carta) { indice = (int)i; break; }
    }
    if (indice == -1) return;

    juego->seleccionarElemento(indice);
    ui->textEdit->append(QString("<span style='color:#4db8ff;'>➤ Elegiste: <b>%1</b></span>").arg(jugador1->getElementos()[indice].obtenerNombre()));

    actualizarPantalla();
}

//Si se hace click en el boton de atacar resuelve el turno y actualiza info en pantalla.
void MainWindow::onBtnAtacarClicked()
{

    if (juego->termino()) return;

    btnAtacarCircular->setEnabled(false);

    Elemento* elemJugador = juego->getElementoActivoJugador();
    Elemento* elemIA = juego->getElementoActivoIA();
    int vidaJugadorAntes = elemJugador ? elemJugador->obtenerVida() : 0;
    int vidaIAAntes = elemIA ? elemIA->obtenerVida() : 0;

    juego->resolverTurno();

    ui->textEdit->append("<hr>");

    const ResultadoRonda& resultado =
        juego->getUltimoResultado();

    for (const ResultadoAtaque& ataque :
         resultado.getAtaques())
    {
        QString texto;

        texto += QString::fromStdString(
            ataque.atacante);

        texto += " ataco a ";

        texto += QString::fromStdString(
            ataque.defensor);

        texto += " (";

        texto += QString::number(
            ataque.danio);

        texto += " daño)";

        ui->textEdit->append(
            "<span style='color:#ffd780;'>⚔ "
            + texto +
            "</span>");
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

    QTimer::singleShot(
        700,
        this,
        [this]()
        {
            actualizarPantalla();
        });

    if (juego->iaNecesitaCambiarYAtacar()) {
        // La carta de la IA murió: le damos una pausa visual antes de que elija una nueva y ataque, para que se note con claridad que es OTRA carta la que está golpeando (y no la que acaba de morir).
        QTimer::singleShot(700, this, &MainWindow::resolverCambioDeCartaIA);
    }
}

//Resuelve el cambio de carta de la ia cuando esta pierde una carta en combate.
void MainWindow::resolverCambioDeCartaIA()
{
    Elemento* elemJugadorAntes = juego->getElementoActivoJugador();
    int vidaJugadorAntes = elemJugadorAntes ? elemJugadorAntes->obtenerVida() : 0;

    QPointF posJugadorAntes = cartaActivaJugador ? cartaActivaJugador->pos() : QPointF();
    bool teniaCartaJugador = (cartaActivaJugador != nullptr);

    juego->resolverCambioIA();

    QStringList lineas = QString::fromStdString(juego->getMensajeEstado()).split("\n");

    for (const QString& linea : std::as_const(lineas)) {
        if (!linea.trimmed().isEmpty())
            ui->textEdit->append("<span style='color:#ffae42;'>🔄 " + linea.toHtmlEscaped() + "</span>");
    }

    // Si la carta del jugador murió con este golpe, le pedimos a actualizarPantalla() que todavía NO la saque del centro: primero queremos que se vea el número de daño sobre ella, y recién después dejarla retirarse.
    retrasarSalidaCartaJugador = true;
    actualizarPantalla();

    QTimer::singleShot(380, this, [this, elemJugadorAntes, vidaJugadorAntes, posJugadorAntes, teniaCartaJugador]() {
        if (elemJugadorAntes) {
            int danio = vidaJugadorAntes - elemJugadorAntes->obtenerVida();
            if (danio > 0 && teniaCartaJugador)
                mostrarDanioFlotante(danio, posJugadorAntes + QPointF(CartaGraphicsItem::ANCHO / 2 - 15, 10));
        }

        // Un ratito más para que dé tiempo a leer el número antes de que la carta derrotada recién ahí se retire del centro.
        QTimer::singleShot(600, this, [this]() {
            retrasarSalidaCartaJugador = false;
            actualizarPantalla();
        });
    });
}

//Se llama constantemente para asegurar que los gráficos (cartas en pantalla, vidas, posiciones) reflejen exactamente lo que está pasando en la partida.
void MainWindow::actualizarPantalla()
{
    //Actualiza vida de las cartas.
    const std::vector<Elemento>& elementosJugador = jugador1->getElementos();
    const std::vector<Elemento>& elementosIA = jugador2->getElementos();

    for (size_t i = 0; i < cartasJugador.size(); i++)
        cartasJugador[i]->actualizarVida(elementosJugador[i].obtenerVida());
    for (size_t i = 0; i < cartasIA.size(); i++)
        cartasIA[i]->actualizarVida(elementosIA[i].obtenerVida());

    // Revisa si hay peleadores en el centro y busca cuáles son sus equivalentes gráficos.
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

        // Si hay un cambio en la carta elegida por el jugador: Primero devuelve a la mano la carta anterior (si había una y sigue viva).
        // Luego mueve la nueva carta al centro, la pone por delante de todo y la bloquea para que no se pueda clickear accidentalmente mientras pelea.
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

        //Devuelve las cartas eliminadas a la mano del jugador/ia.
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

    //Activa boton de atacar cuando ambos jugadores seleccionan sus cartas. Lo desactiva durante combates y cuando la partida finaliza.

    bool mostrarBoton =
        !juego->termino() &&
        juego->hayElementosSeleccionados() &&
        !juego->jugadorDebeCambiar();

    btnAtacarCircular->setEnabled(
        mostrarBoton);

    if (juego->termino()) {
        mostrarFinDePartida();
    }
}

//Muestra mensaje de victorio o derrota.
void MainWindow::mostrarFinDePartida()
{
    proxyBtnAtacar->setVisible(false);
    btnAtacarCircular->setEnabled(false);

    for (auto* carta : cartasJugador)
        carta->establecerSeleccionable(false);
    for (auto* carta : cartasIA)
        carta->establecerSeleccionable(false);

    bool gano = juego->ganoJugador();

    int cartasVivasJugador = 0;
    int vidaJugador = 0;

    for(const Elemento& e :
         juego->getJugador1()->getElementos())
    {
        if(e.estaVivo())
        {
            cartasVivasJugador++;
            vidaJugador += e.obtenerVida();
        }
    }

    int cartasVivasIA = 0;
    int vidaIA = 0;

    for(const Elemento& e :
         juego->getJugador2()->getElementos())
    {
        if(e.estaVivo())
        {
            cartasVivasIA++;
            vidaIA += e.obtenerVida();
        }
    }

    if (gano) {
        QPixmap fondo(
            ":/new/prefix1/Imagenes/Pantalla final/PantallaVictoria.png");

        lblFondoResultado->setPixmap(
            fondo.scaled(
                900,
                600,
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation));

        QPixmap titulo(
            ":/new/prefix1/Imagenes/Pantalla final/TituloVictoria.png");

        lblTituloResultado->setPixmap(
            titulo.scaled(
                800,
                350,
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation));

        lblResultadoSubtitulo->setText(
            QString(
                "IA derrotada: %1\n\n"
                "Cartas supervivientes: %2\n"
                "Vida restante: %3")
                .arg(
                    QString::fromStdString(
                        configuracion->getTipoIA()))
                .arg(cartasVivasJugador)
                .arg(vidaJugador));

        btnResultadoPrincipal->setStyleSheet(
            "QPushButton {"
            "border:none;"
            "background:transparent;"
            "image:url(:/new/prefix1/Imagenes/Pantalla final/NuevaPartida_Normal.png);"
            "}"
            "QPushButton:hover {"
            "image:url(:/new/prefix1/Imagenes/Pantalla final/NuevaPartida_Hover.png);"
            "}");

        btnResultadoPrincipal->setText(
            "");

        btnResultadoSecundario->setStyleSheet(
            "QPushButton {"
            "border:none;"
            "background:transparent;"
            "image:url(:/new/prefix1/Imagenes/Pantalla final/VolverMenu_NormalVictoria.png);"
            "}"
            "QPushButton:hover {"
            "image:url(:/new/prefix1/Imagenes/Pantalla final/VolverMenu_HoverVictoria.png);"
            "}");

        btnResultadoSecundario->setText(
            "");
    } else {
        QPixmap fondo(
            ":/new/prefix1/Imagenes/Pantalla final/PantallaDerrota.png");

        lblFondoResultado->setPixmap(
            fondo.scaled(
                900,
                600,
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation));


        QPixmap titulo(
            ":/new/prefix1/Imagenes/Pantalla final/TituloDerrota.png");

        lblTituloResultado->setPixmap(
            titulo.scaled(
                800,
                350,
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation));

        lblResultadoSubtitulo->setText(
            QString(
                "La IA %1 ha ganado.\n\n"
                "Cartas supervivientes IA: %2\n"
                "Vida restante IA: %3")
                .arg(
                    QString::fromStdString(
                        configuracion->getTipoIA()))
                .arg(cartasVivasIA)
                .arg(vidaIA));

        btnResultadoPrincipal->setStyleSheet(
            "QPushButton {"
            "border:none;"
            "background:transparent;"
            "image:url(:/new/prefix1/Imagenes/Pantalla final/Reintentar_Normal.png);"
            "}"
            "QPushButton:hover {"
            "image:url(:/new/prefix1/Imagenes/Pantalla final/Reintentar_Hover.png);"
            "}");

        btnResultadoPrincipal->setText(
            "");

        btnResultadoSecundario->setStyleSheet(
            "QPushButton {"
            "border:none;"
            "background:transparent;"
            "image:url(:/new/prefix1/Imagenes/Pantalla final/VolverMenu_NormalDerrota.png);"
            "}"
            "QPushButton:hover {"
            "image:url(:/new/prefix1/Imagenes/Pantalla final/VolverMenu_HoverDerrota.png);"
            "}");

        btnResultadoSecundario->setText(
            "");
        /*
        lblImagenResultado->setPixmap(
            QPixmap(":/new/prefix1/Imagenes/Derrota.png")
                .scaled(110, 110, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        */
    }

    overlayResultado->setGeometry(ui->centralwidget->rect());
    overlayResultado->raise();
    overlayResultado->show();
}

// Se ejecuta automáticamente cada vez que el usuario maximiza o cambia el tamaño de la ventana, para mantener la escala.
void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    if (escena)
        ui->graphicsViewMesa->fitInView(escena->sceneRect(), Qt::KeepAspectRatio);
    if (overlayResultado)
        overlayResultado->setGeometry(ui->centralwidget->rect());
}

//Ajusta la escena cuando comienza el juego.
void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    if (escena)
        ui->graphicsViewMesa->fitInView(escena->sceneRect(), Qt::KeepAspectRatio);
}

// Crea un texto temporal encima de la carta que acaba de recibir un ataque.
// Anima este texto para que suba lentamente mientras se vuelve transparente (efecto fantasma).
void MainWindow::mostrarDanioFlotante(int danio, QPointF posicion)
{
    //Configura texto.
    auto* texto = new QGraphicsTextItem(QString("-%1").arg(danio));
    texto->setDefaultTextColor(QColor(0xe7, 0x4c, 0x3c));
    QFont f = texto->font();
    f.setPointSize(18);
    f.setBold(true);
    texto->setFont(f);
    texto->setPos(posicion);
    texto->setZValue(50);
    escena->addItem(texto);

    //Animacion de movimiento.
    auto* animPos = new QPropertyAnimation(texto, "pos");
    animPos->setDuration(900);
    animPos->setStartValue(posicion);
    animPos->setEndValue(posicion - QPointF(0, 50));
    animPos->setEasingCurve(QEasingCurve::OutCubic);

    // Animación de Opacidad
    auto* animOpacidad = new QPropertyAnimation(texto, "opacity");
    animOpacidad->setDuration(900);
    animOpacidad->setStartValue(1.0);
    animOpacidad->setEndValue(0.0);

    //Ejecuta ambas animaciones al mismo tiempo.
    auto* grupo = new QParallelAnimationGroup(this);
    grupo->addAnimation(animPos);
    grupo->addAnimation(animOpacidad);
    connect(grupo, &QParallelAnimationGroup::finished, texto, &QGraphicsTextItem::deleteLater);
    grupo->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::on_btnGuardarPartida_clicked()
{
    bool ok;

    int slot =
        QInputDialog::getInt(
            this,
            "Guardar partida",
            "Seleccione un slot (1-5):",
            1,
            1,
            5,
            1,
            &ok);

    if(!ok)
    {
        return;
    }

    GestorPartidas gestor;

    if(gestor.existeSlot(slot))
    {
        QMessageBox mensaje(this);

        mensaje.setWindowTitle(
            "Sobrescribir partida");

        mensaje.setText(
            QString(
                "El Slot %1 ya contiene una partida.\n\n¿Desea sobrescribirla?")
                .arg(slot));

        mensaje.setStandardButtons(
            QMessageBox::Yes |
            QMessageBox::No);

        mensaje.setStyleSheet(
            "QMessageBox {"
            "background-color: rgb(12,18,30);"
            "}"
            "QLabel {"
            "color: rgb(235,220,170);"
            "font-size: 14px;"
            "font-weight: bold;"
            "}"
            "QPushButton {"
            "background-color: rgb(25,40,70);"
            "color: rgb(235,220,170);"
            "border: 1px solid rgb(180,140,60);"
            "padding: 6px;"
            "min-width: 80px;"
            "}");

        if(mensaje.exec() == QMessageBox::No)
        {
            return;
        }
    }

    gestor.guardarPartida(
        slot,
        juego);

    ui->textEdit->append(
        QString(
            "<b>💾 Partida guardada en Slot %1</b>")
            .arg(slot));
}

void MainWindow::on_btnVolverMenu_clicked()
{
    QMessageBox mensaje(this);

    mensaje.setWindowTitle(
        "Volver al menú");

    mensaje.setText(
        "Si sales sin guardar, el progreso se perderá.\n\n¿Deseas continuar?");

    mensaje.setStandardButtons(
        QMessageBox::Yes |
        QMessageBox::No);

    mensaje.setStyleSheet(
        "QMessageBox {"
        "background-color: rgb(12,18,30);"
        "}"
        "QLabel {"
        "color: rgb(235,220,170);"
        "font-size: 14px;"
        "font-weight: bold;"
        "}"
        "QPushButton {"
        "background-color: rgb(25,40,70);"
        "color: rgb(235,220,170);"
        "border: 1px solid rgb(180,140,60);"
        "padding: 6px;"
        "min-width: 80px;"
        "}");

    if(mensaje.exec() == QMessageBox::No)
    {
        return;
    }

    MenuPrincipal* menu =
        new MenuPrincipal();

    menu->show();

    close();
}

void MainWindow::onResultadoSecundario()
{
    MenuPrincipal* menu =
        new MenuPrincipal();

    menu->show();

    close();
}

void MainWindow::onResultadoPrincipal()
{
    MainWindow* nueva = nullptr;

    if(juego->ganoJugador())
    {
        nueva =
            new MainWindow(
                QString::fromStdString(
                    jugador1->getNombre()),
                QString::fromStdString(
                    configuracion->getTipoIA()));

        GestorPartidas gestor;

        gestor.guardarEstadoTemporal(
            nueva->crearEstadoParaReintento());
    }
    else
    {
        GestorPartidas gestor;

        EstadoPartida estado =
            gestor.cargarEstadoTemporal();

        nueva =
            new MainWindow(
                estado);
    }

    nueva->show();

    close();
}