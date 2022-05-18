#include "imageitem.h"

ImageItem::ImageItem()
{
    rectangle=new QGraphicsRectItem;
    path_item=new QGraphicsPathItem;
    initRectangle();
    initPathItem();
}

/**
 * @brief ImageItem::initRectangle 初始化矩形框item相关设置
 */
void ImageItem::initRectangle(){
    left_point=QPointF(0,0);
    right_point=QPointF(0,0);
    QPen pen=rectangle->pen();
    pen.setWidth(3);
    pen.setColor(Qt::black);
    rectangle->setPen(pen);
    rectangle->setBrush(QColor(0,0,0,20));
}

/**
 * @brief ImageItem::initPathItem 初始化显示显著性识别路径item
 */
void ImageItem::initPathItem(){
    QPen pen ;
    pen.setWidth(2);
    pen.setColor(Qt::green);
    path_item->setPen(pen);
}

/**
 * @brief ImageItem::setScene 设置item所属的场景 同时可以把初始化之后的矩形和路径提前加入
 * @param graphicsScene
 */
void ImageItem::setScene(ImageScene *graphicsScene){
    this_scene=graphicsScene;
    this_scene->addItem(rectangle);
    this_scene->addItem(path_item);
}

/**
 * @brief ImageItem::setView 设置item所属的控件 用于获取当前操作
 * @param graphicsView
 */
void ImageItem::setView(ImageGraphicsView *graphicsView){
    this_view=graphicsView;
}

void ImageItem::setImagePath(QString path){
    imagePath=path;
}

void ImageItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(this_view->getUserAction()==ImageGraphicsView::rectangle_act){
        if(event->button()&Qt::LeftButton){
            temp_point=event->scenePos();
        }
    }else if(this_view->getUserAction()==ImageGraphicsView::man_adjust_act){
       QPointF p=event->scenePos();
       pointSeleced(p);
    }
}

void ImageItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QPointF p=event->scenePos();
    if(this_view->getUserAction()==ImageGraphicsView::rectangle_act){
        if(temp_point.x()<p.x()){
            left_point.setX(temp_point.x());
            right_point.setX(p.x());
        }else{
            left_point.setX(p.x());
            right_point.setX(temp_point.x());
        }
        if(temp_point.y()<p.y()){
            left_point.setY(temp_point.y());
            right_point.setY(p.y());
        }else{
            left_point.setY(p.y());
            right_point.setY(temp_point.y());
        }
        int w=right_point.x()-left_point.x();
        int h=right_point.y()-left_point.y();
        rectangle->setRect(left_point.x(),left_point.y(),w,h);
    }else if(this_view->getUserAction()==ImageGraphicsView::man_adjust_act){
        if(selected!=-1){
            pointItems[selected]->setRect(p.x()-1,p.y()-1,2,2);
            edge_list[selected]->setX(p.x());
            edge_list[selected]->setY(p.y());
            updatePath();
        }
    }
}

void ImageItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
   QGraphicsItem::mouseReleaseEvent(event);
   QPointF p=event->scenePos();
   if(this_view->getUserAction()==ImageGraphicsView::rectangle_act){
       if(temp_point.x()<p.x()){
           left_point.setX(temp_point.x());
           right_point.setX(p.x());
       }else{
           left_point.setX(p.x());
           right_point.setX(temp_point.x());
       }
       if(temp_point.y()<p.y()){
           left_point.setY(temp_point.y());
           right_point.setY(p.y());
       }else{
           left_point.setY(p.y());
           right_point.setY(temp_point.y());
       }
       getSaliency();
       drawSaliency();
   }else if(this_view->getUserAction()==ImageGraphicsView::man_adjust_act){
       if(selected!=-1){
           pointItems[selected]->setRect(p.x()-1,p.y()-1,2,2);
           edge_list[selected]->setX(p.x());
           edge_list[selected]->setY(p.y());
           updatePath();
           selected=-1;
       }
   }
}

/**
 * @brief ImageItem::getSaliency 与底层算法结合，获得显著性识别的边缘
 * 问题：python多次调用引入模块出错的问题
 * 解决：直接放在main函数里
 */
