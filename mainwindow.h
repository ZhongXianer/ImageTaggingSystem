#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTabWidget>
#include <QToolBar>
#include <imagewidget.h>
#include <QLayout>
#include <QFileDialog>
#include <QSlider>
#include <QPushButton>
#include <QLineEdit>
#include <imagelistwidgetitem.h>
#include <imagegraphicsview.h>
#include <exportchoosedialg.h>
#include <image.h>
#include <QInputDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //构建主窗口界面
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //指针类型静态成员变量，用于在其他界面引用主界面的控件
    static MainWindow *mutualUi;
    enum action {draw_rec,move_point,auto_correct};
private:
    struct ImageFile{
        QString directory;
        QString imageName;
        int threshold=-1; //当前图片的阈值
        bool isOpen;
    };
    QList<ImageFile> fileList; //已被引入的所有图片
    QList<Image*> openList; //已经打开的所有图片直接存储为最后导出文件的格式
    Image * nowOpen=nullptr; //当前界面的图片
    int file_count;
public slots:
    //打开图片
    void openImg();
    //打开文件夹
    void openDirectory();
    //矩形框选事件
    void drawRectangle();
    //手工调整事件
    void manAdjust();
    //自动调整事件
    void autoAdjust();
    //导出标注文件事件
    void exportAnnotation();
    //添加标注
    void addLabel();
    //增加一个tabWidget
    void addImageTab(ImageFile &image);
    //阈值进度条改变
    void thresholdChanged(int val);
    //阈值输入改变
    void thresholdInputChanged();
    //滑动条释放事件
    void thresholdReleased();
    //列表item点击事件
    void fileListItemClick(int index);
    //图片信息刷新事件
    void imageTabChanged(int index);
private:
    Ui::MainWindow *ui;
    QGroupBox * createFileList();
    QGroupBox * createImgTab();
    QGroupBox * createTagTool();
    void initThresholdSlider();
    void refreshAnnotationBox();
    void initToolBar();
    void addFileItem(QString directory,QString fileName);
    ImageWidget * getCurrentWidget();
private:
    QListWidget * FileWidget;
    QListWidget * TagList;
    QTabWidget * ImgTab;
    QToolBar * MainToolBar;
    QSlider * ThresholdSlider;
    QLineEdit * ThresholdInput;
    QPushButton * AddTagBtn;
    QLabel * imageNameLabel;
    QLabel * imageWidthLabel;
    QLabel * imageHeightLabel;
};

#endif // MAINWINDOW_H
