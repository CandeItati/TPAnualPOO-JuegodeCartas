#ifndef CARTAGRAPHICSITEM_H
#define CARTAGRAPHICSITEM_H

#include <QGraphicsObject> // Necesario para que la carta sea un objeto gráfico interactivo.
#include "elemento.h" // Se necesita para conocer los datos lógicos que formarán la carta.
#include "enums.h"

// La clase CartaGraphicsItem representa visualmente una carta en la interfaz gráfica del juego.
// Hereda de QGraphicsObject para poder ser dibujada en la escena y usar el sistema de Signals/Slots.
class CartaGraphicsItem : public QGraphicsObject
{
    Q_OBJECT

public:
    // Constructor. Recibe un objeto Elemento con las estadísticas y crea su representación visual.
    explicit CartaGraphicsItem(const Elemento& elemento, QGraphicsItem* parent = nullptr);
    //Define el área rectangular exacta que ocupa la carta
    QRectF boundingRect() const override;
    //Se encarga de dibujar todo el contenido visual
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    // Anima el movimiento de la carta hacia unas coordenadas destino en un tiempo determinado.
    void moverA(QPointF destino, int duracionMs = 350);
    // Actualiza la vida actual de la carta tras recibir daño.
    void actualizarVida(int nuevaVida);
    // Habilita o deshabilita la interacción del jugador con la carta.
    void establecerSeleccionable(bool valor) { seleccionable = valor; }

    // Guarda la posición original de la carta en la fila del jugador.
    void establecerPosicionFila(QPointF pos) { posicionFila = pos; }
    // Anima la carta para que regrese automáticamente a su posición original.
    void volverAFila();
    // Devuelve verdadero si la vida de la carta llegó a 0.
    bool estaDerrotada() const { return derrotadaFlag; }
    // Cambia el estado de la carta para indicar si está peleando.
    void establecerEnCombate(bool valor);
    // Devuelve verdadero si la carta está actualmente en combate.
    bool estaEnCombate() const { return enCombate; }

    // Dimensiones fijas que tendrá la carta visualmente.
    static constexpr int ANCHO = 130;
    static constexpr int ALTO = 180;

signals:
    // Señal que se emite automáticamente cuando el jugador hace clic sobre esta carta.
    void clickeada(CartaGraphicsItem* carta);

protected:
    // Métodos heredados que se sobreescriben para detectar las acciones del mouse sobre la carta.

    // Se activa cuando el puntero del mouse entra al área de la carta (para aplicar efecto de agrandado/brillo).
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    // Se activa cuando el puntero del mouse sale del área de la carta (para devolverla a la normalidad).
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
    // Se activa en el momento exacto en que se presiona el botón del mouse sobre la carta.
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    // Método auxiliar interno para obtener textos según el tipo de elemento.
    QString nombreTipo(TipoElemento tipo) const;

    // Atributos lógicos de la carta.
    QString nombre;
    int vida;
    TipoElemento tipoAtaque;
    TipoElemento tipoDefensa;

    // Banderas de estado del juego
    bool seleccionable = true; // Define si el jugador puede hacerle clic.
    bool enHover = false; // Define si el mouse está actualmente sobre la carta.
    QPointF posicionFila; // Almacena dónde debe ir la carta cuando no está combatiendo.
    bool derrotadaFlag = false; // Marca si la carta ya perdió toda su vida.
    bool enCombate = false; // Marca si la carta fue elegida para pelear.

    // Recursos visuales en caché para optimizar el dibujado.
    QPixmap imagenElemento;
    QPixmap marcoNormal;
    QPixmap marcoHover;
};

#endif