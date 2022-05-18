#ifndef EXPORTCHOOSEDIALG_H
#define EXPORTCHOOSEDIALG_H

#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDebug>

class ExportChooseDialg : public QDialog
{
    Q_OBJECT

public:
    enum FORMAT {JSON,XML};
    ExportChooseDialg();
    int exec();
private:
    FORMAT export_format;
    QVBoxLayout * DialogLayout;
    QPushButton * JsonBtn;
    QPushButton * XMLBtn;
public slots:
    void JsonBtnClicked();
    void XMLBtnClicked();
private:
    void initUI();
};

#endif // EXPORTCHOOSEDIALG_H
