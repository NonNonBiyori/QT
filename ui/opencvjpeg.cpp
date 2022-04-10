/*
 * Copyright [2019]
 */

#include <iostream>
#include <thread>
#include <chrono>
#include <QFileDialog>
#include <opencv2/opencv.hpp>
#include "opencvjpeg.h"
#include "ui_opencvjpeg.h"

OpencvJpeg::OpencvJpeg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OpencvJpeg)
{
    ui->setupUi(this);
    init();
}

OpencvJpeg::~OpencvJpeg()
{
    delete ui;
}

void OpencvJpeg::init()
{
    connect(ui->pb_opencv_jpeg_choose,SIGNAL(clicked()),this,SLOT(slot_choose_jpeg()));
}

void OpencvJpeg::slot_choose_jpeg()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                       tr("选择文件"),
                                                       "D:");
    cv::Mat image;
    image = cv::imread(fileName.toStdString());
    std::cout << fileName.toStdString() << std::endl;
    cv::imshow("baoer",image);
}

