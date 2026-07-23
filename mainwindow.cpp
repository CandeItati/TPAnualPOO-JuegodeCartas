#include "mainwindow.h"      // Definición de MainWindow.
#include "./ui_mainwindow.h" // Interfaz generada automáticamente por Qt.

#include <QMainWindow>

#include "iaaleatoria.h"   // IA utilizada.
#include "juego.h"         // Lógica del juego.
#include "jugadorhumano.h" // Jugador controlado por el usuario.

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)    // Llama al constructor de QMainWindow.
    , ui(new Ui::MainWindow) // Luego crea el objeto ui generado por Qt.
{
    ui->setupUi(this); // Construye toda la interfaz creada en Qt Designer.
                       // Sin esta línea la ventana aparecería vacía.

    jugador1 = new JugadorHumano(); // Crea el jugador humano.
    jugador2 = new IAAleatoria();   // Crea la inteligencia artificial.

    juego = new Juego(jugador1, jugador2); // Crea el juego y le pasa ambos jugadores.

    mostrarSeleccionElementos(); // Al comenzar solamente se muestran los botones para elegir un elemento.

    actualizarPantalla(); // Actualiza todos los textos y vidas.
}

MainWindow::~MainWindow() // Libera toda la memoria reservada con new.
{
    delete juego;
    delete jugador1;
    delete jugador2;
    delete ui;
}

void MainWindow::seleccionarElemento(int indice)
{
    juego->seleccionarElemento(indice); // Le avisa al juego qué elemento eligió el usuario.

    juego->resolverTurno(); // Ejecuta inmediatamente el turno.

    actualizarPantalla(); // Refresca toda la interfaz.

    if (juego->termino()) {                      // Si terminó la partida...
        if (juego->ganoJugador()) {              // Pregunta quién ganó.
            ui->lblEstado->setText("¡GANASTE!"); // Cambia el texto del Label.
        } else {
            ui->lblEstado->setText("¡LA IA HA GANADO!");
        }

        ui->btnAtacar->setEnabled(false);  // Desactiva el botón.
        ui->btnCambiar->setEnabled(false); // Desactiva el botón.

        return; // Sale de la función.
    }

    if (juego->jugadorDebeCambiar()) { // Si el elemento murió...
        mostrarSeleccionElementos();   // Permite elegir otro.
    } else {
        mostrarAcciones(); // Si sigue vivo muestra Atacar y Cambiar.
    }
}

void MainWindow::on_PBelemento1_clicked()
{
    seleccionarElemento(0); //Solo cambia el índice. Es decir de elemento.
}
void MainWindow::on_PBelemento2_clicked()
{
    seleccionarElemento(1); //Solo cambia el índice. Es decir de elemento.
}
void MainWindow::on_PBelemento3_clicked()
{
    seleccionarElemento(2); //Solo cambia el índice. Es decir de elemento.
}
void MainWindow::on_PBelemento4_clicked()
{
    seleccionarElemento(3); //Solo cambia el índice. Es decir de elemento.
}
void MainWindow::on_PBelemento5_clicked()
{
    seleccionarElemento(4); //Solo cambia el índice. Es decir de elemento.
}
void MainWindow::on_btnAtacar_clicked()
{
    juego->resolverTurno(); // Ejecuta un nuevo turno.

    actualizarPantalla();

    if (juego->termino()) { //repetimos lo anterior ahora luego de presionar el boton atacar.
        if (juego->ganoJugador()) {
            ui->lblEstado->setText("¡GANASTE!");
        } else {
            ui->lblEstado->setText("¡LA IA HA GANADO!");
        }

        ui->btnAtacar->setEnabled(false);
        ui->btnCambiar->setEnabled(false);

        return;
    }

    if (juego->jugadorDebeCambiar()) {
        mostrarSeleccionElementos();
    } else {
        mostrarAcciones();
    }
}
void MainWindow::on_btnCambiar_clicked()
{
    juego->cancelarSeleccion(); // Elimina la selección actual.

    actualizarPantalla();

    mostrarSeleccionElementos(); // Permite elegir otro elemento.
}

