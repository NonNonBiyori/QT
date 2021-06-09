/*
 * Copyright [2019]
 */

#ifndef VEDIOPLAYER_H
#define VEDIOPLAYER_H

#include <QWidget>
#include <QtMultimedia>
#include <QVideoWidget>

namespace Ui {
class VedioPlayer;
}

class VedioPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit VedioPlayer(QWidget *parent = 0);
    ~VedioPlayer();

public slots:
    void slot_choose_vedio();

private:
    void init();

private:
    Ui::VedioPlayer *ui;
};

#endif // VEDIOPLAYER_H
