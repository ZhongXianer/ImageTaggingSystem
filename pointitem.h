#ifndef POINTITEM_H
#define POINTITEM_H

#include <QGraphicsEllipseItem>
#include <QObject>
#include <QPen>
#include <QGraphicsSceneMouseEvent>

class PointItem : public QGraphicsEllipseItem
{
public:
    PointItem();
//    void mousePressEvent(QGraphicsSceneMouseEvent * event);
//    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
private:
    void Initial();
};

#endif // POINTITEM_H
