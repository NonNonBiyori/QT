/*
 * Copyright [2019]
 */

#include <iostream>
#include <thread>
#include <chrono>
#include <QFileDialog>
#include <opencv2/opencv.hpp>
#include "opencvvedio.h"
#include "ui_opencvvedio.h"

OpencvVedio::OpencvVedio(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OpencvVedio)
{
    ui->setupUi(this);
    init();
}

OpencvVedio::~OpencvVedio()
{
    delete ui;
}

void OpencvVedio::init()
{
    connect(ui->pb_opencv_vedio_choose,SIGNAL(clicked()),this,SLOT(slot_choose_vedio()));
}

void OpencvVedio::slot_choose_vedio()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                       tr("选择文件"),
                                                       "D:");
    cv::Mat image;
    image = cv::imread(fileName.toStdString());
    std::cout << fileName.toStdString() << std::endl;
    cv::imshow("baoer",image);
}

