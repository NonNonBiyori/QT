/*
 * Copyright [2019]
 */

#ifndef OPENCV_JPEGPLAYER_H
#define OPENCV_JPEGPLAYER_H

#include <QWidget>
#include <QtMultimedia>
#include <QVideoWidget>

namespace Ui {
class OpencvJpeg;
}

class OpencvJpeg : public QWidget
{
    Q_OBJECT

public:
    explicit OpencvJpeg(QWidget *parent = 0);
    ~OpencvJpeg();

public slots:
    void slot_choose_jpeg();

private:
    void init();

private:
    Ui::OpencvJpeg*ui;
};

#endif // OPENCV_JPEGPLAYER_H
