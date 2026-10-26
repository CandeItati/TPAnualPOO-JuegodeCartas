#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include "mainwindow.h"

#include <QWidget>

namespace Ui {
class MenuPrincipal;
}

class MenuPrincipal : public QWidget
{
    Q_OBJECT

public:
    explicit MenuPrincipal(QWidget *parent = nullptr);
    ~MenuPrincipal();

private slots:

    void on_btnNuevaPartida_clicked();

    void on_btnCargarPartida_clicked();

    void on_btnOpciones_clicked();

    void on_btnVolver_clicked();

    void on_btnVolver_2_clicked();

    void on_btnVolver_3_clicked();

    void on_btnSalir_clicked();

    void on_btnCrearPartida_clicked();

    void on_btnSlot1_clicked();
    void on_btnSlot2_clicked();
    void on_btnSlot3_clicked();
    void on_btnSlot4_clicked();
    void on_btnSlot5_clicked();

private:
    Ui::MenuPrincipal *ui;

    void habilitarMenuPrincipal(
        bool habilitado);

    MainWindow* ventanaJuego;

    void actualizarSlots();

    void cargarSlot(int numeroSlot);

    QWidget* overlayMenu = nullptr;
};

#endif // MENUPRINCIPAL_H
