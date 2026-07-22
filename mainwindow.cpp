#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMainWindow>
#include "iaaleatoria.h"
#include "juego.h"
#include "jugadorhumano.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    jugador1 = new JugadorHumano();
    jugador2 = new IAAleatoria();

    juego = new Juego(jugador1, jugador2);

    mostrarSeleccionElementos();

    actualizarPantalla();
}

MainWindow::~MainWindow()
{
    delete juego;
    delete jugador1;
    delete jugador2;
    delete ui;
}

void MainWindow::seleccionarElemento(int indice)
{
    juego->seleccionarElemento(indice);

    juego->resolverTurno();

    actualizarPantalla();

    if (juego->termino())
    {
        if (juego->ganoJugador())
        {
            ui->lblEstado->setText("¡GANASTE!");
        }
        else
        {
            ui->lblEstado->setText("¡LA IA HA GANADO!");
        }

        ui->btnAtacar->setEnabled(false);
        ui->btnCambiar->setEnabled(false);

        return;
    }

    if (juego->jugadorDebeCambiar())
    {
        mostrarSeleccionElementos();
    }
    else
    {
        mostrarAcciones();
    }
}


void MainWindow::on_PBelemento1_clicked()
{
    seleccionarElemento(0);
}
void MainWindow::on_PBelemento2_clicked()
{
    seleccionarElemento(1);
}
void MainWindow::on_PBelemento3_clicked()
{
    seleccionarElemento(2);
}
void MainWindow::on_PBelemento4_clicked()
{
    seleccionarElemento(3);
}
void MainWindow::on_PBelemento5_clicked()
{
    seleccionarElemento(4);
}
void MainWindow::on_btnAtacar_clicked()
{
    juego->resolverTurno();

    actualizarPantalla();

    if (juego->termino())
    {
        if (juego->ganoJugador())
        {
            ui->lblEstado->setText("¡GANASTE!");
        }
        else
        {
            ui->lblEstado->setText("¡LA IA HA GANADO!");
        }

        ui->btnAtacar->setEnabled(false);
        ui->btnCambiar->setEnabled(false);

        return;
    }

    if (juego->jugadorDebeCambiar())
    {
        mostrarSeleccionElementos();
    }
    else
    {
        mostrarAcciones();
    }
}
void MainWindow::on_btnCambiar_clicked()
{
    juego->cancelarSeleccion();

    actualizarPantalla();

    mostrarSeleccionElementos();
}

void MainWindow::mostrarSeleccionElementos()
{
    QPushButton* botonesJugador[5] =
        {
            ui->PBelemento1,
            ui->PBelemento2,
            ui->PBelemento3,
            ui->PBelemento4,
            ui->PBelemento5
        };

    for (int i = 0; i < 5; i++)
    {
        botonesJugador[i]->setVisible(true);
    }

    ui->btnAtacar->setVisible(false);
    ui->btnCambiar->setVisible(false);
}
void MainWindow::mostrarAcciones()
{
    QPushButton* botonesJugador[5] =
        {
            ui->PBelemento1,
            ui->PBelemento2,
            ui->PBelemento3,
            ui->PBelemento4,
            ui->PBelemento5
        };

    for (int i = 0; i < 5; i++)
    {
        botonesJugador[i]->setVisible(false);
    }

    ui->btnAtacar->setVisible(true);
    ui->btnCambiar->setVisible(true);
}
void MainWindow::actualizarPantalla()
{
    QPushButton* botonesJugador[5] =
        {
            ui->PBelemento1,
            ui->PBelemento2,
            ui->PBelemento3,
            ui->PBelemento4,
            ui->PBelemento5
        };
    QLabel* vidasJugador[5] =
        {
            ui->lbleleJHVida1,
            ui->lbleleJHVida2,
            ui->lbleleJHVida3,
            ui->lbleleJHVida4,
            ui->lbleleJHVida5
        };
    QLabel* vidasIA[5] =
        {
            ui->lbleleIAVida1,
            ui->lbleleIAVida2,
            ui->lbleleIAVida3,
            ui->lbleleIAVida4,
            ui->lbleleIAVida5
        };

    const vector<Elemento>& elementosJH = jugador1->getElementos();
    const vector<Elemento>& elementosIA = jugador2->getElementos();


    for (int i = 0; i < 5; i++)
    {
        botonesJugador[i]->setText(elementosJH[i].obtenerNombre());

        botonesJugador[i]->setEnabled(elementosJH[i].estaVivo());

        vidasJugador[i]->setText(
            elementosJH[i].obtenerNombre()
            + ": "
            + QString::number(elementosJH[i].obtenerVida())
            + "%");

        vidasIA[i]->setText(
            elementosIA[i].obtenerNombre()
            + ": "
            + QString::number(elementosIA[i].obtenerVida())
            + "%");
    }


    ui->lblTurno->setText("TURNO ACTUAL: JUGADOR");
    ui->lblEstado->setText(juego->getMensajeEstado());


    if (juego->hayElementosSeleccionados())
    {
        ui->lblEnfrentamiento->setText("ENFRENTAMIENTO: " + juego->getElementoActivoJugador()->obtenerNombre() + " VS " + juego->getElementoActivoIA()->obtenerNombre());
    }
    else
    {
        ui->lblEnfrentamiento->setText(
            "ENFRENTAMIENTO: ----------- VS -----------");
    }

}
