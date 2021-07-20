/*
 * Copyright [2019]
 */

#ifndef OPENCV_VEDIOPLAYER_H
#define OPENCV_VEDIOPLAYER_H

#include <QWidget>
#include <QtMultimedia>
#include <QVideoWidget>

namespace Ui {
class OpencvVedio;
}

class OpencvVedio : public QWidget
{
    Q_OBJECT

public:
    explicit OpencvVedio(QWidget *parent = 0);
    ~OpencvVedio();

public slots:
    void slot_choose_vedio();

private:
    void init();

private:
    Ui::OpencvVedio *ui;
};

#endif // OPENCV_VEDIOPLAYER_H
