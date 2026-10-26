#include "menuprincipal.h"
#include "ui_menuprincipal.h"
#include "gestorpartidas.h"

#include <QApplication>

MenuPrincipal::MenuPrincipal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuPrincipal)
{
    ui->setupUi(this);

    overlayMenu = new QWidget(this);

    overlayMenu->setGeometry(rect());

    overlayMenu->setStyleSheet(
        "background-color: rgba(0,0,0,160);");

    overlayMenu->hide();

    this->setAutoFillBackground(false);
    setAttribute(
        Qt::WA_StyledBackground,
        true);
    this->setObjectName("MenuPrincipal");
    this->setStyleSheet(
        "#MenuPrincipal {"
        "border-image: url(:/new/prefix1/Imagenes/MENU/FondoMENUajustado.png) 0 0 0 0 stretch stretch;"
        "}");

    ui->frmNuevaPartida->hide();

    ui->frmNuevaPartida->setAutoFillBackground(false);

    ui->frmNuevaPartida->setAttribute(
        Qt::WA_StyledBackground,
        true);

    ui->frmNuevaPartida->setStyleSheet(
        "#frmNuevaPartida {"
        "border-image:url(:/new/prefix1/Imagenes/MENU/Vent_NuevaPartida.png);"
        "}");

    ui->lblNombreJugador->setStyleSheet(
        "QLabel {"
        "background: transparent;"
        "color: rgb(230,210,140);"
        "font-size: 16px;"
        "font-weight: bold;"
        "}");

    ui->lblTipodeIA->setStyleSheet(
        "QLabel {"
        "background: transparent;"
        "color: rgb(230,210,140);"
        "font-size: 16px;"
        "font-weight: bold;"
        "}");

    ui->txtNombreJugador->setPlaceholderText(
        "Ingrese su nombre...");

    ui->txtNombreJugador->setStyleSheet(
        "QLineEdit {"
        "background-color: rgba(15,25,45,220);"
        "color: white;"
        "border: 2px solid rgb(180,140,60);"
        "border-radius: 8px;"
        "padding: 6px;"
        "font-size: 14px;"
        "}");

    ui->cmbTipoIA->setStyleSheet(
        "QComboBox {"
        "background-color: rgba(15,25,45,220);"
        "color: white;"
        "border: 2px solid rgb(180,140,60);"
        "border-radius: 8px;"
        "padding: 6px;"
        "font-size: 14px;"
        "}"
        "QComboBox QAbstractItemView {"
        "background-color: rgb(20,30,50);"
        "color: white;"
        "selection-background-color: rgb(50,90,180);"
        "}");

    ui->lblAvisoNombre->setStyleSheet(
        "QLabel {"
        "background: transparent;"
        "color: rgb(255,120,120);"
        "font-weight: bold;"
        "}");

    ui->btnVolver->setText("");

    ui->btnVolver->setFixedSize(
        120,
        100);

    ui->btnVolver->setStyleSheet(
        "QPushButton {"
        "border:none;"
        "background:transparent;"
        "image:url(:/new/prefix1/Imagenes/MENU/Volver_Normal.png);"
        "}"
        "QPushButton:hover {"
        "image:url(:/new/prefix1/Imagenes/MENU/Volver_Hover.png);"
        "}");

    ui->btnCrearPartida->setText("");

    ui->btnCrearPartida->setFixedSize(
        260,
        100);

    ui->btnCrearPartida->setStyleSheet(
        "QPushButton {"
        "border:none;"
        "background:transparent;"
        "image:url(:/new/prefix1/Imagenes/MENU/CrearPartida_Normal.png);"
        "}"
        "QPushButton:hover {"
        "image:url(:/new/prefix1/Imagenes/MENU/CrearPartida_Hover.png);"
        "}");

    ui->btnVolver->setCursor(
        Qt::PointingHandCursor);

    ui->btnCrearPartida->setCursor(
        Qt::PointingHandCursor);

    ui->frmCargarPartida->hide();

    ui->frmCargarPartida->setAutoFillBackground(false);

    ui->frmCargarPartida->setAttribute(
        Qt::WA_StyledBackground,
        true);

    ui->frmCargarPartida->setStyleSheet(
        "#frmCargarPartida {"
        "border-image:url(:/new/prefix1/Imagenes/MENU/Vent_CargarPartida.png);"
        "}");

    ui->lblPartidasGuardadas->setStyleSheet(
        "QLabel {"
        "background: transparent;"
        "color: rgb(230,210,140);"
        "font-size: 20px;"
        "font-weight: bold;"
        "}");


    QString estiloSlot =R"(
    QPushButton {
    border-image:url(:/new/prefix1/Imagenes/MENU/Slot_Normal.png);
    color: rgb(235,220,170);
    font-size: 12px;
    font-weight: bold;
    text-align: left;
    padding-left: 85px;
    padding-top: -3px;
    }
    QPushButton:hover {
    border-image:url(:/new/prefix1/Imagenes/MENU/Slot_Hover.png);
    }
    QPushButton:disabled {
    border-image:url(:/new/prefix1/Imagenes/MENU/Slot_Pressed.png);
    color: rgb(180,180,180);
    } )";

    ui->btnSlot1->setStyleSheet(estiloSlot);
    ui->btnSlot2->setStyleSheet(estiloSlot);
    ui->btnSlot3->setStyleSheet(estiloSlot);
    ui->btnSlot4->setStyleSheet(estiloSlot);
    ui->btnSlot5->setStyleSheet(estiloSlot);

    ui->btnSlot1->setMinimumHeight(120);
    ui->btnSlot2->setMinimumHeight(120);
    ui->btnSlot3->setMinimumHeight(120);
    ui->btnSlot4->setMinimumHeight(120);
    ui->btnSlot5->setMinimumHeight(120);

    ui->btnVolver_3->setText("");

    ui->btnVolver_3->setFixedSize(
        120,
        90);

    ui->btnVolver_3->setCursor(
        Qt::PointingHandCursor);

    ui->btnVolver_3->setStyleSheet(
        "QPushButton {"
        "border:none;"
        "background:transparent;"
        "image:url(:/new/prefix1/Imagenes/MENU/Volver_Normal.png);"
        "}"
        "QPushButton:hover {"
        "image:url(:/new/prefix1/Imagenes/MENU/Volver_Hover.png);"
        "}");

    ui->frmOpciones->hide();

    ui->frmOpciones->setAutoFillBackground(false);

    ui->frmOpciones->setAttribute(
        Qt::WA_StyledBackground,
        true);

    ui->frmOpciones->setStyleSheet(
        "#frmOpciones {"
        "border-image:url(:/new/prefix1/Imagenes/MENU/Vent_Opciones.png);"
        "}");

    ui->lblOpciones->setText(" ");

    ui->btnVolver_2->setText("");

    ui->btnVolver_2->setFixedSize(
        150,
        110);

    ui->btnVolver_2->setCursor(
        Qt::PointingHandCursor);

    ui->btnVolver_2->setStyleSheet(
        "QPushButton {"
        "border:none;"
        "background:transparent;"
        "image:url(:/new/prefix1/Imagenes/MENU/Volver_Normal.png);"
        "}"
        "QPushButton:hover {"
        "image:url(:/new/prefix1/Imagenes/MENU/Volver_Hover.png);"
        "}");

    QString estiloLabelOpciones =
        "QLabel {"
        "background: transparent;"
        "color: rgb(235,220,170);"
        "font-size: 16px;"
        "font-weight: bold;"
        "}";

    ui->lblMusica->setStyleSheet(
        estiloLabelOpciones);

    ui->lblSonido->setStyleSheet(
        estiloLabelOpciones);

    ui->hsSonidoEfectos->setStyleSheet(
        "QSlider::groove:horizontal {"
        "height: 8px;"
        "background: rgb(20,30,50);"
        "border-radius: 4px;"
        "}"
        "QSlider::handle:horizontal {"
        "background: rgb(235,220,170);"
        "width: 18px;"
        "margin: -6px 0;"
        "border-radius: 9px;"
        "}");

    ui->hsSonidoMusica->setStyleSheet(
        ui->hsSonidoEfectos->styleSheet());

    ui->lblAvisoNombre->hide();
    ui->lblPartidasGuardadas->setText(" ");

    ventanaJuego = nullptr;

    ui->btnNuevaPartida->setText("");
    ui->btnNuevaPartida->setFixedSize(420,120);

    ui->btnNuevaPartida->setStyleSheet(
        "QPushButton {"
        "border:none;"
        "background:transparent;"
        "image:url(:/new/prefix1/Imagenes/MENU/NuevaPartida_Normal.png);"
        "}"
        "QPushButton:hover {"
        "image:url(:/new/prefix1/Imagenes/MENU/NuevaPartida_Hover.png);"
        "}");

    ui->btnCargarPartida->setText("");
    ui->btnCargarPartida->setFixedSize(420,120);

    ui->btnCargarPartida->setStyleSheet(
        "QPushButton {"
        "border:none;"
        "background:transparent;"
        "image:url(:/new/prefix1/Imagenes/MENU/CargarPartida_Normal.png);"
        "}"
        "QPushButton:hover {"
        "image:url(:/new/prefix1/Imagenes/MENU/CargarPartida_Hover.png);"
        "}");

    ui->btnOpciones->setText("");
    ui->btnOpciones->setFixedSize(420,120);

    ui->btnOpciones->setStyleSheet(
        "QPushButton {"
        "border:none;"
        "background:transparent;"
        "image:url(:/new/prefix1/Imagenes/MENU/Opciones_Normal.png);"
        "}"
        "QPushButton:hover {"
        "image:url(:/new/prefix1/Imagenes/MENU/Opciones_Hover.png);"
        "}");

    ui->btnSalir->setText("");
    ui->btnSalir->setFixedSize(420,120);

    ui->btnSalir->setStyleSheet(
        "QPushButton {"
        "border:none;"
        "background:transparent;"
        "image:url(:/new/prefix1/Imagenes/MENU/Salir_Normal.png);"
        "}"
        "QPushButton:hover {"
        "image:url(:/new/prefix1/Imagenes/MENU/Salir_Hover.png);"
        "}");

    ui->btnNuevaPartida->setCursor(
        Qt::PointingHandCursor);

    ui->btnCargarPartida->setCursor(
        Qt::PointingHandCursor);

    ui->btnOpciones->setCursor(
        Qt::PointingHandCursor);

    ui->btnSalir->setCursor(
        Qt::PointingHandCursor);

    ui->lblTitulo->setText("");

    QPixmap titulo(
        ":/new/prefix1/Imagenes/MENU/Elemental/TituloMENU.png");

    ui->lblTitulo->setPixmap(
        titulo.scaled(
            1100,
            350,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation));
    ui->lblTitulo->setAlignment(
        Qt::AlignCenter);
}

