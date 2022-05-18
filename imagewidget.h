 #ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H
#include <QHBoxLayout>
#include <cstdlib>
#include <QLabel>
#include <opencv2/opencv.hpp>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <string>
#include <QEvent>
#include <QMouseEvent>
#include <vector>
#include <imagescene.h>
#include <imageitem.h>
#include <imagegraphicsview.h>

class ImageWidget:public QWidget
{
public:
    ImageWidget(QString fileName);
    void setViewAction(ImageGraphicsView::user_action act);
    void setThreshold(int val);
private:
    QString fileName;
    QLabel * ImageLabel;
    ImageGraphicsView * imageView;
    //场景
    ImageScene * scene;
    //画布
    ImageItem * imageItem;
    //绘制的OpenCV图像
    cv::Mat image;
    //显著性分割的阈值
    int threshold;
private:
    void readImage();
    void scaleImage(float factor);
public slots:
    void showImage(const cv::Mat &image);
};


#endif // IMAGEWIDGET_H
