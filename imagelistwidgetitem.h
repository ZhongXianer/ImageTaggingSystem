#ifndef IMAGELISTWIDGETITEM_H
#define IMAGELISTWIDGETITEM_H
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>


class ImageListWidgetItem : public QWidget
{
    Q_OBJECT
public:
    explicit ImageListWidgetItem(QWidget *parent = nullptr);
    ImageListWidgetItem(QString directory,QString fileName);
    void setIndex(int id);
    int getIndex();
    void mouseDoubleClickEvent(QMouseEvent * event);
signals:
    void listItemClicked(int);
private:
    int index;
};

#endif // IMAGELISTWIDGETITEM_H
