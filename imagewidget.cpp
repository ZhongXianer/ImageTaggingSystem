#include "imagewidget.h"

ImageWidget::ImageWidget(QString fileName)
{
    this->fileName=fileName;
    QHBoxLayout * layout=new QHBoxLayout;
    imageView=new ImageGraphicsView;
    scene=new ImageScene();
    imageItem=new ImageItem();
    //给场景增加画布
    scene->addItem(imageItem);
    imageItem->setScene(scene);
    imageItem->setImagePath(fileName);
    //控件绑定场景
    imageView->setScene(scene);
    //能使QGraphicsView控件的鼠标跟踪
    imageView->setMouseTracking(true);
    imageItem->setView(imageView);
    layout->addWidget(imageView);
    this->setLayout(layout);
    readImage();
}

/**
 * @brief ImageWidget::readImage 读入图片转换为Mat并调用showImage函数进行展示
 */
void ImageWidget::readImage(){
    std::string name=fileName.toStdString();
    cv::Mat imageToShow;
    cv::Mat t_image=cv::imread(name);
    cv::cvtColor(t_image,imageToShow,cv::COLOR_BGR2RGB,0);
    showImage(imageToShow);
}

/**
 * @brief ImageWidget::showImage 将opencv Mat绘制到QGraphicsView
 * @param imageToShow
 * ? 不用mat应该也可以吧
 */
void ImageWidget::showImage(const cv::Mat &imageToShow){
    image=imageToShow.clone();
    //三通道RGB
    if(image.type()==CV_8UC3)
        imageItem->setPixmap(QPixmap::fromImage(QImage((const unsigned char*)imageToShow.data,imageToShow.cols,imageToShow.rows,imageToShow.cols*3,QImage::Format::Format_RGB888)));
    //四通道RGBA
    else if(image.type()==CV_8UC4)
        imageItem->setPixmap(QPixmap::fromImage(QImage((const unsigned char*)imageToShow.data,imageToShow.cols,imageToShow.rows,imageToShow.cols*4,QImage::Format::Format_RGBA8888_Premultiplied)));
    //单通道Gray
    else if(image.type()==CV_8UC1)
        imageItem->setPixmap(QPixmap::fromImage(QImage((const unsigned char*)imageToShow.data,imageToShow.cols,imageToShow.rows,imageToShow.cols,QImage::Format::Format_Grayscale8)));
    else
        return;
    this->imageView->show();
}

/**
 * @brief ImageWidget::setViewAction 设置用户现在正在进行的操作
 * @param act
 */
void ImageWidget::setViewAction(ImageGraphicsView::user_action act){
    imageView->setUserAction(act);
}

/**
 * @brief ImageWidget::setThreshold 将显著性识别的阈值传递给相应的item
 * @param val
 */
void ImageWidget::setThreshold(int val){
    imageItem->setThreshold(val);
}
