#ifndef CARTAGRAPHICSITEM_H
#define CARTAGRAPHICSITEM_H

#include <QGraphicsObject>
#include "elemento.h"
#include "enums.h"

class CartaGraphicsItem : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit CartaGraphicsItem(const Elemento& elemento, QGraphicsItem* parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    void moverA(QPointF destino, int duracionMs = 350);
    void actualizarVida(int nuevaVida);
    void establecerSeleccionable(bool valor) { seleccionable = valor; }

    void establecerPosicionFila(QPointF pos) { posicionFila = pos; }
    void volverAFila();
    bool estaDerrotada() const { return derrotadaFlag; }
    void establecerEnCombate(bool valor);
    bool estaEnCombate() const { return enCombate; }

    static constexpr int ANCHO = 130;
    static constexpr int ALTO = 180;

signals:
    void clickeada(CartaGraphicsItem* carta);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    void dibujarIconoElemento(QPainter* painter, TipoElemento tipo, QRectF area);
    QString nombreTipo(TipoElemento tipo) const;
    QColor colorTipo(TipoElemento tipo) const;

    QString nombre;
    int vida;
    TipoElemento tipoAtaque;
    TipoElemento tipoDefensa;
    bool seleccionable = true;
    bool enHover = false;
    QPointF posicionFila;
    bool derrotadaFlag = false;
    bool enCombate = false;

    QPixmap imagenElemento;
    QPixmap marcoNormal;
    QPixmap marcoHover;
};

#endif