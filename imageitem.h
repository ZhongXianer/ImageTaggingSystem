#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <pointitem.h>
#include <ui_mainwindow.h>
#include <imagegraphicsview.h>
#include <imagescene.h>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <iostream>
#include <QGraphicsSceneMouseEvent>
#include <QVector>
#include <QPointF>
#include <QPen>
#include <QBrush>
#include <QDebug>
#include <string>
#include <QList>
#include <cstdlib>
#include <pixel.h>
//解决python和Qt的关键词slots冲突
#pragma push_macro("slots")
#undef slots
#include <Python.h>
#pragma pop_macro("slots")

class ImageItem : public QGraphicsPixmapItem
{
public:
    ImageItem();
    //一组标注的结构体
    struct Label_Item{
        QGraphicsRectItem * rec_item;
        QGraphicsPathItem * path_item;
        QList<Pixel> edge_list;
    };
    enum action_type {};
    enum action_state {unstart,drawing};
public:
    //设置item的场景
    void setScene(ImageScene *graphicsScene);
    //设置item的控件
    void setView(ImageGraphicsView * graphicsView);
    //设置打开图片的路径
    void setImagePath(QString path);
    //鼠标点击事件
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    //鼠标移动事件
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    //鼠标释放事件
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
    //设置显著性识别的阈值
    void setThreshold(int val);
private:
    //所属场景
    ImageScene * this_scene;
    //所属控件 用于获取当前操作状态
    ImageGraphicsView * this_view;
    QList<Label_Item*> label_items;
    Label_Item * now_label;
    int threshold = -1;
    QList<Pixel*> edge_list; //点集 用于绘制路径
    QList<PointItem*> pointItems; //点集 用于绘制点   
    QString imagePath;
    QVector<QPointF> points;
    QGraphicsPathItem * path_item;
    QPointF left_point,right_point,temp_point;
    QGraphicsRectItem * rectangle;
    //被选中的点
    int selected=-1;
private:
    void initRectangle();
    void initPathItem();
    void DrawRec(QPointF p_current);
    void getSaliency();
    void removeSaliency();
    void drawSaliency();
    void updatePath();
    bool pointSeleced(QPointF p);
};


#endif // IMAGEITEM_H