MenuPrincipal::~MenuPrincipal()
{
    delete ui;
}

void MenuPrincipal::on_btnSalir_clicked()
{
    QApplication::quit();
}

void MenuPrincipal::on_btnNuevaPartida_clicked()
{
    overlayMenu->show();
    overlayMenu->raise();

    ui->frmNuevaPartida->show();
    ui->frmNuevaPartida->raise();

    ui->frmNuevaPartida->show();

    habilitarMenuPrincipal(
        false);
}

void MenuPrincipal::on_btnCargarPartida_clicked()
{
    actualizarSlots();

    overlayMenu->show();
    overlayMenu->raise();

    ui->frmCargarPartida->show();
    ui->frmCargarPartida->raise();

    ui->frmCargarPartida->show();

    habilitarMenuPrincipal(false);
}

void MenuPrincipal::on_btnOpciones_clicked()
{
    overlayMenu->show();
    overlayMenu->raise();

    ui->frmOpciones->show();
    ui->frmOpciones->raise();

    ui->frmOpciones->show();

    habilitarMenuPrincipal(
        false);
}

void MenuPrincipal::on_btnVolver_clicked()
{
    overlayMenu->hide();

    ui->frmNuevaPartida->hide();

    habilitarMenuPrincipal(
        true);
}

void MenuPrincipal::on_btnVolver_2_clicked()
{
    overlayMenu->hide();

    ui->frmOpciones->hide();

    habilitarMenuPrincipal(
        true);
}

