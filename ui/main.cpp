#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    MainWindow w;
    //QIcon icon(":/new/prefix1/image/head.png");
    //w.setWindowIcon(icon);
    w.show();
    return a.exec();
}
