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
    void slot_control_vedio();
    void slot_get_time_vedio(qint64 time);

private:
    void init();

private:
    Ui::VedioPlayer *ui;
    QVideoWidget    *m_pPlayerWidget;
    QMediaPlayer    *m_pPlayer;


    int64_t         m_duration;
};

#endif // VEDIOPLAYER_H