void MenuPrincipal::on_btnVolver_3_clicked()
{
    overlayMenu->hide();

    ui->frmCargarPartida->hide();

    habilitarMenuPrincipal(
        true);
}

void MenuPrincipal::habilitarMenuPrincipal(
    bool habilitado)
{
    ui->btnNuevaPartida
        ->setEnabled(habilitado);

    ui->btnCargarPartida
        ->setEnabled(habilitado);

    ui->btnOpciones
        ->setEnabled(habilitado);

    ui->btnSalir
        ->setEnabled(habilitado);
}

void MenuPrincipal::actualizarSlots()
{
    GestorPartidas gestor;

    for(int i = 1; i <= 5; i++)
    {
        QPushButton* boton = nullptr;

        switch(i)
        {
        case 1:
            boton = ui->btnSlot1;
            break;

        case 2:
            boton = ui->btnSlot2;
            break;

        case 3:
            boton = ui->btnSlot3;
            break;

        case 4:
            boton = ui->btnSlot4;
            break;

        case 5:
            boton = ui->btnSlot5;
            break;
        }

        if(gestor.existeSlot(i))
        {
            EstadoPartida estado =
                gestor.cargarPartida(i);

            int kills =
                estado.getCantidadCartas()
                - estado.getCartasVivasIA();

            boton->setEnabled(true);

            boton->setText(
                "SLOT " + QString::number(i)
                + "\n"
                + "Jugador: "
                + QString::fromStdString(
                    estado.getNombreJugador())
                + "    IA: "
                + QString::fromStdString(
                    estado.getTipoIA())
                + "\n"
                + "Vivas: "
                + QString::number(
                    estado.getCartasVivasJugador())
                + "    Kills: "
                + QString::number(kills)
                + "    Vida: "
                + QString::number(
                    estado.getVidaTotalJugador()));
        }
        else
        {
            boton->setEnabled(false);

            boton->setText(
                "SLOT "
                + QString::number(i)
                + "\nVACIO");
        }
    }
}

