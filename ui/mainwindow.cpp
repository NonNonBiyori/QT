/*
 * Copyright [2019]
 */

#include <iostream>
#include <algorithm>
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
    connect(ui->treeWidget_files, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(slot_double_click_file(QTreeWidgetItem*, int))); // 信号里不需要带参数名
    connect(ui->pb_opencv_image_pre, SIGNAL(clicked()), this, SLOT(slot_click_pre_image()));
    connect(ui->pb_opencv_image_post, SIGNAL(clicked()), this, SLOT(slot_click_pos_image()));
    connect(ui->pb_opencv_image_big, SIGNAL(clicked()), this, SLOT(slot_click_large_image()));
    connect(ui->pb_opencv_image_small, SIGNAL(clicked()), this, SLOT(slot_click_small_image()));

    ui->treeWidget_files->installEventFilter(this);
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

void MainWindow::slot_double_click_file(QTreeWidgetItem* item, int column)
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
        if (fileFormat == "jpg" || fileFormat == "png" || fileFormat == "JPG")
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

void MainWindow::slot_click_pre_image()
{
    if (ui->treeWidget_files->currentItem() != nullptr)
    {
        //QString txt = ui->treeWidget_files->itemBelow(ui->treeWidget_files->currentItem())->text(0);
        QTreeWidgetItem* lastItem = ui->treeWidget_files->itemAbove(ui->treeWidget_files->currentItem());
        if (lastItem != nullptr)
        {
            slot_double_click_file(lastItem, 0);
            ui->treeWidget_files->setCurrentItem(lastItem);
        }
    }
}

void MainWindow::slot_click_pos_image()
{
    if (ui->treeWidget_files->currentItem() != nullptr)
    {
        //QString txt = ui->treeWidget_files->itemBelow(ui->treeWidget_files->currentItem())->text(0);
        QTreeWidgetItem* nextItem = ui->treeWidget_files->itemBelow(ui->treeWidget_files->currentItem());
        if (nextItem != nullptr)
        {
            slot_double_click_file(nextItem, 0);
            ui->treeWidget_files->setCurrentItem(nextItem);
        }
    }
}

void MainWindow::slot_click_large_image()
{

}

void MainWindow::slot_click_small_image()
{

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
    //opencv_show_imageByOpencv(imagePath);
    //opencv_show_imageByQT(imagePath);
    // std::string fileName = imagePath;
    // std::string tmp = "";
    //if (imagePath.find(' ') != std::string::npos)
    //{
    //    for (int i = 0; i < imagePath.length(); i++)
    //    {
    //        if (imagePath[i] != ' ')
    //        {
    //            tmp += imagePath[i];
    //        }
    //    }
    //}
    //if (tmp != "")
    //{
    //    rename(imagePath.c_str(), tmp.c_str());
    //    fileName = tmp;
    //}

    // QT + opencv
    // Mat类图像是按照BGR顺序存储的图像，而QImage是按照RGB顺序存储的，在类型转换前需要将通道更改。
    cv::Mat image;
    cv::Mat temp;
    image = cv::imread(imagePath);
    cv::cvtColor(image, temp, cv::COLOR_BGR2RGB);//BGR convert to RGB
    QImage img = QImage((const unsigned char*)(temp.data), temp.cols, temp.rows, (int)temp.step, QImage::Format_RGB888); // step不加导致部分图片coredown
    ui->label_opencv_jpeg->clear();
    QSize tmpSize = ui->label_opencv_jpeg->size(); 
    ui->label_opencv_jpeg->resize(tmpSize);
    ui->label_opencv_jpeg->setPixmap(QPixmap::fromImage(img).scaled(tmpSize, Qt::KeepAspectRatio));
    ui->label_opencv_jpeg->setScaledContents(true);
    //if (tmp != "")
    //{
    //    rename(tmp.c_str(), imagePath.c_str());
    //}
}

void MainWindow::opencv_show_imageByOpencv(std::string imagePath)
{
    // opencv 显示图片
    std::cout << "OPENCV SHOW " << std::endl;
    cv::destroyAllWindows();
    cv::Mat image;
    image = cv::imread(imagePath);
    cv::namedWindow(imagePath, cv::WINDOW_NORMAL); // 第二个参数设置大小可调
    cv::imshow(imagePath, image);
}

void MainWindow::opencv_show_imageByQT(std::string imagePath)
{
    std::cout << "QT SHOW " << std::endl;
    // QT 显示图片
    QImage* img = new QImage;
    if (!(img->load(utf82gbk(imagePath))))//加载图像
    {
        std::cout << "open file : " << imagePath << " failed" << std::endl;
        delete img;
        return;
    }
    ui->label_opencv_jpeg->clear();
    ui->label_opencv_jpeg->setPixmap(QPixmap::fromImage(*img).scaled(ui->label_opencv_jpeg->size()));
}

void MainWindow::slot_click_delete()
{
    if (ui->treeWidget_files->currentItem() != nullptr)
    {
        QTreeWidgetItem* curItem = ui->treeWidget_files->currentItem();
        std::string filePath = utf82gbk(curItem->text(0));
        while (curItem->parent() != nullptr)
        {
            curItem = curItem->parent();
            filePath = utf82gbk(curItem->text(0)) + "/" + filePath;
        }
        std::cout << "delete " << filePath << std::endl;
        remove(filePath.c_str());
        QTreeWidgetItem* nextItem = ui->treeWidget_files->itemBelow(ui->treeWidget_files->currentItem());
        delete ui->treeWidget_files->currentItem();
        if (nextItem != nullptr)
        {
            slot_double_click_file(nextItem, 0);
            ui->treeWidget_files->setCurrentItem(nextItem);
        }
    }
}

bool MainWindow::eventFilter(QObject* target, QEvent* event) {
    if (target == ui->treeWidget_files) 
    {
        if (event->type() == QEvent::KeyPress) 
        {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            //if ((keyEvent->modifiers() == Qt::ControlModifier) && (keyEvent->key() == Qt::Key_C))
            //{
            //    QListWidget* listW = static_cast<QListWidget*>(target);
            //    QList<QListWidgetItem*> selectItems = listW->selectedItems();
            //    auto it = selectItems.begin();
            //    QString newText = "";
            //    for (; it != selectItems.end(); it++) {
            //        newText += (*it)->text() + "\n";
            //    }
            //    QClipboard* clipboard = QApplication::clipboard();   //获取系统剪贴板指针
            //    clipboard->setText(newText);		             //设置剪贴板内容</span>
            //    return true;
            //}
            keyPressEvent(keyEvent);
            return true;
        }
    }
    return QWidget::eventFilter(target, event);
}

void MainWindow::mousePressEvent(QMouseEvent* event) 
{

}

void MainWindow::keyPressEvent(QKeyEvent* event) 
{
    if (event->key() == Qt::Key_Up) 
    {
        slot_click_pre_image();
    }
    else if (event->key() == Qt::Key_Down)
    {
        slot_click_pos_image();
    }
    else if (event->key() == Qt::Key_D)
    {
        slot_click_delete();
    }
    return;
}