#include "imagescene.h"

ImageScene::ImageScene(QObject *parent) : QGraphicsScene(parent)
{

}

void ImageScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    //将点击事件向下传递到item中
    QGraphicsScene::mousePressEvent(event);
}

void ImageScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsScene::mouseMoveEvent(event);
}

void ImageScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsScene::mouseReleaseEvent(event);
}