void MenuPrincipal::on_btnCrearPartida_clicked()
{
    QString nombreJugador =
        ui->txtNombreJugador
            ->text()
            .trimmed();

    if(nombreJugador.isEmpty())
    {
        ui->lblAvisoNombre->setText(
            "Ingrese un nombre de jugador");

        ui->lblAvisoNombre->show();

        return;
    }

    QString tipoIA =
        ui->cmbTipoIA
            ->currentText();

    ventanaJuego =
        new MainWindow(
            nombreJugador,
            tipoIA);

    GestorPartidas gestor;

    gestor.guardarEstadoTemporal(
        ventanaJuego->crearEstadoParaReintento());

    ui->lblAvisoNombre->hide();

    ventanaJuego->show();

    this->hide();
}

void MenuPrincipal::cargarSlot(
    int numeroSlot)
{
    GestorPartidas gestor;

    EstadoPartida estado =
        gestor.cargarPartida(
            numeroSlot);

    EstadoPartida reinicio;

    reinicio.setNombreJugador(
        estado.getNombreJugador());

    reinicio.setTipoIA(
        estado.getTipoIA());

    reinicio.setCantidadCartas(
        estado.getCantidadCartas());

    for(const DatosCarta& carta :
         estado.getCartasJugador())
    {
        DatosCarta nueva =
            carta;

        nueva.vida = 100;

        reinicio.agregarCartaJugador(
            nueva);
    }

    for(const DatosCarta& carta :
         estado.getCartasIA())
    {
        DatosCarta nueva =
            carta;

        nueva.vida = 100;

        reinicio.agregarCartaIA(
            nueva);
    }

    reinicio.setCartaActivaJugador(
        "NINGUNO");

    reinicio.setCartaActivaIA(
        "NINGUNO");

    reinicio.setNombreJugador(
        estado.getNombreJugador());

    gestor.guardarEstadoTemporal(
        reinicio);

    ventanaJuego =
        new MainWindow(
            estado);

    ventanaJuego->show();

    this->hide();
}

void MenuPrincipal::on_btnSlot1_clicked()
{
    cargarSlot(1);
}

void MenuPrincipal::on_btnSlot2_clicked()
{
    cargarSlot(2);
}

void MenuPrincipal::on_btnSlot3_clicked()
{
    cargarSlot(3);
}

void MenuPrincipal::on_btnSlot4_clicked()
{
    cargarSlot(4);
}

void MenuPrincipal::on_btnSlot5_clicked()
{
    cargarSlot(5);
}

