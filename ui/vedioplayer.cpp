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
    m_pPlayer = new QMediaPlayer;
    m_pPlayerWidget = new QVideoWidget;
    m_pPlayer->setVideoOutput(m_pPlayerWidget);
    ui->verticalLayout->addWidget(m_pPlayerWidget);

    m_pPlayerWidget->setAutoFillBackground(true);
    QPalette qplte;
    qplte.setColor(QPalette::Window, QColor(0,0,0));
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
}

void VedioPlayer::slot_choose_vedio()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                       tr("选择文件"),
                                                       "D:");
    m_pPlayer->setMedia(QUrl::fromLocalFile(fileName));
    std::cout << fileName.toStdString() << std::endl;
}
