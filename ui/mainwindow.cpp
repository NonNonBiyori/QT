/*
 * Copyright [2019]
 */

#include <iostream>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vedioplayer.h"
#include "opencvvedio.h"

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
    connect(ui->pb_openCV,SIGNAL(clicked()),this,SLOT(slot_opencv_player()));
}

void MainWindow::slot_vedio_player()
{
    std::cout << "xujl slot_vedio_player " << std::endl;
    VedioPlayer *vp = new VedioPlayer;
    vp->show();
}

void MainWindow::slot_opencv_player()
{
    std::cout << "xujl slot_opencv_player " << std::endl;
    OpencvVedio *ovp = new OpencvVedio;
    ovp->show();
}
