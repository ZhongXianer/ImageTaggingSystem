#include "pixel.h"

Pixel::Pixel()
{

}

Pixel::Pixel(int x,int y){
    this->x=x;
    this->y=y;
}

int Pixel::getX() const
{
    return x;
}

void Pixel::setX(int newX)
{
    x = newX;
}

int Pixel::getY() const
{
    return y;
}

void Pixel::setY(int newY)
{
    y = newY;
}
