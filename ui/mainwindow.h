/*
 * Copyright [2019]
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma execution_character_set("utf-8") 

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <string>
#include <vector>
#include <map>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void slot_vedio_player();        // QT播放视频
    void slot_opencv_vedio_player(); // opencv播放视频
    void slot_opencv_jpeg_player();  // opencv打开图片
    void slot_open_file_path();      // 选择文件夹
    void slot_double_click_file(QTreeWidgetItem* item, int column); // 选择文件
    void slot_click_pre_image();     // 上一张
    void slot_click_pos_image();     // 上一张
    void slot_click_large_image();   // 放大
    void slot_click_small_image();   // 缩小
    void slot_click_delete();        // 删除
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event);
    bool eventFilter(QObject* target, QEvent* event);

private:
    void init();
    void setFiles(QString dirStr, QTreeWidgetItem* root=nullptr);
    void opencv_show_image(std::string imagePath);
    void opencv_show_imageByOpencv(std::string imagePath);
    void opencv_show_imageByQT(std::string imagePath);

private:
    Ui::MainWindow *ui;
    std::map<std::string, std::vector<std::string> > m_fileNameMap; // <文件夹，文件夹下的文件

};

#endif // MAINWINDOW_H
