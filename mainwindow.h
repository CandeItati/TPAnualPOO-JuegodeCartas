#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "juego.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:


    void on_PBelemento1_clicked();
    void on_PBelemento2_clicked();
    void on_PBelemento3_clicked();
    void on_PBelemento4_clicked();
    void on_PBelemento5_clicked();

    void on_btnAtacar_clicked();
    void on_btnCambiar_clicked();


private:
    Ui::MainWindow *ui;

    Juego *juego;

    Jugador *jugador1;
    Jugador *jugador2;


    void actualizarPantalla();
    void mostrarSeleccionElementos();
    void mostrarAcciones();
    void seleccionarElemento(int indice);

};
#endif // MAINWINDOW_H