void MainWindow::mostrarSeleccionElementos()
{
    QPushButton *botonesJugador[5]
        = {ui->PBelemento1, // Arreglo de punteros a botones. (No los crea solo guarda sus direcciones)
           ui->PBelemento2,
           ui->PBelemento3,
           ui->PBelemento4,
           ui->PBelemento5};

    for (int i = 0; i < 5; i++) {
        botonesJugador[i]->setVisible(true); // Hace visibles los botones.
    }

    ui->btnAtacar->setVisible(false);  // Oculta Atacar.
    ui->btnCambiar->setVisible(false); // Oculta Cambiar.
}
void MainWindow::
    mostrarAcciones() //Hace exactamente lo mismo que antes pero lo contrario. Oculta los botones de elementos y muesta atacar y cambiar
{
    QPushButton *botonesJugador[5] = {ui->PBelemento1,
                                      ui->PBelemento2,
                                      ui->PBelemento3,
                                      ui->PBelemento4,
                                      ui->PBelemento5};

    for (int i = 0; i < 5; i++) {
        botonesJugador[i]->setVisible(false);
    }

    ui->btnAtacar->setVisible(true);
    ui->btnCambiar->setVisible(true);
}
void MainWindow::actualizarPantalla() //Actualiza toda la interfaz
{
    QPushButton *botonesJugador[5] = {ui->PBelemento1, //Guarda todos los botones
                                      ui->PBelemento2,
                                      ui->PBelemento3,
                                      ui->PBelemento4,
                                      ui->PBelemento5};
    QLabel *vidasJugador[5] = {ui->lbleleJHVida1, //Guarda los labels de vida del jugador.
                               ui->lbleleJHVida2,
                               ui->lbleleJHVida3,
                               ui->lbleleJHVida4,
                               ui->lbleleJHVida5};
    QLabel *vidasIA[5] = {ui->lbleleIAVida1, //Guarda los labels de vida de la IA.
                          ui->lbleleIAVida2,
                          ui->lbleleIAVida3,
                          ui->lbleleIAVida4,
                          ui->lbleleIAVida5};

    const vector<Elemento> &elementosJH
        = jugador1->getElementos(); //Obtiene el vector del jugador humano sin realizar una copia.
    const vector<Elemento> &elementosIA
        = jugador2->getElementos(); //Obtiene el vector del jugador IA sin realizar una copia.

    for (int i = 0; i < 5; i++) {                                   //Recorre los cinco elementos.
        botonesJugador[i]->setText(elementosJH[i].obtenerNombre()); //Pone el nombre en el botón.

        botonesJugador[i]->setEnabled(
            elementosJH[i].estaVivo()); //Si el elemento murió deshabilita el boton

        vidasJugador[i]->setText(elementosJH[i].obtenerNombre() + ": "
                                 + QString::number(elementosJH[i].obtenerVida())
                                 + "%"); //Muestra los elementos del Jugador humano con sus vidas

        vidasIA[i]->setText(elementosIA[i].obtenerNombre() + ": "
                            + QString::number(elementosIA[i].obtenerVida())
                            + "%"); //Muestra los elementos del Jugador IA con sus vidas
    }

    ui->lblTurno->setText("TURNO ACTUAL: JUGADOR");    //muestra el turno actual
    ui->lblEstado->setText(juego->getMensajeEstado()); //muestra los estados de la partida.

    if (juego->hayElementosSeleccionados()) { //Si ambos eligieron un elemento muestra cuales se estan enfrentando y si no elegieron muestra que no hay enfrentamiento
        ui->lblEnfrentamiento->setText("ENFRENTAMIENTO: "
                                       + juego->getElementoActivoJugador()->obtenerNombre() + " VS "
                                       + juego->getElementoActivoIA()->obtenerNombre());
    } else {
        ui->lblEnfrentamiento->setText("ENFRENTAMIENTO: ----------- VS -----------");
    }
}
