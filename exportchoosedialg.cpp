#include "exportchoosedialg.h"

ExportChooseDialg::ExportChooseDialg()
{
    initUI();
}

void ExportChooseDialg::initUI(){
    DialogLayout=new QVBoxLayout;
    JsonBtn=new QPushButton;
    XMLBtn=new QPushButton;

    JsonBtn->setText("导出为Json格式");
    XMLBtn->setText("导出为XML格式");
    DialogLayout->addWidget(JsonBtn);
    DialogLayout->addWidget(XMLBtn);

    QObject::connect(JsonBtn,SIGNAL(clicked()),this,SLOT(JsonBtnClicked()));
    QObject::connect(XMLBtn,SIGNAL(clicked()),this,SLOT(XMLBtnClicked()));

    this->setLayout(DialogLayout);
    this->setWindowTitle("选择导出格式");
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowCloseButtonHint);
    this->resize(300,100);
}

void ExportChooseDialg::JsonBtnClicked(){
    qDebug()<<"导出为Json格式";
    this->accept();
    export_format=JSON;
}

void ExportChooseDialg::XMLBtnClicked(){
    qDebug()<<"导出为XML格式";
    this->accept();
    export_format=XML;
}

int ExportChooseDialg::exec(){
    QDialog::exec();
    return export_format;
}


