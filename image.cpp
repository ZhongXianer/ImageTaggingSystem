#include "image.h"

Image::Image()
{

}

/**
 * @brief Image::Image MainWindow里可以调用的构造函数
 * @param directory
 * @param imageName
 */
Image::Image(QString directory,QString imageName){
    QString path=directory+"/"+imageName;
    QImage image(path);
    this->imagePath=imageName.toStdString();
    this->imageWidth=image.width();
    this->imageHeight=image.height();
}

int Image::getImageWidth() const
{
    return imageWidth;
}

void Image::setImageWidth(int newImageWidth)
{
    imageWidth = newImageWidth;
}

int Image::getImageHeight() const
{
    return imageHeight;
}

void Image::setImageHeight(int newImageHeight)
{
    imageHeight = newImageHeight;
}

int Image::getThreshold() const
{
    return threshold;
}

void Image::setThreshold(int newThreshold)
{
    threshold = newThreshold;
}

const string &Image::getImagePath() const
{
    return imagePath;
}

void Image::setImagePath(const string &newImagePath)
{
    imagePath = newImagePath;
}

/**
 * @brief Image::image2Json 将图像标注数据生成为Json文件
 * 注：格式参照labelme => 还是自己编一个格式
 */
void Image::image2Json(){
    StringBuffer s;
    Writer<StringBuffer> writer(s);
    writer.StartObject();
    writer.Key("imagePath");
    writer.String(imagePath.c_str());
    writer.Key("imageWidth");
    writer.Int(imageWidth);
    writer.Key("imageHeight");
    writer.Int(imageHeight);
    writer.Key("labels");
    writer.StartArray();
    for(Label i:labels){
        writer.Key("label");
        writer.String(i.getAnnotation().c_str());
        writer.Key("points");
        writer.StartArray();
        for(auto j:i.getEdges()){
            writer.StartArray();
            writer.Int(j.getX());
            writer.Int(j.getY());
            writer.EndArray();
        }
        writer.EndArray();
    }
    writer.EndArray();
    writer.EndObject();
    qDebug()<<s.GetString();
}
