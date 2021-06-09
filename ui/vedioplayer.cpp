/*
 * Copyright [2019]
 */

#include <iostream>
#include <thread>
#include <chrono>
#include <QFileDialog>
#include "vedioplayer.h"
#include "ui_vedioplayer.h"

VedioPlayer::VedioPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VedioPlayer)
{
    ui->setupUi(this);
    init();
}

VedioPlayer::~VedioPlayer()
{
    delete ui;
}

void VedioPlayer::init()
{
    connect(ui->pb_vedio_choose,SIGNAL(clicked()),this,SLOT(slot_choose_vedio()));
}

void VedioPlayer::slot_choose_vedio()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                       tr("选择文件"),
                                                       "D:");
    std::cout << fileName.toStdString() << std::endl;
}
