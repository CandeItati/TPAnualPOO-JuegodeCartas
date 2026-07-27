#include "cartagraphicsitem.h"
#include <QPainter>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QCursor>

// CONSTRUCTOR
CartaGraphicsItem::CartaGraphicsItem(const Elemento& elemento, QGraphicsItem* parent)
    : QGraphicsObject(parent)
{
    //Guardamos datos de las cartas.
    nombre = elemento.obtenerNombre();
    vida = elemento.obtenerVida();
    tipoAtaque = elemento.obtenerAtaque();
    tipoDefensa = elemento.obtenerDefensa();

    //Cargamos imagenes, desde resouces, de las cartas.
    imagenElemento.load(":/new/prefix1/Imagenes/ELEMENTOS/" + nombre.toUpper() + ".png");
    marcoNormal.load(":/new/prefix1/Imagenes/FondoCarta2-sinfondo.png");
    marcoHover.load(":/new/prefix1/Imagenes/FondoCarta3-sinfondo.png");

    //Interaccion del mouse sobre la carta.
    setAcceptHoverEvents(true);
    setCursor(Qt::PointingHandCursor);

    setTransformOriginPoint(ANCHO / 2.0, ALTO / 2.0);

    // Sombra que después vamos a usar para el "brillo" al pasar el mouse
    auto* sombra = new QGraphicsDropShadowEffect();
    sombra->setBlurRadius(0);
    sombra->setColor(QColor(0xf1c40f));
    sombra->setOffset(0, 0);
    setGraphicsEffect(sombra);
}

//Define el area que ocupa una carta.
QRectF CartaGraphicsItem::boundingRect() const
{
    return QRectF(0, 0, ANCHO, ALTO);
}

//Convierte el enumerador a string.
QString CartaGraphicsItem::nombreTipo(TipoElemento tipo) const
{
    switch (tipo) {
    case FUEGO:  return "Fuego";
    case AGUA:   return "Agua";
    case TIERRA: return "Tierra";
    case RAYO:   return "Rayo";
    case HIELO:  return "Hielo";
    }
    return "?";
}

// Método que pinta visualmente la carta en la pantalla.
void CartaGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    //Mejora calidad de las cartas.
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);

    //=========================
    // Imagen del elemento
    //=========================
    painter->save();
    painter->setClipRect(QRect(8, 28, 116, 116));
    painter->drawPixmap(
        QRect(8, 28, 116, 116),
        imagenElemento
        );
    painter->restore();

    //=========================
    // Marco
    //=========================
    painter->drawPixmap(boundingRect().toRect(), enHover ? marcoHover : marcoNormal);

    //=========================
    // Nombre
    //=========================
    painter->setPen(Qt::white);
    QFont fuenteNombre = painter->font();
    fuenteNombre.setPointSize(7);
    fuenteNombre.setBold(true);
    painter->setFont(fuenteNombre);
    painter->drawText(
        QRectF(8, 10, ANCHO * 0.55, 20),
        Qt::AlignCenter | Qt::AlignVCenter,
        nombre.toUpper());

    //=========================
    // Vida
    //=========================
    painter->setPen(QColor(0xe74c3c));
    QFont fuenteVida = painter->font();
    fuenteVida.setPointSize(7);
    painter->setFont(fuenteVida);
    painter->drawText(
        QRectF(ANCHO * 0.55, 10, ANCHO * 0.45 + 14, 20),
        Qt::AlignCenter | Qt::AlignVCenter,
        QString("%1").arg(vida));

    //=========================
    // Ataque
    //=========================
    painter->setPen(QColor(0x060301));
    QFont fuenteInfo = painter->font();
    fuenteInfo.setPointSize(7);
    painter->setFont(fuenteInfo);
    painter->drawText(
        QRectF(28, ALTO - 41, ANCHO - 16, 14),
        Qt::AlignLeft,
        nombreTipo(tipoAtaque));

    //=========================
    // Defensa
    //=========================
    painter->drawText(
        QRectF(28, ALTO - 24, ANCHO - 16, 14),
        Qt::AlignLeft,
        nombreTipo(tipoDefensa));
}

