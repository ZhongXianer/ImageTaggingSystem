#include "mainwindow.h"
#include <QApplication>
//解决python和Qt的关键词slots冲突
#pragma push_macro("slots")
#undef slots
#include <Python.h>
#pragma pop_macro("slots")



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Py_Initialize();
    MainWindow w;
    w.show();
    return a.exec();
}
