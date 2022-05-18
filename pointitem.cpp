#include "pointitem.h"

PointItem::PointItem()
{
    Initial();
}

void PointItem::Initial(){
    //画笔 - 边框笔
    QPen p=this->pen();
    p.setWidth(2);
    p.setColor(Qt::red);
    this->setPen(p);
    //画刷 - 背景色
    this->setBrush(QColor(0,0,0,100));
    //可选择、可移动
//    this->setFlags(QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemIsMovable);

}

//void PointItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
//    if(event->button()==Qt::LeftButton){
//        if(event->modifiers()==Qt::ShiftModifier){
//            this->setSelected(true);
//        }else if(event->modifiers()==Qt::AltModifier){

//        }else{
//            QGraphicsItem::mousePressEvent(event);
//            event->accept();
//        }
//    }else if(event->button()==Qt::RightButton){
//        event->ignore();
//    }
//}

//void PointItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
//    QPointF point=event->scenePos();
//    this->setPos(point);
//    QGraphicsItem::mouseMoveEvent(event);
//}

//void PointItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
//    QPointF point=event->scenePos();
//    this->setPos(point);
//    QGraphicsItem::mouseReleaseEvent(event);
//}