//Mueve la carta cuando entra en combate.
void CartaGraphicsItem::moverA(QPointF destino, int duracionMs)
{
    auto* animacion = new QPropertyAnimation(this, "pos");
    animacion->setDuration(duracionMs);
    animacion->setStartValue(pos());
    animacion->setEndValue(destino);
    animacion->setEasingCurve(QEasingCurve::OutCubic);
    animacion->start(QAbstractAnimation::DeleteWhenStopped);
}

// Actualiza la vida de la carta tras un ataque. Si la vida cae a 0 o menos, bloquea la carta marcándola como derrotada y desactiva la interacción.
void CartaGraphicsItem::actualizarVida(int nuevaVida)
{
    vida = nuevaVida;
    if (vida <= 0 && !derrotadaFlag) {
        derrotadaFlag = true;
        seleccionable = false;
    }
    update();
}

// Efecto hover estilo Clash Royale: se agranda y brilla.
void CartaGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent*)
{
    if (!seleccionable) return;
    enHover = true;
    setZValue(10);

    auto* animEscala = new QPropertyAnimation(this, "scale");
    animEscala->setDuration(150);
    animEscala->setStartValue(scale());
    animEscala->setEndValue(1.15); // 15% más grande
    animEscala->start(QAbstractAnimation::DeleteWhenStopped);

    auto* sombra = qobject_cast<QGraphicsDropShadowEffect*>(graphicsEffect());
    if (sombra) {
        auto* animBrillo = new QPropertyAnimation(sombra, "blurRadius");
        animBrillo->setDuration(150);
        animBrillo->setStartValue(sombra->blurRadius());
        animBrillo->setEndValue(25); // brillo dorado alrededor
        animBrillo->start(QAbstractAnimation::DeleteWhenStopped);
    }
    update();
}

//Si el mouse no esta encima de la carta esta vuelve a la normalidad.
void CartaGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
    if (!enHover) return;
    enHover = false;
    setZValue(0);

    auto* animEscala = new QPropertyAnimation(this, "scale");
    animEscala->setDuration(150);
    animEscala->setStartValue(scale());
    animEscala->setEndValue(1.0);
    animEscala->start(QAbstractAnimation::DeleteWhenStopped);

    auto* sombra = qobject_cast<QGraphicsDropShadowEffect*>(graphicsEffect());
    if (sombra) {
        auto* animBrillo = new QPropertyAnimation(sombra, "blurRadius");
        animBrillo->setDuration(150);
        animBrillo->setStartValue(sombra->blurRadius());
        animBrillo->setEndValue(0);
        animBrillo->start(QAbstractAnimation::DeleteWhenStopped);
    }
    update();
}

// Detecta cuando el jugador presiona la carta con el mouse.
void CartaGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent*)
{
    if (seleccionable) emit clickeada(this);
}

//Devuelve la carta a su posicion luego del combate.
void CartaGraphicsItem::volverAFila()
{
    setZValue(0);
    moverA(posicionFila);
}

// Cambia el estado de la carta cuando es enviada al centro del tablero a pelear.
void CartaGraphicsItem::establecerEnCombate(bool valor)
{
    enCombate = valor;

    // Por si el mouse había quedado "arriba" cuando la carta se volvió no-seleccionable (el hoverLeaveEvent puede no llegar nunca porque es la CARTA la que se movió, no el mouse): apagamos el brillo a la fuerza
    enHover = false;
    auto* sombra = qobject_cast<QGraphicsDropShadowEffect*>(graphicsEffect());
    if (sombra) {
        auto* animBrillo = new QPropertyAnimation(sombra, "blurRadius");
        animBrillo->setDuration(150);
        animBrillo->setStartValue(sombra->blurRadius());
        animBrillo->setEndValue(0);
        animBrillo->start(QAbstractAnimation::DeleteWhenStopped);
    }

    // El agrandado ahora es independiente del hover: si está en combate, grande; si no, tamaño normal.
    auto* animEscala = new QPropertyAnimation(this, "scale");
    animEscala->setDuration(200);
    animEscala->setStartValue(scale());
    animEscala->setEndValue(valor ? 1.15 : 1.0);
    animEscala->start(QAbstractAnimation::DeleteWhenStopped);

    update();
}