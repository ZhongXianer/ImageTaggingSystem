#ifndef IMAGE_H
#define IMAGE_H
#include <string>
#include <vector>
#include <iostream>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <QDebug>
#include <pixel.h>
#include <label.h>
#include <QImage>

using namespace rapidjson;
using namespace std;


class Image
{
public:
    Image();
    Image(string imageName,int imageHeight,int imageWidth);
    Image(QString directory,QString imageName);
private:
    string imagePath;
    string imageData;
    int imageHeight;
    int imageWidth;
    vector<Label> labels;
    int threshold=-1; //不管了先加上吧
public:
    void image2Json();
    void image2XML();

    const string &getImagePath() const;
    void setImagePath(const string &newImagePath);
    int getThreshold() const;
    void setThreshold(int newThreshold);
    int getImageHeight() const;
    void setImageHeight(int newImageHeight);
    int getImageWidth() const;
    void setImageWidth(int newImageWidth);
};

#endif // IMAGE_H
