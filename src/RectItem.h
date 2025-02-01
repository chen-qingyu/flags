#ifndef RECTITEM_H
#define RECTITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QtMath>

class RectItem : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    RectItem(qreal x, qreal y, qreal width, qreal height, const QColor& fillColor, const QString& text)
        : x(x)
        , y(y)
        , width(width)
        , height(height)
        , fillColor(fillColor)
        , text(text)
    {
        this->setAcceptHoverEvents(true);
    }

    QRectF boundingRect() const override
    {
        return QRectF(x, y, width, height);
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override
    {
        painter->setPen(Qt::NoPen);
        painter->setBrush(fillColor);
        painter->drawRect(QRectF(x, y, width, height));
    }

signals:
    void mouseEntered(const QString& text);
    void mouseLeft();

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override
    {
        emit mouseEntered(text);
    }

    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override
    {
        emit mouseLeft();
    }

private:
    qreal x;
    qreal y;
    qreal width;
    qreal height;
    QColor fillColor;
    QString text;
};

#endif // RECTITEM_H
