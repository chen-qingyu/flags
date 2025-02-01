#ifndef STARITEM_H
#define STARITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QtMath>

#include "MainWindow.h"

class StarItem : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    StarItem(const QPointF& center, qreal radius, const QColor& fillColor, qreal angle, const QString& text)
        : center(center)
        , radius(radius)
        , fillColor(fillColor)
        , angle(angle)
        , text(text)
    {
        this->setAcceptHoverEvents(true);
        this->connect(this, &StarItem::mouseEntered, MainWindow::instance(), &MainWindow::updateDesc);
        this->connect(this, &StarItem::mouseLeft, MainWindow::instance(), &MainWindow::clearDesc);
    }

    QRectF boundingRect() const override
    {
        return QRectF(center.x() - radius, center.y() - radius, radius * 2, radius * 2);
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override
    {
        QPolygonF points;
        for (int i = 0; i < 5; ++i)
        {
            points << QPointF(radius * qCos(i * 2 * M_PI / 5), -radius * qSin(i * 2 * M_PI / 5));
        }

        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.moveTo(points[0]);
        path.lineTo(points[2]);
        path.lineTo(points[4]);
        path.lineTo(points[1]);
        path.lineTo(points[3]);
        path.closeSubpath();

        painter->setPen(Qt::NoPen);
        painter->setBrush(fillColor);
        painter->save();
        painter->translate(center);
        painter->rotate(qRadiansToDegrees(angle) - 90);
        painter->drawPath(path);
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
    qreal radius;
    QColor fillColor;
    qreal angle;
    QString text;
};

#endif // STARITEM_H
