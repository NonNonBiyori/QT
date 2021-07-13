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
    m_duration = 0;
    ui->setupUi(this);
    m_pPlayer = new QMediaPlayer;
    m_pPlayerWidget = new QVideoWidget;
    m_pPlayer->setVideoOutput(m_pPlayerWidget);
    ui->verticalLayout->addWidget(m_pPlayerWidget);

    //m_pPlayerWidget->setAutoFillBackground(true);
    QPalette qplte;
    qplte.setColor(QPalette::Window, QColor(0,0,0));
    //qplte.setBrush();
    m_pPlayerWidget->setPalette(qplte);

    init();
}

VedioPlayer::~VedioPlayer()
{
    delete m_pPlayer;
    delete m_pPlayerWidget;
    delete ui;
}

void VedioPlayer::init()
{
    connect(ui->pb_vedio_choose,SIGNAL(clicked()),this,SLOT(slot_choose_vedio()));
    connect(ui->pb_vedio_control,SIGNAL(clicked()),this,SLOT(slot_control_vedio()));
    connect(m_pPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(slot_get_time_vedio(qint64)));
    connect(m_pPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(slot_set_posion(qint64)));
    connect(ui->horizontalSlider_vedio,SIGNAL(sliderReleased()),this,SLOT(slot_slider_drag()));
}

void VedioPlayer::slot_choose_vedio()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                       tr("选择文件"),
                                                       "D:");
    m_pPlayer->setMedia(QUrl::fromLocalFile(fileName));
    m_pPlayer->play();
    std::cout << fileName.toStdString() << std::endl;
}

void VedioPlayer::slot_control_vedio()
{
    if (m_pPlayer->state() == QMediaPlayer::PausedState)
    {
        m_pPlayer->play();
        ui->pb_vedio_control->setText("暂停");
    }
    else if (m_pPlayer->state() == QMediaPlayer::PlayingState)
    {
        m_pPlayer->pause();
        ui->pb_vedio_control->setText("播放");
    }
}

void VedioPlayer::slot_get_time_vedio(qint64 time)
{
    m_duration = m_pPlayer->duration() / 1000;
    std::cout << "duration = " << m_duration << std::endl;
    ui->horizontalSlider_vedio->setRange(0,m_duration);
}

void VedioPlayer::slot_set_posion(qint64 time)
{
    ui->horizontalSlider_vedio->setValue(time / 1000);
}

void VedioPlayer::slot_slider_drag()
{
    int pos = ui->horizontalSlider_vedio->value();
    m_pPlayer->setPosition(pos * 1000);
}
