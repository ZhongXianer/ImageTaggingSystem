#ifndef IMAGESCENE_H
#define IMAGESCENE_H

#include <QGraphicsScene>
#include <QObject>

class ImageScene : public QGraphicsScene
{
public:
    explicit ImageScene(QObject *parent = nullptr);
public:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
};

#endif // IMAGESCENE_H
