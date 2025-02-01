#ifndef CIRCLEITEM_H
#define CIRCLEITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QtMath>

#include "MainWindow.h"

class CircleItem : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    CircleItem(QPointF center, qreal radius, const QColor& fillColor, const QString& text)
        : center(center)
        , radius(radius)
        , fillColor(fillColor)
        , text(text)
    {
        this->setAcceptHoverEvents(true);
        this->connect(this, &CircleItem::mouseEntered, MainWindow::instance(), &MainWindow::updateDesc);
        this->connect(this, &CircleItem::mouseLeft, MainWindow::instance(), &MainWindow::clearDesc);
    }

    QRectF boundingRect() const override
    {
        return QRectF(center.x() - radius, center.y() - radius, 2 * radius, 2 * radius);
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override
    {
        painter->setPen(Qt::NoPen);
        painter->setBrush(fillColor);
        painter->drawEllipse(center, radius, radius);
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
    QString text;
};

#endif // CIRCLEITEM_H
