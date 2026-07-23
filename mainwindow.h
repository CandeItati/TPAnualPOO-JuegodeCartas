#ifndef MAINWINDOW_H          // Evita incluir este archivo más de una vez.
#define MAINWINDOW_H

#include <QMainWindow>        // Clase base de todas las ventanas de Qt.
#include "juego.h"            // Se utilizará un objeto Juego.

QT_BEGIN_NAMESPACE            // Macro de Qt.
namespace Ui {
class MainWindow;             // Declaración adelantada de la interfaz generada por Qt Designer.
}
QT_END_NAMESPACE

// MainWindow hereda de QMainWindow.
// Es la ventana principal de la aplicación.
class MainWindow : public QMainWindow
{
    Q_OBJECT                  // Macro obligatoria para utilizar señales y slots de Qt.

public:

    // Constructor.
    explicit MainWindow(QWidget *parent = nullptr);

    // Destructor.
    ~MainWindow() override;

private slots:                // Funciones que responden a eventos de la interfaz.

    // Se ejecutan cuando el usuario presiona uno de los botones
    // para elegir un elemento.
    void on_PBelemento1_clicked();
    void on_PBelemento2_clicked();
    void on_PBelemento3_clicked();
    void on_PBelemento4_clicked();
    void on_PBelemento5_clicked();

    // Se ejecuta cuando se presiona Atacar.
    void on_btnAtacar_clicked();

    // Se ejecuta cuando se presiona Cambiar.
    void on_btnCambiar_clicked();

private:

    // Puntero a todos los controles creados por Qt Designer.
    Ui::MainWindow *ui;

    // Objeto que controla toda la lógica del juego.
    Juego *juego;

    // Jugador humano.
    Jugador *jugador1;

    // Inteligencia artificial.
    Jugador *jugador2;

    // Actualiza toda la interfaz.
    void actualizarPantalla();

    // Muestra únicamente los botones de selección.
    void mostrarSeleccionElementos();

    // Muestra únicamente los botones de acción.
    void mostrarAcciones();

    // Función auxiliar para seleccionar un elemento.
    void seleccionarElemento(int indice);
};

#endif // MAINWINDOW_H