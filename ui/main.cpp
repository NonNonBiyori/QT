#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //QIcon icon(":/new/prefix1/image/head.png");
    //w.setWindowIcon(icon);
    w.show();
    return a.exec();
}
