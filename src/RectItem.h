#ifndef RECTITEM_H
#define RECTITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QtMath>

class RectItem : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    RectItem(const QPointF& center, qint32 width, qint32 height, const QColor& fillColor, const QString& text)
        : center(center)
        , width(width)
        , height(height)
        , fillColor(fillColor)
        , text(text)
    {
        this->setAcceptHoverEvents(true);
    }

    QRectF boundingRect() const override
    {
        return QRectF(center.x() - width / 2, center.y() - height / 2, width, height);
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override
    {
        painter->setPen(Qt::NoPen);
        painter->setBrush(fillColor);
        painter->save();
        painter->translate(center);
        painter->drawRect(-width / 2, -height / 2, width, height);
        painter->restore();
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
    QPointF center;
    qint32 width;
    qint32 height;
    QColor fillColor;
    QString text;
};

#endif // RECTITEM_H
