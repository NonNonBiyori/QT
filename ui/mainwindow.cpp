/*
 * Copyright [2019]
 */

#include <iostream>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

#include <QFileDialog>
#include <QDirModel>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vedioplayer.h"
#include "opencvvedio.h"
#include "opencvjpeg.h"
#include "../include/utils.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("mydemo"));
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    connect(ui->pb_vedio,SIGNAL(clicked()),this,SLOT(slot_vedio_player()));
    connect(ui->pb_openCV,SIGNAL(clicked()),this,SLOT(slot_opencv_vedio_player()));
    connect(ui->pb_openCV_JPEG, SIGNAL(clicked()), this, SLOT(slot_opencv_jpeg_player()));
    connect(ui->pb_open, SIGNAL(clicked()), this, SLOT(slot_open_file_path()));
    connect(ui->treeWidget_files, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(slot_click_file(QTreeWidgetItem*, int))); // 信号里不需要带参数名
}

void MainWindow::slot_vedio_player()
{
    std::cout << "xujl slot_vedio_player " << std::endl;
    VedioPlayer *vp = new VedioPlayer;
    vp->show();
}

void MainWindow::slot_opencv_vedio_player()
{
    std::cout << "xujl slot_opencv_player " << std::endl;
    OpencvVedio *ovp = new OpencvVedio;
    ovp->show();
}

void MainWindow::slot_opencv_jpeg_player()
{
    std::cout << "xujl slot_jpeg_player " << std::endl;
    OpencvJpeg* ovp = new OpencvJpeg;
    ovp->show();
}

void MainWindow::slot_open_file_path()
{
    m_fileNameMap.clear();
    std::cout << "xujl slot_open_file_path " << std::endl;
    QString dirStr = QFileDialog::getExistingDirectory(this, tr("选择目录"),
        "E:",
        QFileDialog::ShowDirsOnly
        | QFileDialog::DontResolveSymlinks);
    std::cout << "xujl dirStr: " << utf82gbk(dirStr) << std::endl;
    if (!dirStr.isEmpty())
    {
        ui->treeWidget_files->clear();
        setFiles(dirStr);
    }
}

void MainWindow::slot_click_file(QTreeWidgetItem* item, int column)
{
    std::cout << "xujl slot_click_file: " << utf82gbk(item->text(column)) << ",col = " << column << std::endl;
    std::string filePath = utf82gbk(item->text(column));
    while (item->parent() != nullptr)
    {
        item = item->parent();
        filePath = utf82gbk(item->text(column)) + "/" + filePath;
    }
    auto it = filePath.find_last_of('.');
    if (it != std::string::npos)
    {
        std::string fileFormat = filePath.substr(it + 1, filePath.length() - it - 1);
        if (fileFormat == "jpg")
        {
            opencv_show_image(filePath);
        }
        else if (fileFormat == "mp4")
        {

        }
        else
        {
            std::cout << "unkown file format : " << fileFormat << std::endl;
        }
    }
}

void MainWindow::setFiles(QString dirStr, QTreeWidgetItem* root)
{
    QDir dir(dirStr);
    dirStr = dir.fromNativeSeparators(dirStr);//  "\\"转为"/" 
    std::cout << "xujl dirStr: " << utf82gbk(dirStr) << std::endl;
    if (dir.exists())
    {
        dir.setFilter(QDir::Files);
        dir.setSorting(QDir::Name);
        //dir.setNameFilters(QString("*.tiff;*.tif").split(";"));
        QStringList fileNames = dir.entryList();
        if (root == nullptr)
        {
            root = new QTreeWidgetItem(ui->treeWidget_files, QStringList(dirStr));
        }
        
        for (int i = 0; i < fileNames.size(); ++i)
        {
            std::cout << "xujl file: " << i << "-" << utf82gbk(fileNames[i]) << std::endl;
            QTreeWidgetItem* child = new QTreeWidgetItem(QStringList() << fileNames[i]);
            //child->setIcon(0, QIcon(":/file/image/link.ico"));
            //child->setCheckState(1, Qt::Checked);
            root->addChild(child);
        }
        dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
        dir.setSorting(QDir::Name);
        QStringList subDir = dir.entryList();
        for (int i = 0; i < subDir.size(); ++i)
        {
            QTreeWidgetItem* child = new QTreeWidgetItem(QStringList() << subDir[i]);
            root->addChild(child);
            setFiles(dirStr + "/" + subDir[i], child);
            std::cout << "xujl dir: " << i << "-" << utf82gbk(subDir[i]) << std::endl;
        }
    }
    QDirModel* dirModel = new QDirModel;
}

void MainWindow::opencv_show_image(std::string imagePath)
{
    //// opencv 显示图片
    //cv::destroyAllWindows();
    //cv::Mat image;
    //image = cv::imread(imagePath);
    //cv::namedWindow(imagePath, cv::WINDOW_NORMAL); // 第二个参数设置大小可调
    //cv::imshow(imagePath, image);

    //// QT 显示图片
    //QImage* img = new QImage;
    //if (!(img->load(utf82gbk(imagePath))))//加载图像
    //{
    //    std::cout << "open file : " << imagePath << " failed" << std::endl;
    //    delete img;
    //    return;
    //}
    //ui->label_opencv_jpeg->clear();
    //ui->label_opencv_jpeg->setPixmap(QPixmap::fromImage(*img).scaled(ui->label_opencv_jpeg->size()));

    // QT + opencv
    // Mat类图像是按照BGR顺序存储的图像，而QImage是按照RGB顺序存储的，在类型转换前需要将通道更改。
    cv::Mat image;
    cv::Mat temp;
    image = cv::imread(imagePath);
    cv::cvtColor(image, temp, cv::COLOR_BGR2RGB);//BGR convert to RGB
    QImage img = QImage((const unsigned char*)(temp.data), temp.cols, temp.rows, QImage::Format_RGB888);
    ui->label_opencv_jpeg->clear();
    ui->label_opencv_jpeg->setPixmap(QPixmap::fromImage(img).scaled(ui->label_opencv_jpeg->size(), Qt::KeepAspectRatio));
    ui->label_opencv_jpeg->setScaledContents(true);
}