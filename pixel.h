#ifndef PIXEL_H
#define PIXEL_H


class Pixel
{
public:
    Pixel();
    Pixel(int x,int y);
    int getX() const;
    void setX(int newX);

    int getY() const;
    void setY(int newY);

private:
    int x;
    int y;
};

#endif // PIXEL_H
