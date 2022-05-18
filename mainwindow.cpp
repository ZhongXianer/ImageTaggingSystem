#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

//初始化
MainWindow *MainWindow::mutualUi = nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mutualUi=this; //赋值
    file_count=0;
    setWindowTitle("半自动图像标记系统");
    this->resize(1280,800);
    initToolBar();
    QHBoxLayout * MainHBoxLayout = new QHBoxLayout(this);

    QGroupBox * FileList=createFileList();
    QGroupBox * ImgTab=createImgTab();
    QGroupBox * TagWidget=createTagTool();

    MainHBoxLayout->addWidget(FileList,2);
    MainHBoxLayout->addWidget(ImgTab,5);
    MainHBoxLayout->addWidget(TagWidget,2);
    ui->centralWidget->setLayout(MainHBoxLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::createFileList 初始化文件列表
 * @return 左侧文件列表
 */
QGroupBox * MainWindow::createFileList(){
    QGroupBox * fileBox=new QGroupBox("文件列表");
    FileWidget=new QListWidget;
    QHBoxLayout * AutoFileLayout=new QHBoxLayout;
    AutoFileLayout->addWidget(FileWidget);
    fileBox->setLayout(AutoFileLayout);
    //设置边距和间距
    FileWidget->setContentsMargins(0,0,0,0);
    FileWidget->setSpacing(5);
    return fileBox;
}

/**
 * @brief MainWindow::createTagTool 初始化标记工具框
 * @return 右侧标注界面
 */
QGroupBox * MainWindow::createTagTool(){
    //界面分块
    QGroupBox * TagBox=new QGroupBox("标记工具");
    QGroupBox * ImageInfoBox=new QGroupBox("图片信息");
    QGroupBox * TagShowBox=new QGroupBox("所有标记");
    QGroupBox * ArgSetBox=new QGroupBox("设置参数");
    //每块的布局
    QVBoxLayout * TagBoxLayout=new QVBoxLayout; //总布局
    QVBoxLayout * ImageInfoLayout=new QVBoxLayout; //图片信息展示布局
    QHBoxLayout * TagListLayout=new QHBoxLayout; //标记信息展示布局
    QVBoxLayout * ArgsLayout=new QVBoxLayout; //参数设置总布局
    QHBoxLayout * thresholdSetLayout=new QHBoxLayout; //阈值设置滑动条布局

    imageNameLabel=new QLabel;
    imageWidthLabel=new QLabel;
    imageHeightLabel=new QLabel;
    ImageInfoLayout->addWidget(imageNameLabel);
    ImageInfoLayout->addWidget(imageWidthLabel);
    ImageInfoLayout->addWidget(imageHeightLabel);
    ImageInfoBox->setLayout(ImageInfoLayout);

    TagList=new QListWidget;
    TagListLayout->addWidget(TagList);
    TagShowBox->setLayout(TagListLayout);
    //添加标记按钮
    AddTagBtn=new QPushButton;
    AddTagBtn->setText("添加标记");
//    AddTagBtn->setEnabled(false); //未被标记时按钮不能点击
    QObject::connect(AddTagBtn,SIGNAL(clicked()),this,SLOT(addLabel()));
    //阈值滑动条
    initThresholdSlider();
    thresholdSetLayout->addWidget(ThresholdSlider,8);
    thresholdSetLayout->addSpacing(10);
    thresholdSetLayout->addWidget(ThresholdInput,2);
    ArgsLayout->addLayout(thresholdSetLayout);
    ArgSetBox->setLayout(ArgsLayout);

    TagBoxLayout->addWidget(ImageInfoBox);
    TagBoxLayout->addWidget(TagShowBox);
    TagBoxLayout->addWidget(AddTagBtn);
    TagBoxLayout->addWidget(ArgSetBox);
    TagBox->setLayout(TagBoxLayout);
    return TagBox;
}

/**
 * @brief MainWindow::initThresholdSlider 初始化阈值设置的滑动条
 */
void MainWindow::initThresholdSlider(){
    ThresholdSlider=new QSlider;
    ThresholdSlider->setMaximum(255);
    ThresholdSlider->setMinimum(0);
    ThresholdSlider->setSingleStep(1);
    ThresholdSlider->setPageStep(1);
    ThresholdSlider->setValue(50);
    ThresholdSlider->setOrientation(Qt::Horizontal);
    //数值改变时实时改变输入框中显示的阈值
    QObject::connect(ThresholdSlider,SIGNAL(valueChanged(int)),this,SLOT(thresholdChanged(int)));
    //滑动释放时把数据传给后台
    QObject::connect(ThresholdSlider,SIGNAL(sliderReleased()),this,SLOT(thresholdReleased()));
    ThresholdInput=new QLineEdit;
    ThresholdInput->setText("默认");
    QObject::connect(ThresholdInput,SIGNAL(editingFinished()),this,SLOT(thresholdInputChanged()));
}

/**
 * @brief MainWindow::createImgTab 初始化图片显示TabWidget
 * @return 图片显示界面
 */
QGroupBox * MainWindow::createImgTab(){
    QGroupBox * ImgTabBox=new QGroupBox();
    ImgTab=new QTabWidget;
    ImgTab->setTabShape(QTabWidget::Triangular);
    ImgTab->setTabPosition(QTabWidget::North);

    QHBoxLayout * ImgTabLayout=new QHBoxLayout;
    ImgTabLayout->addWidget(ImgTab);
    ImgTabBox->setLayout(ImgTabLayout);
    ImgTab->setMovable(true);
    ImgTab->setTabsClosable(true);
    QObject::connect(ImgTab,SIGNAL(tabBarClicked(int)),this,SLOT(imageTabChanged(int)));
    return ImgTabBox;
}

/**
 * @brief MainWindow::initToolBar 初始化工具栏
 * ·打开图片
 * ·打开文件夹
 * ·框出矩形
 */
void MainWindow::initToolBar(){
    MainToolBar=ui->mainToolBar;
    QAction * openImgAction=new QAction("打开图片");
    QAction * openDirctory=new QAction("打开文件夹");
    QAction * drawRectangle=new QAction("框选矩形");
    QAction * manAdjust=new QAction("手动调整");
    QAction * autoAdjust=new QAction("自动调整");
    QAction * exportAnnotation=new QAction("导出文件");

    openImgAction->setStatusTip("打开一张图片");
    openDirctory->setStatusTip("批量打开一个文件夹中的图片");
    drawRectangle->setStatusTip("选择标记的范围");
    manAdjust->setStatusTip("拖动点调整标记边缘");
    autoAdjust->setStatusTip("点击不精确区域等待调整结果");
    exportAnnotation->setStatusTip("导出标注文件");

    MainToolBar->addAction(openImgAction);
    MainToolBar->addSeparator();
    MainToolBar->addAction(openDirctory);
    MainToolBar->addSeparator();
    MainToolBar->addAction(drawRectangle);
    MainToolBar->addSeparator();
    MainToolBar->addAction(manAdjust);
    MainToolBar->addSeparator();
    MainToolBar->addAction(autoAdjust);
    MainToolBar->addSeparator();
    MainToolBar->addAction(exportAnnotation);
    MainToolBar->addSeparator();

    QObject::connect(openImgAction,SIGNAL(triggered()),this,SLOT(openImg()));
    QObject::connect(openDirctory,SIGNAL(triggered()),this,SLOT(openDirectory()));
    QObject::connect(drawRectangle,SIGNAL(triggered()),this,SLOT(drawRectangle()));
    QObject::connect(manAdjust,SIGNAL(triggered()),this,SLOT(manAdjust()));
    QObject::connect(autoAdjust,SIGNAL(triggered()),this,SLOT(autoAdjust()));
    QObject::connect(exportAnnotation,SIGNAL(triggered()),this,SLOT(exportAnnotation()));
}

/**
 * @brief MainWindow::openImg slot 打开文件
 */
void MainWindow::openImg(){
    QString fileName;
    fileName=QFileDialog::getOpenFileName(this,"选择要打开的图片",
                                          "","Image Files(*.jpg *.png *.bmp *.pgm *.pbm);;All(*.*)");
    //分割文件路径为 文件夹 文件名
    QStringList list=fileName.split("/");
    QString directory,name;
    for(int i=0;i<list.size()-1;i++){
        if(i<list.size()-2){
            directory.append(list[i]).append("/");
        }else{
            directory.append(list[i]);
        }
    }
    name=list[list.size()-1];
    if(fileName!=""){
        //查看是否已经加入过fileList
        int isVisited=-1;
        for(int i=0;i<fileList.size();i++){
            if(fileList[i].imageName.compare(name)==0
                   && fileList[i].directory.compare(directory)==0){
                isVisited=i;
                break;
            }
        }
        //没有打开过就加入到文件列表并且打开文件
        if(isVisited==-1){
            addFileItem(directory,name);
            ImageFile file;
            file.directory=directory;
            file.imageName=name;
            file.isOpen=false;
            fileList.append(file);
            addImageTab(file);
        }else{
            addImageTab(fileList[isVisited]);
        }
    }
}

/**
 * slot 打开文件夹
 * @brief MainWindow::openDirectory
 */
void MainWindow::openDirectory(){
    QString directoryPath; //文件夹路径
    directoryPath=QFileDialog::getExistingDirectory();
    QDir dir;
    dir.setPath(directoryPath);
    QStringList ImageList;
    ImageList<<"*.bmp"<<"*.jpg"<<"*.png";//向字符串列表添加图片类型
    dir.setNameFilters(ImageList);//获得文件夹下图片的名字
    int count=dir.count();
    qDebug()<<count;
    for(int i=0;i<count;i++){ //遍历文件夹中的所有文件
        bool isVisited=false; //之前是否打开过相同的文件
        for(int j=0;j<fileList.size();j++){
            if(fileList[j].imageName.compare(dir[i])==0
                    &&fileList[j].directory.compare(directoryPath)==0){
                isVisited=true;
                break;
            }
        }
        ImageFile file;
        if(!isVisited){
            file.directory=directoryPath;
            file.imageName=dir[i];
            file.isOpen=false;
            //默认打开第一张图片展示
            if(i==0){
                addImageTab(file);
            }
            fileList.append(file);
            addFileItem(directoryPath,dir[i]);
        }
    }
}

/**
 * @brief MainWindow::drawRectangle 点击矩形框选事件
 */
void MainWindow::drawRectangle(){
    getCurrentWidget()->setViewAction(ImageGraphicsView::rectangle_act);
    qDebug()<<"now act:rectangle_act";
}

/**
 * @brief MainWindow::manAdjust 点击手动调整事件
 */
void MainWindow::manAdjust(){
    getCurrentWidget()->setViewAction(ImageGraphicsView::man_adjust_act);
    qDebug()<<"now act:man_adjust_act";
}

/**
 * @brief MainWindow::autoAdjust 点击自动调整事件
 */
void MainWindow::autoAdjust(){
    getCurrentWidget()->setViewAction(ImageGraphicsView::auto_adjust_act);
}

/**
 * @brief MainWindow::exportAnnotation 点击导出标注文件事件
 */
void MainWindow::exportAnnotation(){
    if(nowOpen==nullptr) return; //todo 或者添加一个提示框
    ExportChooseDialg * dialog=new ExportChooseDialg;
    int format=dialog->exec();
    if(format==ExportChooseDialg::JSON){
        nowOpen->image2Json();
    }else if(format==ExportChooseDialg::XML){
        //todo
    }
}

/**
 * @brief MainWindow::addLabel 弹出输入dialog提示用户输入
 */
void MainWindow::addLabel(){
    bool isOK;
    QString text=QInputDialog::getText(this,QString("添加标注")
                                       ,QString("请输入要添加的标注名称")
                                       ,QLineEdit::Normal
                                       ,QString("点击输入")
                                       ,&isOK);
    if(isOK){

    }
}

/**
 * 阈值进度条修改之后，修改变量thresholdValue，修改显示框中的信息
 * @brief MainWindow::ThresholdChanged
 * @param val 滑动条的数值
 */
void MainWindow::thresholdChanged(int val){
    nowOpen->setThreshold(val);
    qDebug()<<"阈值修改"<<nowOpen->getThreshold();
    ThresholdInput->setText(QString::number(val));
}

/**
 * 阈值输入框中的内容改变之后，修改变量thresholdValue,修改阈值进度条的显示
 * @brief MainWindow::thresholdInputChanged
 */
void MainWindow::thresholdInputChanged(){
   nowOpen->setThreshold(ThresholdInput->text().toInt());
   ThresholdSlider->setValue(nowOpen->getThreshold());
   getCurrentWidget()->setThreshold(nowOpen->getThreshold());
}

/**
 * 阈值进度条滑动释放之后将阈值传递给界面后端并更新界面
 * @brief MainWindow::thresholdReleased
 */
void MainWindow::thresholdReleased(){
    getCurrentWidget()->setThreshold(nowOpen->getThreshold());
}

/**
 * 增加一个图片的标签卡
 * @brief MainWindow::addImageTab
 * @param image 图片的结构体数据
 */
void MainWindow::addImageTab(ImageFile &image){
    Image *i=new Image(image.directory,image.imageName);
    openList.append(i);
    QString filePath=image.directory+"/"+image.imageName;
    if(!image.isOpen){
        ImageWidget * widget=new ImageWidget(filePath);
        ImgTab->addTab(widget,image.imageName);
        ImgTab->setCurrentWidget(widget);
        nowOpen=i;
        image.isOpen=true;
        refreshAnnotationBox();
    }
}

/**
 * 给filelist中增加一个file
 * @brief MainWindow::addFileItem
 * @param directory 图片的文件夹
 * @param fileName 图片的文件名
 */
void MainWindow::addFileItem(QString directory,QString fileName){
    ImageListWidgetItem * item=new ImageListWidgetItem(directory,fileName);
    item->setIndex(file_count++);
    QListWidgetItem * listItem=new QListWidgetItem;
    listItem->setSizeHint(QSize(200,100));
    FileWidget->addItem(listItem);
    FileWidget->setItemWidget(listItem,item);
    QObject::connect(item,SIGNAL(listItemClicked(int)),this,SLOT(fileListItemClick(int)));
}

/**
 * 双击文件列表事件
 * @brief MainWindow::fileListItemClick
 * @param index 双击的item的索引
 */
void MainWindow::fileListItemClick(int index){
    addImageTab(fileList[index]);
}

void MainWindow::refreshAnnotationBox(){
    QString name2show="图片名：" + QString(nowOpen->getImagePath().c_str());
    QString width2show="宽度：" + QString::number(nowOpen->getImageWidth());
    QString height2show="高度：" + QString::number(nowOpen->getImageHeight());
    if(nowOpen->getThreshold()!=-1){
        ThresholdSlider->setValue(nowOpen->getThreshold());
        ThresholdInput->setText(QString::number(nowOpen->getThreshold()));
    }else{
        ThresholdSlider->setValue(50);
        ThresholdInput->setText("默认");
    }
    imageNameLabel->setText(name2show);
    imageWidthLabel->setText(width2show);
    imageHeightLabel->setText(height2show);
}

/**
 * @brief MainWindow::imageTabChanged slot 标签卡点击事件
 * 更新图片的信息显示 更新标注显示 更新阈值显示
 * @param index 所点击标签卡的索引
 */
void MainWindow::imageTabChanged(int index){
    nowOpen=openList[index];
    refreshAnnotationBox();
}

/**
 * @brief MainWindow::getCurrentWidget
 * @return 当前正在被使用的imageWidget
 */
ImageWidget * MainWindow::getCurrentWidget(){
    return dynamic_cast<ImageWidget*>(ImgTab->currentWidget());
}