void ImageItem::getSaliency(){
    this_view->setUserAction(ImageGraphicsView::wait_act);
    removeSaliency();
    if(!Py_IsInitialized()){
        qDebug()<<"Python init fail!";
    }
    PyObject * pModule=PyImport_ImportModule("SaliencyTest");
    if(!pModule){
        qDebug()<<"Get module error!";
        Py_Finalize();
        return;
    }
    PyObject * pFunction=PyObject_GetAttrString(pModule,"test_rc_map");
    PyObject * args=PyTuple_New(6);
    char* path;
    QByteArray t=imagePath.toLatin1();
    path=t.data();
    int width=right_point.x()-left_point.x();
    int height=right_point.y()-left_point.y();
    int left_x=left_point.x();
    int left_y=left_point.y();
    PyTuple_SetItem(args,0,Py_BuildValue("s",path));
    PyTuple_SetItem(args,1,Py_BuildValue("i",left_x));
    PyTuple_SetItem(args,2,Py_BuildValue("i",left_y));
    PyTuple_SetItem(args,3,Py_BuildValue("i",width));
    PyTuple_SetItem(args,4,Py_BuildValue("i",height));
    PyTuple_SetItem(args,5,Py_BuildValue("i",threshold));
    qDebug()<<"阈值："<<threshold;
    PyObject * line=PyEval_CallObject(pFunction,args);
    int size=PyList_Size(line);
    for(int i=0;i<size;i++){
        PyObject* item=PyList_GetItem(line,i);
        int x,y;
        PyArg_ParseTuple(item,"i|i",&x,&y);
        PointItem * point=new PointItem;
        Pixel * e=new Pixel(x,y);
        edge_list.append(e);
        point->setRect(x-1,y-1,2,2);
        pointItems.append(point);
    }
    this_view->setUserAction(ImageGraphicsView::normal_act);

}

void ImageItem::updatePath(){
    QPainterPath *p =new QPainterPath;
    int size=edge_list.size();
    p->moveTo(edge_list[size-1]->getX(),edge_list[size-1]->getY());
    for(int i=0;i<pointItems.size();i++){
        p->lineTo(edge_list[i]->getX(),edge_list[i]->getY());
    }
    path_item->setPath(*p);
    path_item->show();
}

/**
 * @brief ImageItem::drawSaliency 将显著性识别的边缘绘出
 */
void ImageItem::drawSaliency(){
    qDebug()<<"draw saliency";
    QPainterPath * p=new QPainterPath;
    int size=pointItems.size();
    p->moveTo(edge_list[size-1]->getX(),edge_list[size-1]->getY());
    for(int i=0;i<pointItems.size();i++){
        this_scene->addItem(pointItems[i]);
        p->lineTo(edge_list[i]->getX(),edge_list[i]->getY());
    }
    path_item->setPath(*p);
    path_item->show();
//    this_scene->removeItem(rectangle);
}

/**
 * @brief ImageItem::removeSaliency 移除当前显著性检测结果
 */
void ImageItem::removeSaliency(){
    if(!pointItems.empty()){
        for(int i=0;i<pointItems.size();i++){
            this_scene->removeItem(pointItems[i]);
        }
        pointItems.clear();
        edge_list.clear();
    }
}

/**
 * @brief ImageItem::pointSeleced 根据当前鼠标点击的点判断是否是边缘点集中的点
 * @param p 鼠标点击的位置
 * @return
 */
bool ImageItem::pointSeleced(QPointF p){
    Pixel * e;
    bool ans=false;
    for(int i=0;i<edge_list.size();i++){
        e=edge_list[i];
        if(p.x()>=e->getX()-1&&p.x()<=e->getX()+1){
            if(p.y()>=e->getY()-1&&p.y()<=e->getY()+1){
                selected=i;
                ans=true;
                break;
            }
        }
    }
    return ans;
}

/**
 * @brief ImageItem::setThreshold 设置显著性识别的阈值
 * @param val 值
 */
void ImageItem::setThreshold(int val){
    this->threshold=val;
    getSaliency();
    drawSaliency();
}
