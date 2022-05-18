#ifndef IMAGEGRAPHICSVIEW_H
#define IMAGEGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWidget>
#include <QWheelEvent>
#include <QMouseEvent>

class ImageGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    enum user_action {normal_act,rectangle_act,wait_act,man_adjust_act,auto_adjust_act};
    ImageGraphicsView();
    void setUserAction(user_action act);
    user_action getUserAction();
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
private:
    user_action USER_ACT;
};

#endif // IMAGEGRAPHICSVIEW_H
