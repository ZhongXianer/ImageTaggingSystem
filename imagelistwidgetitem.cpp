#include "imagelistwidgetitem.h"

ImageListWidgetItem::ImageListWidgetItem(QWidget *parent) : QWidget(parent)
{

}

ImageListWidgetItem::ImageListWidgetItem(QString directory,QString fileName){
    QString imagePath=directory+"/"+fileName;
    this->setBaseSize(QSize(200,100));
    QHBoxLayout *layout=new QHBoxLayout;
    QLabel * image=new QLabel;
    image->setMaximumSize(100,100);
    QLabel * name=new QLabel;
    QPixmap * pixmap=new QPixmap(imagePath);
    image->setScaledContents(true);
    image->setPixmap(*pixmap);
    name->setText(fileName);
    layout->addWidget(image,4);
    layout->addSpacing(1);
    layout->addWidget(name,6);
    this->setLayout(layout);
}

void ImageListWidgetItem::setIndex(int id){
    this->index=id;
}

int ImageListWidgetItem::getIndex(){
    return this->index;
}

void ImageListWidgetItem::mouseDoubleClickEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        emit this->listItemClicked(index);
    }
}
