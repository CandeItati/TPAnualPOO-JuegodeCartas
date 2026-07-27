#include "cartagraphicsitem.h"
#include <QPainter>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QCursor>

CartaGraphicsItem::CartaGraphicsItem(const Elemento& elemento, QGraphicsItem* parent)
    : QGraphicsObject(parent)
{
    nombre = elemento.obtenerNombre();
    vida = elemento.obtenerVida();
    tipoAtaque = elemento.obtenerAtaque();
    tipoDefensa = elemento.obtenerDefensa();

    imagenElemento.load(":/new/prefix1/Imagenes/ELEMENTOS/" + nombre.toUpper() + ".png");
    marcoNormal.load(":/new/prefix1/Imagenes/FondoCarta2-sinfondo.png");
    marcoHover.load(":/new/prefix1/Imagenes/FondoCarta3-sinfondo.png");

    setAcceptHoverEvents(true);
    setCursor(Qt::PointingHandCursor);

    setTransformOriginPoint(ANCHO / 2.0, ALTO / 2.0);

    // Sombra que después vamos a usar para el "brillo" al pasar el mouse
    auto* sombra = new QGraphicsDropShadowEffect();
    sombra->setBlurRadius(0);
    sombra->setColor(QColor(0xf1c40f)); // amarillo dorado
    sombra->setOffset(0, 0);
    setGraphicsEffect(sombra);
}

QRectF CartaGraphicsItem::boundingRect() const
{
    return QRectF(0, 0, ANCHO, ALTO);
}

// Devuelve un color asociado al tipo elemental (para pintar la carta)
QColor CartaGraphicsItem::colorTipo(TipoElemento tipo) const
{
    switch (tipo) {
    case FUEGO:  return QColor(0xe74c3c);
    case AGUA:   return QColor(0x3498db);
    case TIERRA: return QColor(0x8d6e34);
    case RAYO:   return QColor(0xf1c40f);
    case HIELO:  return QColor(0x5dade2);
    }
    return QColor(0x7f8c8d);
}

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

// Dibuja un ícono simple (llama, gota, etc) usando formas básicas de QPainter
void CartaGraphicsItem::dibujarIconoElemento(QPainter* painter, TipoElemento tipo, QRectF area)
{
    painter->save();
    painter->setBrush(colorTipo(tipo));
    painter->setPen(Qt::NoPen);

    QPointF centro = area.center();
    qreal r = area.width() / 2;

    if (tipo == FUEGO) {
        // Llama: un triángulo curvo simple con QPainterPath
        QPainterPath llama;
        llama.moveTo(centro.x(), area.top());
        llama.cubicTo(area.left(), centro.y(),
                      area.left() + r * 0.3, area.bottom(),
                      centro.x(), area.bottom());
        llama.cubicTo(area.right() - r * 0.3, area.bottom(),
                      area.right(), centro.y(),
                      centro.x(), area.top());
        painter->drawPath(llama);
    } else if (tipo == AGUA) {
        // Gota
        QPainterPath gota;
        gota.moveTo(centro.x(), area.top());
        gota.cubicTo(area.left(), area.top() + r,
                     area.left(), area.bottom(),
                     centro.x(), area.bottom());
        gota.cubicTo(area.right(), area.bottom(),
                     area.right(), area.top() + r,
                     centro.x(), area.top());
        painter->drawPath(gota);
    } else if (tipo == RAYO) {
        // Rayo en zigzag
        QPolygonF rayo;
        rayo << QPointF(centro.x() + r*0.2, area.top())
             << QPointF(centro.x() - r*0.4, centro.y())
             << QPointF(centro.x(), centro.y())
             << QPointF(centro.x() - r*0.2, area.bottom())
             << QPointF(centro.x() + r*0.4, centro.y())
             << QPointF(centro.x(), centro.y());
        painter->drawPolygon(rayo);
    } else if (tipo == HIELO) {
        // Cristal: rombo
        QPolygonF rombo;
        rombo << QPointF(centro.x(), area.top())
              << QPointF(area.right(), centro.y())
              << QPointF(centro.x(), area.bottom())
              << QPointF(area.left(), centro.y());
        painter->drawPolygon(rombo);
    } else { // TIERRA
        // Montaña: triángulo
        QPolygonF montana;
        montana << QPointF(centro.x(), area.top())
                << QPointF(area.right(), area.bottom())
                << QPointF(area.left(), area.bottom());
        painter->drawPolygon(montana);
    }
    painter->restore();
}

void CartaGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
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

void CartaGraphicsItem::moverA(QPointF destino, int duracionMs)
{
    auto* animacion = new QPropertyAnimation(this, "pos");
    animacion->setDuration(duracionMs);
    animacion->setStartValue(pos());
    animacion->setEndValue(destino);
    animacion->setEasingCurve(QEasingCurve::OutCubic);
    animacion->start(QAbstractAnimation::DeleteWhenStopped);
}

void CartaGraphicsItem::actualizarVida(int nuevaVida)
{
    vida = nuevaVida;
    if (vida <= 0 && !derrotadaFlag) {
        derrotadaFlag = true;
        seleccionable = false;
    }
    update();
}

// --- Efecto hover estilo Clash Royale: se agranda y brilla ---
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

void CartaGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent*)
{
    if (seleccionable) emit clickeada(this);
}
void CartaGraphicsItem::volverAFila()
{
    setZValue(0);
    moverA(posicionFila);
}
void CartaGraphicsItem::establecerEnCombate(bool valor)
{
    enCombate = valor;

    // Por si el mouse había quedado "arriba" cuando la carta se volvió
    // no-seleccionable (el hoverLeaveEvent puede no llegar nunca porque
    // es la CARTA la que se movió, no el mouse): apagamos el brillo a la fuerza.
    enHover = false;
    auto* sombra = qobject_cast<QGraphicsDropShadowEffect*>(graphicsEffect());
    if (sombra) {
        auto* animBrillo = new QPropertyAnimation(sombra, "blurRadius");
        animBrillo->setDuration(150);
        animBrillo->setStartValue(sombra->blurRadius());
        animBrillo->setEndValue(0);
        animBrillo->start(QAbstractAnimation::DeleteWhenStopped);
    }

    // El agrandado ahora es independiente del hover: si está en combate, grande;
    // si no, tamaño normal.
    auto* animEscala = new QPropertyAnimation(this, "scale");
    animEscala->setDuration(200);
    animEscala->setStartValue(scale());
    animEscala->setEndValue(valor ? 1.15 : 1.0);
    animEscala->start(QAbstractAnimation::DeleteWhenStopped);

    update();
}