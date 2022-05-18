#include "imagegraphicsview.h"

ImageGraphicsView::ImageGraphicsView()
{
    this->setMouseTracking(true);
    this->USER_ACT=normal_act;
}

/**
 * @brief ImageGraphicsView::setUserAction 设置当前用户选择的操作并修改鼠标光标
 * @param act 用户当前的操作 枚举类型
 */
void ImageGraphicsView::setUserAction(user_action act){
    this->USER_ACT=act;
    switch (act) {
    case normal_act:
        this->setCursor(Qt::ArrowCursor);
        break;
    case rectangle_act:
        this->setCursor(Qt::CrossCursor);
        break;
    case wait_act:
        this->setCursor(Qt::WaitCursor);
        break;
    case man_adjust_act:
        this->setCursor(Qt::PointingHandCursor);
        break;
    default:
        break;
    }
}

ImageGraphicsView::user_action ImageGraphicsView::getUserAction(){
    return this->USER_ACT;
}

/**
 * @brief ImageGraphicsView::wheelEvent 滚轮响应事件
 * @param event
 */
void ImageGraphicsView::wheelEvent(QWheelEvent *event){
    if(event->modifiers()==Qt::ControlModifier){
        if(event->delta()>0){
            this->scale(1.1,1.1);
        }else{
            this->scale(0.9,0.9);
        }
    }
}


void ImageGraphicsView::mousePressEvent(QMouseEvent *event){
    QGraphicsView::mousePressEvent(event);
}

void ImageGraphicsView::mouseMoveEvent(QMouseEvent *event){
    QGraphicsView::mouseMoveEvent(event);
}

void ImageGraphicsView::mouseReleaseEvent(QMouseEvent *event){
    QGraphicsView::mouseReleaseEvent(event);
}
